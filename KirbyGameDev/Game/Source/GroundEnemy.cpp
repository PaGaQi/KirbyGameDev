#include "GroundEnemy.h"
#include "App.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"
#include "List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"

GroundEnemy::GroundEnemy()
{
	texture = nullptr;

	/*float idleSpeed = ;
	float movement1Speed = ;
	float movement2Speed = ;
	float deathSpeed = ;*/


	//ANIMATIONS


}

GroundEnemy::~GroundEnemy()
{

}

bool GroundEnemy::Awake()
{

	return true;
}

bool GroundEnemy::Start()
{
	texture = app->tex->Load("Assets/sprites/EnemySpritesheet.png");

	/*startPosX = ;
	startPosY = ;
	speed = ;*/

	LOG("Loading Ground Enemy");

	return true;
}



/*bool GroundEnemy::PostUpdate()
{
	app->render->DrawTexture(texture, positionOfTheObject.x - 5, positionOfTheObject.y, &currentAnimation->GetCurrentFrame());
	return true;
}*/

bool GroundEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}

int GroundEnemy::GetEnemyLifes()
{
	return lifes;
}

void GroundEnemy::SetEnemyLifes(int l)
{
	lifes = l;
}

void GroundEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 5) && (bodyB->id == 1))
		{

			// is hitted by the player

		}
	}
}



