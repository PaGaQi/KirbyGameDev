#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Module.h"
#include "Animation.h"

#include <Box2D/Box2D/Box2D.h>

struct SDL_Texture;

class Player : public Module
{
public:


	Player();

	// Destructor
	virtual ~Player();
	
	// Called before render is available
	//bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	bool LevelStart(int level);

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();


	// Called before quitting
	virtual bool CleanUp();

	//Collision callback, called when the player intersects with another collider
	void OnCollision(b2Body* bodyA, b2Body* bodyB);


	// Position of the player in the map
	int x;
	int y;
	bool isMoving;
	int direction;

	SDL_Rect playerRect;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* playerSprites = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idle;
	Animation jump;
	Animation left;
	Animation right;

	// Sound effects indices								???????????????????????????????????
};

#endif