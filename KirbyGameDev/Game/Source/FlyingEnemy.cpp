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
	//ANIMATIONS

	////Left Fly Animation---------------------------
	flyLeft.PushBack({ 0, 68, 32, 32 });
	flyLeft.PushBack({ 34, 68, 32, 32 });

	flyLeft.loop = true;
	flyLeft.speed = 0.2f;

	////Right Walk Animation---------------------------
	flyRight.PushBack({ 0, 102, 32, 32 });
	flyRight.PushBack({ 34, 102, 32, 32 });


	flyRight.loop = true;
	flyRight.speed = 0.2f;
}

FlyingEnemy::~FlyingEnemy()
{

}

bool FlyingEnemy::Start()
{
	if (app->currentScene == LEVEL_1)
	{
		LOG("Loading ground enemy");
		enemySprites = app->tex->Load("Assets/textures/EnemySpritesheet.png");

		currentAnimation = &flyLeft;		
		direction = 1;

		enemyRect = { 1845, 200, 32, 32 };
		b2Vec2 enemyPos = { 0, 0 };
		b2Vec2 enemyVel = { 0, 0 };

		LOG("Creating enemy hitbox");
		enemyPhys = app->physics->CreateCircle(1845, 200, 14, b2_kinematicBody);
		enemyPhys->id = 2;
		enemyPhys->listener = this;	

		isDead = false;
	}

	return true;
}

bool FlyingEnemy::PreUpdate()
{
	if (app->currentScene == LEVEL_1)
	{
		if (direction == 0)
		{
			currentAnimation = &flyRight;
		}
		else if (direction == 1)
		{
			currentAnimation = &flyLeft;
		}
	}
	return true;
}

bool FlyingEnemy::Update(float dt)
{
	if (!isDead && enemyPhys != nullptr)
	{
		enemyPos = enemyPhys->body->GetPosition();
		enemyRect.x = METERS_TO_PIXELS(enemyPos.x) - 16;
		enemyRect.y = METERS_TO_PIXELS(enemyPos.y) - 16;	
	}

	if (app->currentScene == LEVEL_1) currentAnimation->Update();
	

	return true;
}
	



bool FlyingEnemy::PostUpdate()
{
	if (app->currentScene == LEVEL_1 && enemySprites != nullptr)
	{
		app->render->DrawTexture(enemySprites, enemyRect.x, enemyRect.y, &currentAnimation->GetCurrentFrame());
	}

	return true;
}

bool FlyingEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}


void FlyingEnemy::SetEnemyState(FLYING_ENEMY_STATE state)
{
	actualState = state;
}


void FlyingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else if (bodyB->id == 1)
	{
		LOG("FLYING ENEMY KILLED PLAYER");
	}
}