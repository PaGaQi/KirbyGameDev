#include "App.h"
#include "Audio.h"
#include "Player.h"
#include "Module.h"
#include "Map.h"
#include "Menu.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Animation.h"
#include "Physics.h"
#include "Log.h"

#include <iostream>
#include <sstream>

#include "Scene.h"

Player::Player()
{
	name.Create("player");

	isMoving = false;

	//Right Idle Animation---------------------------
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 34, 0, 32, 32 });
	idleRight.PushBack({ 0, 0, 32, 32 });
	idleRight.PushBack({ 34, 0, 32, 32 });

	idleRight.loop = true;
	idleRight.speed = 0.2f;

	//Left Idle Animation-------------------------- -
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 34, 102, 32, 32 });
	idleLeft.PushBack({ 0, 102, 32, 32 });
	idleLeft.PushBack({ 34, 102, 32, 32 });

	idleLeft.loop = true;
	idleLeft.speed = 0.2f;

	//Right Walk Animation---------------------------
	walkRight.PushBack({ 0, 34, 32, 32 });
	walkRight.PushBack({ 34, 34, 32, 32 });
	walkRight.PushBack({ 68, 34, 32, 32 });
	walkRight.PushBack({ 102, 34, 32, 32 });

	walkRight.loop = true;
	walkRight.speed = 0.2f;

	////Left Walk Animation---------------------------
	walkLeft.PushBack({ 0, 136, 32, 32 });
	walkLeft.PushBack({ 34, 136, 32, 32 });
	walkLeft.PushBack({ 68, 136, 32, 32 });
	walkLeft.PushBack({ 102, 136, 32, 32 });

	walkLeft.loop = true;
	walkLeft.speed = 0.2f;

	//Right Jump Animation---------------------------

	jumpRight.PushBack({ 0, 68, 32, 32 });

	jumpRight.loop = true;
	jumpRight.speed = 0.1f;

	//Left Jump Animation---------------------------
	jumpLeft.PushBack({ 0, 170, 32, 32 });

	jumpLeft.loop = true;
	jumpLeft.speed = 0.1f;

	//Death Animation-------------------------------
	death.PushBack({ 0, 204, 32, 32 });
	death.PushBack({ 34, 204, 32, 32 });
	death.PushBack({ 68, 204, 32, 32 });
	death.PushBack({ 102, 204, 32, 32 });

	death.loop = true;
	death.speed = 0.1f;

	deadDirection = 1;

	playerRect = { 0, 320, 32, 32 };

	lastY;

	startPos = { 32, 576 };
	startAttackPos = {-100, 0 };
	
	collectibleGet;

	paused = 0;

	health = 110;
	timer = 300.0f;
}

Player::~Player() {};

bool Player::Awake(pugi::xml_node&)
{	
	return true;
}

