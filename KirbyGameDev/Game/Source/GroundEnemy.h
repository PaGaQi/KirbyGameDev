#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Textures.h"
#include "Animation.h"

struct SDL_Texture;


enum GROUND_ENEMY_STATE
{
	WALKING,
	ATTACK,
	DEATHS
};

class GroundEnemy : public Module
{

private:
	float x, y;
	b2Vec2 speed = { 1.3,0 };

	b2Vec2 DetectionRange;
	
public:
	GroundEnemy();
	virtual ~GroundEnemy();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	//bool LoadState(pugi::xml_node&);
	//bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	//void SetEnemyState(GROUND_ENEMY_STATE state);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

private:
	iPoint directionPoint; // pixels	

	iPoint positionOfTheObject; // pixels	

	bool isDead;
	int lastY;
	bool direction;

	int deathSFX;

	GROUND_ENEMY_STATE actualState;

	b2Vec2 enemyPos;
	b2Vec2 enemyVel;

	b2Vec2 startPos;

	PhysBody* enemyPhys;
	SDL_Rect enemyRect;
	SDL_Texture* enemySprites = nullptr;


	Animation* currentAnimation = nullptr;

	Animation walkRight;
	Animation walkLeft;		
};