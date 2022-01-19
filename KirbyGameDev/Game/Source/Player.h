#pragma once

#include "App.h"
#include "Module.h"
#include "Animation.h"
#include "Physics.h"
#include "Point.h"

struct SDL_Texture;

class PhysBody;

class Player : public Module
{
public:

	PhysBody* playerPhys;

	Player();

	// Destructor
	virtual ~Player();
	
	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	virtual bool CleanUp();

	//Collision callback, called when the player intersects with another collider
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	bool PlayerWin();
	
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	bool isDead;
	bool collectibleGet;

	bool paused;

private:
	// Position of the player in the map
	int x;
	int y;
	int lastY;
	bool win;

	bool isMoving;
	bool direction;
	bool godMode;
	bool isJumping;
	bool deadDirection;

	SDL_Rect playerRect;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* playerSprites = nullptr;	

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRight;
	Animation idleLeft;
	Animation jumpRight;
	Animation jumpLeft;
	//Animation fallRight;
	Animation fallLeft;
	//Animation peakRight;
	//Animation peakLeft;
	Animation walkLeft;
	Animation walkRight;
	Animation death;


	b2Vec2 startPos;

	b2Vec2 playerPos;
	b2Vec2 playerVel;

	int deathHeight;

	int jumpSFX;
	int deathSFX;
};

