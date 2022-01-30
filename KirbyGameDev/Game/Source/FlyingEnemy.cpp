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
	name.Create("flying_enemy");
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
		deathSFX = app->audio->LoadFx("Assets/audio/fx/Enemy_Killed_SFX.wav");

		currentAnimation = &flyLeft;		
		direction = 1;

		if (app->scene->playSaved == 0) startPos = { 1845, 200, };

		enemyRect = { (int)startPos.x, (int)startPos.y, 32, 32 };

		b2Vec2 enemyPos = { 0, 0 };
		b2Vec2 enemyVel = { 0, 0 };

		LOG("Creating enemy hitbox");
		enemyPhys = app->physics->CreateCircle(enemyRect.x, enemyRect.y, 14, b2_dynamicBody);
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

		b2Vec2 impulse = {0.0f, -6.667f};

		if (enemyRect.y > 200 && !isDead) enemyPhys->body->SetLinearVelocity(impulse);
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
	if (isDead)
	{
		b2Vec2 deadPos = { 0, 0 };
		enemyPhys->body->SetTransform(deadPos, 0);
	}
	else if (app->currentScene == LEVEL_1 && enemySprites != nullptr && !isDead)
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
	else if (bodyB->id == 4)
	{
		isDead = true;
		app->audio->PlayFx(deathSFX);
	}
}

bool FlyingEnemy::LoadState(pugi::xml_node& data)
{
	if (data != NULL && app->currentScene == LEVEL_1)
	{
		LOG("loading flying enemy ");
		enemyPos.x = data.child("enemyPos").attribute("x").as_float(0);
		enemyPos.y = data.child("enemyPos").attribute("y").as_float(0);
		direction = data.child("enemyDir").attribute("value").as_bool();
		isDead = data.child("isDead").attribute("value").as_bool(0);

		if (startPos.x != NULL || startPos.y != NULL)
		{
			b2Vec2 newPos = { PIXEL_TO_METERS(startPos.x), PIXEL_TO_METERS(startPos.y) };

			enemyPhys->body->SetTransform(newPos, 0);
		}
	}

	return true;
}


bool FlyingEnemy::SaveState(pugi::xml_node& data) const
{
	if (app->currentScene == LEVEL_1)
	{
		LOG("saving flying enemy ");
		data.child("enemyPos").attribute("x").set_value(METERS_TO_PIXELS(enemyPhys->body->GetPosition().x));
		data.child("enemyPos").attribute("y").set_value(METERS_TO_PIXELS(enemyPhys->body->GetPosition().y));
		data.child("enemyDir").attribute("value").set_value(direction);
		data.child("isDead").attribute("value").set_value(isDead);

	}
	return true;
}
