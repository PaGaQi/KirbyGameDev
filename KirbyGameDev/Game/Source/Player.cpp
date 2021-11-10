#include "App.h"
#include "Audio.h"
#include "Player.h"
#include "Module.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Animation.h"
#include <Box2D/Box2D/Box2D.h>
#include "Physics.h"
#include "Log.h"


Player::Player()
{
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
	//jumpRight.PushBack({ 34, 68, 32, 32 });
	//jumpRight.PushBack({ 68, 68, 32, 32 });
	//jumpRight.PushBack({ 102, 68, 32, 32 });
	//jumpRight.PushBack({ 136, 68, 32, 32 });


	jumpRight.loop = true;
	jumpRight.speed = 0.1f;

	//Left Jump Animation---------------------------
	jumpLeft.PushBack({ 0, 170, 32, 32 });
	//jumpLeft.PushBack({ 34, 170, 32, 32 });
	//jumpLeft.PushBack({ 68, 170, 32, 32 });
	//jumpLeft.PushBack({ 102, 170, 32, 32 });
	//jumpLeft.PushBack({ 136, 170, 32, 32 });

	jumpLeft.loop = true;
	jumpLeft.speed = 0.1f;

	//Left Fall Animation
	fallLeft.PushBack({ 136, 170, 32, 32 });
	
	//Death Animation-------------------------------
	death.PushBack({ 0, 204, 32, 32 });
	death.PushBack({ 34, 204, 32, 32 });
	death.PushBack({ 68, 204, 32, 32 });
	death.PushBack({ 102, 204, 32, 32 });

	death.loop = true;
	death.speed = 0.1f;
	
	deadDirection = 1;

	playerRect = { 0, 320, 32, 32 };
	playerPhys;

	lastY;
}

Player::~Player() {}

// Load assets
bool Player::Start()
{
	if (app->currentScene == LEVEL_1) 
	{		
		LOG("Loading player sprites");
		playerSprites = app->tex->Load("Assets/textures/KirbyFullSpritesheet.png");
		
		direction = 0;	
		lastY = 480;

		playerRect = { 0, 320, 32, 32 };
		b2Vec2 playerPos = { 0, 0 };
		b2Vec2 playerVel = { 0, 0 };

		LOG("Creating player hitbox");
		playerPhys = app->physics->CreateCircle(32, 320, 14, b2_dynamicBody);

		jumpSFX = app->audio->LoadFx("Assets/audio/fx/jump.wav");
		deathSFX = app->audio->LoadFx("Assets/audio/fx/death_Kirb.wav");
		isDead = false;
	}		

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (isDead == 1)													//Death Animation
	{
		currentAnimation = &death;		

		if ((playerRect.y >= (lastY - 128)) && (deadDirection == 1)) playerRect.y -= 2;
		if ((playerRect.y <= lastY - 128) && (deadDirection == 1)) deadDirection = 0;
		if (deadDirection == 0) playerRect.y += 2;

		if ((playerRect.y >= 483) && (app->currentScene == LEVEL_1))
		{
			app->ChangeScene(DEATH);
			playerRect.y = 0;
		}
	}	
	
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)			//Walking Right
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


	if (godMode == true)												//GOD MODE
	{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) playerRect.y -= 8;		
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) playerRect.y += 8;		
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
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) godMode = !godMode;

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	
	if ((playerRect.x > 254) && (playerRect.x < 1280) && (app->currentScene == LEVEL_1))
	{
		app->render->camera.x = 256 - playerRect.x;  //The right camera limit is the level width - 256
	}

	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) isDead = !isDead;

	if ((playerRect.y >= 481) && (!isDead))
	{
		isDead = true;
		app->audio->PlayFx(deathSFX);
		deadDirection = 1;
	}

	app->render->DrawTexture(playerSprites, playerRect.x, playerRect.y, &currentAnimation->GetCurrentFrame());
	return true;
}

void Player::OnCollision(b2Body* bodyA, b2Body* bodyB)
{
	LOG("SOMETHING IS COLLIDING");

	if ((bodyA == playerPhys->body) && (bodyB->GetType() == b2_staticBody)) 
		LOG("PLAYER IS COLLIDING");
}

bool Player::CleanUp()
{
	app->tex->UnLoad(playerSprites);
	
	return true;
}