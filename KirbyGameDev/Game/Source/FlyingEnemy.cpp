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
		enemyPhys = app->physics->CreateCircle(0, 45, 14, b2_dynamicBody);
		enemyPhys->id = 2;
		enemyPhys->listener = this;
	}

	return true;
}

bool FlyingEnemy::Update(float dt)
{
	if (lifes <= 0)
	{
		actualState = DEATHSS;
		isAlive = false;
	}

	if (isAlive == true)
	{

		/*if (METERS_TO_PIXELS(app->player->playerPhys()->body->GetPosition().x) > 832)
		{
			actualState = CHASIN_PLAYER;

			if (app->player->isAlive == false)
			{
				actualState = PATROLLIN;
			}
		}
		else
		{
			actualState = PATROLLIN;
		}*/
	}

	if (app->player->PlayerWin() == true)
	{
		actualState = PATROLLIN;
	}


	switch (actualState)
	{
	case CHASIN_PLAYER:
	{
		// chase the player

		// Make the pathfinding

		// advance one tile

		/*iPoint playerPos;
		if (app->currentScene = LEVEL_1)
		{ }
			app->player->playerPhys->GetPosition(playerPos.x, playerPos.y);

		enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

		playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);

		app->pathfinding->CreatePath(directionPoint, playerPos);

		iPoint NextPos;

		const DynArray<iPoint>* lastPath = app->pathfinding->GetLastPath();

		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}

		directionPoint = NextPos;

		/*if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(app->scene->pathfindingTex, pos.x, pos.y);
			}
		}*/


	}break;
	case PATROLLIN:
	{
		//  Maintain the position

		/*enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);


		iPoint playerPos;

		enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

		playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);

		app->pathfinding->CreatePath(directionPoint, { 27,11 });

		iPoint NextPos;

		const DynArray<iPoint>* lastPath = app->pathfinding->GetLastPath();

		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}

		directionPoint = NextPos;

		/*if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(app->scene->pathfindingTex, pos.x, pos.y);
			}
		}*/

	}break;
	case DEATHSS:
	{
		/*enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

		isAlive = false;
		deathAnimAllowed = true;
		enemyPhys->id = 0;*/

	}break;
	}





	// Enemy movement 

	if (isAlive == true)
	{
		switch (actualState)
		{
		case CHASIN_PLAYER:
		{
			// chase the player

			// Make the pathfinding

			// advance one tile

			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y - 1); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y); // pixels



			if (directionPoint.x < positionOfTheObject.x)
			{
				if (enemyPhys->body->GetLinearVelocity().x > -0.1f)
				{
					enemyPhys->body->ApplyLinearImpulse({ -0.1f,0.0f }, enemyPhys->body->GetPosition(), true);
				}

			}

			if (directionPoint.x > positionOfTheObject.x)
			{
				if (enemyPhys->body->GetLinearVelocity().x < 0.9f)
				{
					enemyPhys->body->ApplyLinearImpulse({ 0.1f,0.0f }, enemyPhys->body->GetPosition(), true);
				}
			}

			if (directionPoint.y + 25 < positionOfTheObject.y)
			{
				if (enemyPhys->body->GetLinearVelocity().y > -0.2f)
				{
					enemyPhys->body->ApplyLinearImpulse({ 0.0f,-0.1f }, enemyPhys->body->GetPosition(), true);
				}
			}

		}break;
		case PATROLLIN:
		{
			//  Maintain the position

			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y - 1); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			enemyPhys->GetPosition(positionOfTheObject.x, positionOfTheObject.y); // pixels



			if (directionPoint.x < positionOfTheObject.x)
			{
				if (enemyPhys->body->GetLinearVelocity().x > -0.1f)
				{
					enemyPhys->body->ApplyLinearImpulse({ -0.1f,0.0f }, enemyPhys->body->GetPosition(), true);
				}

			}

			if (directionPoint.x > positionOfTheObject.x)
			{
				if (enemyPhys->body->GetLinearVelocity().x < 0.1f)
				{
					enemyPhys->body->ApplyLinearImpulse({ 0.1f,0.0f }, enemyPhys->body->GetPosition(), true);
				}
			}

			if (directionPoint.y + 32 < positionOfTheObject.y)
			{
				if (enemyPhys->body->GetLinearVelocity().y > -0.2f)
				{
					enemyPhys->body->ApplyLinearImpulse({ 0.0f,-0.1f }, enemyPhys->body->GetPosition(), true);
				}
			}

			


		}break;
		case DEATHSS:
		{


		}break;
		}
	}

	switch (actualState)
	{
	case PATROLLIN:
	{
		statesInt = 0;
	}break;
	case CHASIN_PLAYER:
	{
		statesInt = 1;
	}break;
	case DEATHSS:
	{
		statesInt = 2;
	}
	}

	direction = 0;
	if (direction == 0)
	{
		//currentAnimation = &rightIdleAnim;
	}

	//currentAnimation->Update();

	return true;

}

bool FlyingEnemy::PostUpdate()
{
	//app->render->DrawTexture(texture, positionOfTheObject.x - 5, positionOfTheObject.y, &currentAnimation->GetCurrentFrame());




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



void FlyingEnemy::SetEnemyState(FLYING_ENEMY_STATE state)
{
	actualState = state;
}

bool FlyingEnemy::LoadState(pugi::xml_node& data)
{
	b2Vec2 v = { PIXEL_TO_METERS(data.child("Pos").attribute("x").as_float()), PIXEL_TO_METERS(data.child("Pos").attribute("y").as_float()) };

	lifes = data.child("lifes").attribute("value").as_int();
	isAlive = data.child("isAlive").attribute("value").as_bool();
	deathAnimAllowed = data.child("deathAnimation").attribute("value").as_bool();
	statesInt = data.child("deathAnimation").attribute("value").as_int();

	switch (statesInt)
	{
	case 0:
	{
		actualState = PATROLLIN;
	}break;
	case 1:
	{
		actualState = CHASIN_PLAYER;
	}break;
	case 2:
	{
		actualState = DEATHSS;
	}
	}

	enemyPhys->body->SetTransform(v, 0);

	return true;
}

bool FlyingEnemy::SaveState(pugi::xml_node& data) const
{
	LOG("saving enemy ");

	data.child("Pos").attribute("x").set_value(positionOfTheObject.x);
	data.child("Pos").attribute("y").set_value(positionOfTheObject.y);
	data.child("lifes").attribute("value").set_value(lifes);
	data.child("isAlive").attribute("value").set_value(isAlive);
	data.child("deathAnimation").attribute("value").set_value(deathAnimAllowed);
	data.child("state").attribute("value").set_value(statesInt);



	return true;
}

void FlyingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 5) && (bodyB->id == 7))
		{



			if (lifes > 0)
			{


				lifes--;


				app->audio->PlayFx(app->scene->enemyhit_fx);
			}
			else
			{
				app->audio->PlayFx(app->scene->enemydeath_fx);
			}

		}
	}
}