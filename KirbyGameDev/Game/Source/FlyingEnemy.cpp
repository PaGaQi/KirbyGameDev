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
#include "FlyingEnemy.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

FlyingEnemy::FlyingEnemy()
{
	texture = nullptr;

	/*float idleSpeed = ;
	float movement1Speed = ;
	float movement2Speed = ;
	float deathSpeed = ;*/


	//ANIMATIONS


}

FlyingEnemy::~FlyingEnemy()
{

}

bool FlyingEnemy::Awake()
{

	return true;
}

bool FlyingEnemy::Start()
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



/*bool FlyingEnemy::PostUpdate()
{
	app->render->DrawTexture(texture, positionOfTheObject.x - 5, positionOfTheObject.y, &currentAnimation->GetCurrentFrame());
	return true;
}*/

/*bool FlyingEnemy::CleanUp()
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

void FlyingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
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
}*/