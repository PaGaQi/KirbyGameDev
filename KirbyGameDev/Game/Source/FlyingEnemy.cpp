#include "App.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "Audio.h"
#include "FlyingEnemy.h"
#include "Animation.h"
#include "PathFinding.h"


FlyingEnemy::FlyingEnemy()
{	
	/*float idleSpeed = ;
	float movement1Speed = ;
	float movement2Speed = ;
	float deathSpeed = ;*/


	//ANIMATIONS
}

FlyingEnemy::~FlyingEnemy()
{

}

bool FlyingEnemy::Start()
{
	if (app->currentScene == LEVEL_1)
	{
		LOG("Creating enemy hitbox");
		enemyPhys = app->physics->CreateCircle(1500, 500, 14, b2_dynamicBody);
		enemyPhys->id = 2;
		enemyPhys->listener = this;
	}

	return true;
}

/*
bool FlyingEnemy::Update(float dt)
{
	
	return true;
}
bool FlyingEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}

int FlyingEnemy::GetEnemyLifes()
{
	return lifes;
}

void FlyingEnemy::SetEnemyLifes(int l)
{
	lifes = l;
}
*/

void FlyingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	//else if (bodyB == app->player->playerPhys) LOG("PLAYER HABING LE SEXEEEEEEEEEEEEEEEEE");
	else LOG("ENEMY EATING BEANS AT THE THEATER");
	
}