// Load assets
bool Player::Start()
{
	if (app->currentScene == LEVEL_1) 
	{		
		LOG("Loading player sprites");
		playerSprites = app->tex->Load("Assets/textures/KirbyFullSpritesheet.png");
		attackText = app->tex->Load("Assets/textures/Attack.png");
		
		lastY = 704;

		playerRect = { (int)startPos.x, (int)startPos.y, 32, 32 };
		b2Vec2 playerPos = { 0, 0 };
		b2Vec2 playerVel = { 0, 0 };

		attackRect = { (int)startAttackPos.x, (int)startAttackPos.y, 32, 32 };
		attackCrop = { 0, 0, 32, 32 };

		LOG("Creating player hitbox");
		playerPhys = app->physics->CreateCircle((float)startPos.x, (float)startPos.y, 14, b2_dynamicBody);
		playerPhys->id = 1;
		playerPhys->listener = this;

		jumpSFX = app->audio->LoadFx("Assets/audio/fx/jump.wav");
		deathSFX = app->audio->LoadFx("Assets/audio/fx/death_Kirb.wav");
		hitSFX = app->audio->LoadFx("Assets/audio/fx/Hit SFX.wav");
		collSFX = app->audio->LoadFx("Assets/audio/fx/Collectible Sound.wav");
		
		b2Vec2 attackPos = { playerPos.x + PIXEL_TO_METERS(32), playerPos.y };
		b2Vec2 attackVel = playerVel;

		attackPhys = app->physics->CreateCircle(METERS_TO_PIXELS(attackPos.x + 32), METERS_TO_PIXELS(attackPos.y), 14, b2_kinematicBody);
		attackPhys->id = 4;
		attackPhys->listener = this;

		paused = 0;

		if (app->scene->playSaved == 0)
		{
			startPos = { 32, 576 };
			startAttackPos = {-100, -100 };
			collectibleGet = false;
			direction = 0;
			health = 110;
			timer = 300;

			b2Vec2 newPos = { PIXEL_TO_METERS(startPos.x), PIXEL_TO_METERS(startPos.y) };
			b2Vec2 newAttackPos = { PIXEL_TO_METERS(startAttackPos.x), PIXEL_TO_METERS(startAttackPos.y) };

			playerPhys->body->SetTransform(newPos, 0);
			attackPhys->body->SetTransform(newAttackPos, 0);

			app->render->camera.x = 0;
		}
		else
		{
			app->LoadGameRequest();
			isDead = false;
		}

		isDead = false;
	}	

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (!paused) app->SaveGameRequest();

		paused = !paused;
	}
	else if (!paused)
	{
	if (isDead == 1)													//Death Animation
	{
		currentAnimation = &death;		

		if ((playerRect.y >= (lastY - 128)) && (deadDirection == 1))
		{
			playerRect.y -= 4;			
		}

		if ((playerRect.y <= lastY - 128) && (deadDirection == 1))
		{
			deadDirection = 0;
			deathHeight = playerRect.y;
		}

		if (deadDirection == 0)
		{
			//LOG("DEATH AT %i", deathHeight);
			playerRect.y += 4 * (625 - deathHeight) / 80;
			//LOG("POS = %i", playerRect.y);
		}

		if ((playerRect.y >= 708) && (app->currentScene == LEVEL_1))
		{
			app->ChangeScene(DEATH);
			playerRect.y = 0;
		}
	}	
	
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)				//Walking Right
		{
			playerVel = { 6, 0 };
			direction = 0;
			playerRect.x += 8;
			currentAnimation = &walkRight;
		}

		else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)			//Walking Left
		{
			playerVel = { -6, 0 };
			direction = 1;
			playerRect.x -= 8;
			currentAnimation = &walkLeft;
		}

		else																//IDLE ANIMATIONS
		{
			playerVel = { 0, 0 };

			//if (playerVel.y > 0) currentAnimation = &fallLeft;
			if (direction == 0)currentAnimation = &idleRight;
			else if (direction == 1) currentAnimation = &idleLeft;
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)				//JUMPING ANIMATIONS
		{
			app->audio->PlayFx(jumpSFX);
			playerVel.y = -40;
			if (direction == 0) currentAnimation = &jumpRight;
			else if (direction == 1) currentAnimation = &jumpLeft;
		}

		else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			playerVel.y = -15;
			if (direction == 0) currentAnimation = &jumpRight;
			else if (direction == 1) currentAnimation = &jumpLeft;
		}
		else if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		{
			timer = 30;
		}

		if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{
			b2Vec2 attackPos = { 0, 0 };
			if (direction == 0) attackPos = { playerPos.x + PIXEL_TO_METERS(32), playerPos.y };
			else attackPos = { playerPos.x + PIXEL_TO_METERS(-32), playerPos.y };
			b2Vec2 attackVel = playerVel;
			
			attackPhys->body->SetTransform(attackPos, 0);
			attackPhys->body->SetLinearVelocity(attackVel);
		
		}		

		if (godMode == true)												//GOD MODE
		{
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) playerRect.y -= 8;
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) playerRect.y += 8;
		}
	}
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{
	if ((!godMode) && (!isDead) && (playerPhys != nullptr))
	{
		playerPos = playerPhys->body->GetPosition();
		playerRect.x = METERS_TO_PIXELS(playerPos.x) - 16;
		playerRect.y = METERS_TO_PIXELS(playerPos.y) - 16;
		
		playerPhys->body->SetLinearVelocity(playerVel);

		lastY = playerRect.y;

		attackRect.x = METERS_TO_PIXELS(attackPhys->body->GetPosition().x) - 16;
		attackRect.y = METERS_TO_PIXELS(attackPhys->body->GetPosition().y) - 16;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) godMode = !godMode;

	if ((app->currentScene == LEVEL_1))
	{
		if (timer >= 0) timer -= dt;
		else if (timer <= 0 && !isDead)
		{
			timer = 0;
			health = 0;
		}
	}

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{	
	if ((playerRect.x > SCREEN_WIDTH / 2 - 2) && (playerRect.x < SCREEN_WIDTH * 2.5 + 2) && (app->currentScene == LEVEL_1))
	{
		app->render->camera.x = (SCREEN_WIDTH / 2) - playerRect.x;  //The right camera limit is the level width - HALF THE SCREEN WIDTH
	}
	else if (playerRect.x <= SCREEN_WIDTH) app->render->camera.x = 0;

	if ((playerRect.y >= 705 || health <= 0) && (!isDead))
	{
		health = 0;
		isDead = true;
		app->audio->PlayFx(deathSFX);
		deadDirection = 1;
	}

	if (app->currentScene == LEVEL_1)
	{
		app->render->DrawTexture(playerSprites, playerRect.x, playerRect.y, &currentAnimation->GetCurrentFrame());

		app->render->DrawTexture(attackText, attackRect.x, attackRect.y, &attackCrop);
	}
	
	return true;
}

bool Player::PlayerWin()
{
	return win;
}

bool Player::LoadState(pugi::xml_node& data)
{
	if (data != NULL && app->currentScene == LEVEL_1)
	{
		LOG("loading player ");
		startPos.x = data.child("playerPos").attribute("x").as_float(0);
		startPos.y = data.child("playerPos").attribute("y").as_float(0);
		collectibleGet = data.child("collectibleGet").attribute("value").as_bool();
		direction = data.child("playerDir").attribute("value").as_bool();
		health = data.child("health").attribute("value").as_int(100);
		isDead = data.child("isDead").attribute("value").as_bool(0);
		timer = data.child("timer").attribute("value").as_float(300.0f);
		startAttackPos.x = data.child("attackPos").attribute("x").as_float(0.0f);
		startAttackPos.y = data.child("attackPos").attribute("y").as_float(0.0f);

		if (startAttackPos.x != NULL || startAttackPos.y != NULL)
		{
			b2Vec2 newAttackPos = { PIXEL_TO_METERS(startAttackPos.x), PIXEL_TO_METERS(startAttackPos.y) };
			attackPhys->body->SetTransform(newAttackPos, 0);
		}

		if (startPos.x != NULL || startPos.y != NULL)
		{
			b2Vec2 newPos = { PIXEL_TO_METERS(startPos.x), PIXEL_TO_METERS(startPos.y) };

			playerPhys->body->SetTransform(newPos, 0);
		}		
	}

	return true;
}


bool Player::SaveState(pugi::xml_node& data) const
{
	if(playerPhys == NULL) app->menu->saveDataAvailable = false;
	else if (app->currentScene == LEVEL_1)
	{
		LOG("saving player ");
		data.child("playerPos").attribute("x").set_value(METERS_TO_PIXELS(playerPhys->body->GetPosition().x));
		data.child("playerPos").attribute("y").set_value(METERS_TO_PIXELS(playerPhys->body->GetPosition().y));
		data.child("collectibleGet").attribute("value").set_value(collectibleGet);
		data.child("playerDir").attribute("value").set_value(direction);
		data.child("health").attribute("value").set_value(health);
		data.child("timer").attribute("value").set_value(timer);
		data.child("attackPos").attribute("x").set_value(METERS_TO_PIXELS(attackPhys->body->GetPosition().x));
		data.child("attackPos").attribute("y").set_value(METERS_TO_PIXELS(attackPhys->body->GetPosition().y));

		if (!paused) app->menu->saveDataAvailable = true;
	}
	return true;
}

void Player::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (app->currentScene == LEVEL_1)
	{
		//LOG("%i, %i", METERS_TO_PIXELS(playerPhys->body->GetPosition().x), METERS_TO_PIXELS(playerPhys->body->GetPosition().y));
		if (bodyA == playerPhys)
		{
			if (bodyB == nullptr) {}
			else if (bodyB->id == 2 && isDead == false)
			{
				health -= 28;
				app->audio->PlayFx(hitSFX);
			}
			else if (bodyB->id == 3)
			{
				if (collectibleGet == false) app->audio->PlayFx(collSFX);
				collectibleGet = true;
			}
		}

		if (bodyA->id == 4 && attackPhys->body != NULL)
		{		
		}
	}
}

bool Player::CleanUp()
{
	//app->tex->UnLoad(playerSprites);
	
	return true;
}