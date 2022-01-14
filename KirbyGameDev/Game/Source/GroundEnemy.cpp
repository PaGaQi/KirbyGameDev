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
	//ANIMATIONS

	////Left Walk Animation---------------------------
	walkLeft.PushBack({ 0, 0, 32, 32 });
	walkLeft.PushBack({ 34, 0, 32, 32 });

	walkLeft.loop = true;
	walkLeft.speed = 0.2f;

	////Right Walk Animation---------------------------
	walkRight.PushBack({ 0, 34, 32, 32 });
	walkRight.PushBack({ 34, 34, 32, 32 });


	walkRight.loop = true;
	walkRight.speed = 0.2f;

}

GroundEnemy::~GroundEnemy() {}

bool GroundEnemy::Awake()
{
	return true;
}

bool GroundEnemy::Start()
{
	if (app->currentScene == LEVEL_1)
	{
		LOG("Loading ground enemy");
		enemySprites = app->tex->Load("Assets/textures/EnemySpritesheet.png");

		currentAnimation = &walkRight;
		direction = 0;		

		enemyRect = { 2050, 436, 32, 32 };
		b2Vec2 enemyPos = { 0, 0 };
		b2Vec2 enemyVel = { 0, 0 };

		LOG("Creating Enemy Hitbox");
		enemyPhys = app->physics->CreateCircle(2050, 436, 14, b2_dynamicBody);
		enemyPhys->id = 2;
		enemyPhys->listener = this;

		isDead = false;

	}

	return true;
}

bool GroundEnemy::PreUpdate()
{
	if (app->currentScene == LEVEL_1)
	{
		if (direction == 0) // && enemyPhys->body->GetLinearVelocity().x == 0)
		{
			enemyVel = { 6, 0 };
			currentAnimation = &walkRight;
		}
		else if (direction == 1) // && enemyPhys->body->GetLinearVelocity().x == 0)
		{
			enemyVel = { -6, 0 };
			currentAnimation = &walkLeft;
		}
	}

	return true;
}


bool GroundEnemy::Update(float dt)
{
	if ((!isDead) && (enemyPhys != nullptr))
	{
		enemyPos = enemyPhys->body->GetPosition();
		enemyRect.x = METERS_TO_PIXELS(enemyPos.x) - 16;
		enemyRect.y = METERS_TO_PIXELS(enemyPos.y) - 16;

		enemyPhys->body->SetLinearVelocity(enemyVel);

		lastY = enemyRect.y;
	}	

	if (app->currentScene == LEVEL_1) currentAnimation->Update();

	return true;
}


bool GroundEnemy::PostUpdate()
{
	if (app->currentScene == LEVEL_1 && enemySprites != nullptr)
	{
		app->render->DrawTexture(enemySprites, enemyRect.x, enemyRect.y, &currentAnimation->GetCurrentFrame());
	}
	return true;
}

bool GroundEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}

void GroundEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else if ((bodyB->id == 1))
	{
		LOG("PLAYER KILLED BY WADDLE DEE");

	}
	else if ((bodyB->id == 0))
	{
		direction = !direction;
		//LOG("ENEMY COLLISION WITH WALL");
	}
	
}



