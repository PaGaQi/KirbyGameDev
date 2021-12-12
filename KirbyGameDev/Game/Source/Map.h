#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "PQueue.h"
#include "Queue.h"
#include "DynArray.h"
#include "SDL/include/SDL.h"

#include "PugiXml\src\pugixml.hpp"

#define COST_MAP_SIZE	100

// L03: DONE 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tile_width;
	int	tile_height;

	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	tilecount;
	int	columns;
	//int	offsetX;
	//int	offsetY;

	// L04: TODO 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;
};

// L03: DONE 1: We create an enum for map type, just for convenience,
// NOTE: Platformer game will be of type ORTHOGONAL
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// L04: TODO 1: Create a struct for the map layer
struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	// L04: TODO 6: Short function to get the gid value of x,y
	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

// L03: DONE 1: Create a struct needed to hold the information to Map node
struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;

	// L04: TODO 2: Add a list/array of layers to the map
	List<MapLayer*> maplayers;
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);

	// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	iPoint WorldToMap(int x, int y) const;

	// L10: BFS Pathfinding methods
	void ResetPath();
	void DrawPath();
	bool IsWalkable(int x, int y) const;

	// L11: More pathfinding methods
	int MovementCost(int x, int y) const;
	void ComputePath(int x, int y);

	// L12a: AStar pathfinding
	void ComputePathAStar(int x, int y);

	// Propagation methods
	void PropagateBFS();
	void PropagateDijkstra();
	// L12a: AStar propagation
	void PropagateAStar(int heuristic);

private:

	bool LoadMap(pugi::xml_node mapFile);

	// L03: Methods to load all required map data
	bool LoadTileSets(pugi::xml_node mapFile);
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);

	// L04
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadAllLayers(pugi::xml_node mapNode);

	TileSet* GetTilesetFromTileId(int id) const;

public:

    // L03: DONE 1: Add your struct for map info
	MapData mapData;

private:

    SString folder;
    bool mapLoaded;

	// L10: BFS Pathfinding variables
	PQueue<iPoint> frontier;
	List<iPoint> visited;

	// L11: Additional variables
	List<iPoint> breadcrumbs;
	uint costSoFar[COST_MAP_SIZE][COST_MAP_SIZE];
	DynArray<iPoint> path;

	// L12: AStar (A*) variables
	iPoint goalAStar;			// Store goal target tile
	bool finishAStar = false;	// Detect when reached goal

	SDL_Texture* tileX = nullptr;
};

#endif // __MAP_H__