#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#include <Box2D/Box2D/Box2D.h>
#include "SDL/include/SDL.h"

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
	int lastY;

	bool isMoving;
	bool direction;
	bool godMode;
	bool isDead;
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

	PhysBody* playerPhys;
	

	b2Vec2 playerPos;
	b2Vec2 playerVel;


	int jumpSFX;
	int deathSFX;
};

#endif