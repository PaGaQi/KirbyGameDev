#include "App.h"
#include "Player.h"
#include "Module.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Animation.h"
#include <Box2D/Box2D/Box2D.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

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
	idleRight.speed = 0.005f;

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
	idleLeft.speed = 0.005f;

	//Right Walk Animation---------------------------
	walkRight.PushBack({ 0, 34, 32, 32 });
	walkRight.PushBack({ 34, 34, 32, 32 });
	walkRight.PushBack({ 68, 34, 32, 32 });
	walkRight.PushBack({ 102, 34, 32, 32 });

	walkRight.loop = true;
	walkRight.speed = 0.009f;

	////Left Walk Animation---------------------------
	walkLeft.PushBack({ 0, 136, 32, 32 });
	walkLeft.PushBack({ 34, 136, 32, 32 });
	walkLeft.PushBack({ 68, 136, 32, 32 });
	walkLeft.PushBack({ 102, 136, 32, 32 });

	walkLeft.loop = true;
	walkLeft.speed = 0.009f;

	//Right Jump Animation---------------------------
	jumpRight.PushBack({ 0, 170, 32, 32 });
	jumpRight.PushBack({ 34, 170, 32, 32 });
	jumpRight.PushBack({ 68, 170, 32, 32 });
	jumpRight.PushBack({ 102, 170, 32, 32 });

	jumpRight.loop = true;
	jumpRight.speed = 0.1f;

	//Left Jump Animation---------------------------
	jumpLeft.PushBack({ 0, 170, 32, 32 });
	jumpLeft.PushBack({ 34, 170, 32, 32 });
	jumpLeft.PushBack({ 68, 170, 32, 32 });
	jumpLeft.PushBack({ 102, 170, 32, 32 });

	jumpLeft.loop = true;
	jumpLeft.speed = 0.1f;

	//Death Animation-------------------------------
	death.PushBack({ 0, 204, 32, 32 });
	death.PushBack({ 34, 204, 32, 32 });
	death.PushBack({ 68, 204, 32, 32 });
	death.PushBack({ 102, 204, 32, 32 });

	jumpLeft.loop = true;
	jumpLeft.speed = 0.1f;

	playerRect = { 0, 320, 32, 32 };
	playerCrop = { 0, 0, 32, 32 };
}

Player::~Player()
{}

// Load assets
bool Player::Start()
{
	//LOG("Loading player textures");

	playerSprites = app->tex->Load("Assets/textures/KirbyFullSpritesheet.png");

	direction = 0;

	return true;
}


// Unload assets
bool Player::CleanUp()
{
	
	
	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerRect.x++;
		direction = 0;
		currentAnimation = &walkRight;

	}

	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerRect.x--;
		direction = 1;
		currentAnimation = &walkLeft;
	}
	else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		playerRect.y--;
		direction = 1;
		currentAnimation = &jumpLeft;
		


	}
	
	else if (direction == 0)
	{
		currentAnimation = &idleRight;
	}
	else if (direction == 1)
	{
		currentAnimation = &idleLeft;
	}
	

	if (godMode == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			playerRect.y--;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			playerRect.y++;
		}
	}
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (!godMode) godMode = 1;
		else godMode = 0;
	}

	


	currentAnimation->Update();


	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (!isDead) isDead = 1;
		else isDead = 0;
	}
	app->render->DrawTexture(playerSprites, playerRect.x, playerRect.y, &currentAnimation->GetCurrentFrame());
	return true;
}

void Player::OnCollision(b2Body* bodyA, b2Body* bodyB)
{

}
