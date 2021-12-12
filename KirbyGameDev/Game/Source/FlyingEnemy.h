#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Textures.h"
#include "Animation.h"
#include "PathFinding.h"

struct SDL_Texture;


enum FLYING_ENEMY_STATE
{
	PATROLLIN,
	CHASIN_PLAYER,
	DEATHSS
};

class FlyingEnemy : public Module
{

private:
	float x, y;
	b2Vec2 speed = { 1.3,0 };
	float maxXspeed;

	b2Vec2 DetectionRange;

	SDL_Texture* texture;

public:
	iPoint directionPoint; // pixels	

	iPoint positionOfTheObject; // pixels	

	int lifes;
	bool isAlive;

	float startPosX;
	float startPosY;
	bool isDead;
	int lastY;
	bool direction;

	SDL_Rect enemyRect;
	int statesInt;

	FLYING_ENEMY_STATE actualState;

	PhysBody* enemyPhys;

	FlyingEnemy();
	virtual ~FlyingEnemy();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	//bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	int GetEnemyLifes();
	void SetEnemyLifes(int l);
	void SetEnemyState(FLYING_ENEMY_STATE state);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


	Animation* currentAnimation = nullptr;
	//int direction;

	/*void FlyingEnemy::SetAnimation(Animation& toChange)
	{
		if (currentAnimation != &toChange) {

			toChange.Reset();
			currentAnimation = &toChange;
		}
	}*/

	FlyingEnemy* CreateFlyingEnemy(int xPosition, int yPosition)
	{
		FlyingEnemy enemy;

		enemy.startPosX = xPosition;
		enemy.startPosY = yPosition;

		enemy.enemyPhys = app->physics->CreateCircle(enemy.startPosX, enemy.startPosY, 6, b2_dynamicBody);
		enemy.enemyPhys->id = 5;
		enemy.enemyPhys->listener = app->flyingEnemy;

		enemy.actualState = PATROLLIN;

		enemy.lifes = 2;
		enemy.isAlive = true;
		enemy.deathAnimAllowed = false;



		return &enemy;
	}

	//// Set of animations
	//// IDLE animations
	Animation rightIdleAnim;
	Animation leftIdleAnim;



	bool deathAnimAllowed;
};
