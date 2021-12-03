#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "PugiXml/src/pugixml.hpp"
#include "PugiXml/src/pugiconfig.hpp"



#include "Box2D/Box2D/Box2D.h"

#include "PugiXml/src/pugixml.hpp"


#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "savegame.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Player;
class Menu;
class Scene;
class Map;
class Physics;


enum sceneType
{
	TITLE,
	LEVEL_1,
	DEATH,
	

};

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	void ChangeScene(sceneType nextScene);

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Player* player;
	Menu* menu;
	Scene* scene;
	Map* map;
	Physics* physics;

	sceneType currentScene = TITLE;

#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1024




private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;
public:
	
	

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	uint32 start;

	uint frames;
	float dt;

	// L02: DONE 1: Create variables to control when to execute the request load / save
	mutable bool saveGameRequested;
	bool loadGameRequested;

	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	//float dt = 0.0f;
};

extern App* app;

#endif	// __APP_H__