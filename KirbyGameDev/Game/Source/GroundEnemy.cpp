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
#include "Audio.h"
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

	if (app->currentScene == LEVEL_1)
	{
		LOG("Loading ground enemy");
		texture = app->tex->Load("Assets/textures/EnemySpritesheet.png");

		direction = 0;
		lastY = 704;

		enemyRect = { 0, 576, 33, 33 };
		b2Vec2 playerPos = { 0, 0 };
		b2Vec2 playerVel = { 0, 0 };

		LOG("Creating player hitbox");
		enemyPhys = app->physics->CreateCircle(90, 576, 14, b2_dynamicBody);

		jumpSFX = app->audio->LoadFx("Assets/audio/fx/jump.wav");
		deathSFX = app->audio->LoadFx("Assets/audio/fx/death_Kirb.wav");
		isDead = false;
	}

	return true;
}



bool GroundEnemy::PostUpdate()
{
	//app->render->DrawTexture(texture, positionOfTheObject.x - 5, positionOfTheObject.y, &currentAnimation->GetCurrentFrame());
	return true;
}

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



