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
	name.Create("ground_enemy");
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

		deathSFX = app->audio->LoadFx("Assets/audio/fx/Enemy_Killed_SFX.wav");
		currentAnimation = &walkRight;	
		direction = 0;					
		
		if (app->scene->playSaved == 0) startPos = { 2050, 436 };

		enemyRect = { (int)startPos.x, (int)startPos.y, 32, 32 };

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
	if (enemyPhys != nullptr)
	{
		if (app->currentScene == LEVEL_1 && app->player->paused == false)
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
		else enemyVel = { 0 , 0 };
	}

	return true;
}


bool GroundEnemy::Update(float dt)
{
	if (enemyPhys != nullptr)
	{
		if (isDead)
		{
			b2Vec2 deadPos = { 0, 0 };
			enemyPhys->body->SetTransform(deadPos, 0);
		}
		else if ((!isDead) && (enemyPhys != nullptr) && (app->player->paused == false))
		{
			enemyPos = enemyPhys->body->GetPosition();
			enemyRect.x = METERS_TO_PIXELS(enemyPos.x) - 16;
			enemyRect.y = METERS_TO_PIXELS(enemyPos.y) - 16;

			enemyPhys->body->SetLinearVelocity(enemyVel);

			lastY = enemyRect.y;
		}
		else if (app->player->paused == true && (enemyPhys != nullptr)) enemyPhys->body->SetLinearVelocity({ 0, 0 });

		if (app->currentScene == LEVEL_1) currentAnimation->Update();
	}

	return true;
}


bool GroundEnemy::PostUpdate()
{
	
	if (app->currentScene == LEVEL_1 && enemySprites != nullptr && !app->player->paused && enemyPhys != nullptr && !isDead)
	{
		app->render->DrawTexture(enemySprites, enemyRect.x, enemyRect.y, &currentAnimation->GetCurrentFrame());
	}
	
	return true;
}

bool GroundEnemy::CleanUp()
{
	LOG("Unloading Enemy");
	app->tex->UnLoad(enemySprites);
	return true;
}

void GroundEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
{}
	else if ((bodyB->id == 1))
	{
		direction = !direction;		
	}
	else if ((bodyB->id == 0))
	{
		direction = !direction;
		//LOG("ENEMY COLLISION WITH WALL");
	}	
	else if (bodyB->id == 4)
	{
		isDead = true;
		app->audio->PlayFx(deathSFX);
	}	
}

bool GroundEnemy::LoadState(pugi::xml_node& data)
{
	if (data != NULL && app->currentScene == LEVEL_1)
	{
		LOG("loading ground enemy ");
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


bool GroundEnemy::SaveState(pugi::xml_node& data) const
{
	if (app->currentScene == LEVEL_1)
	{
		LOG("saving ground enemy ");
		data.child("enemyPos").attribute("x").set_value(METERS_TO_PIXELS(enemyPhys->body->GetPosition().x));
		data.child("enemyPos").attribute("y").set_value(METERS_TO_PIXELS(enemyPhys->body->GetPosition().y));
		data.child("enemyDir").attribute("value").set_value(direction);
		data.child("isDead").attribute("value").set_value(isDead);
		
	}
	return true;
}


