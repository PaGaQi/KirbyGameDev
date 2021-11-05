#include "App.h"
#include "Player.h"
#include "Module.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Animation.h"
#include <Box2D/Box2D/Box2D.h>

Player::Player()
{
	isMoving = false;

	idle.PushBack({ 0, 0, 32, 32 });
	idle.PushBack({ 34, 0, 32, 32 });

	idle.loop = true;
	idle.speed = 0.1f;

	right.PushBack({ 0, 34, 32, 32 });
	right.PushBack({ 34, 34, 32, 32 });
	right.PushBack({ 68, 34, 32, 32 });
	right.PushBack({ 102, 34, 32, 32 });

	right.loop = true;
	right.speed = 0.1f;

	//Left movement not yet implemented :)
	left.PushBack({ 0, 34, 32, 32 });
	left.PushBack({ 34, 34, 32, 32 });
	left.PushBack({ 68, 34, 32, 32 });
	left.PushBack({ 102, 34, 32, 32 });

	left.loop = true;
	left.speed = 0.1f;

	jump.PushBack({ 40, 0, 19, 20 });
	jump.PushBack({ 40, 44, 19, 20 });
	jump.PushBack({ 40, 88, 19, 20 });
	jump.PushBack({ 40, 132, 19, 20 });

	left.loop = true;
	left.speed = 0.1f;

	playerRect = { 0, 0, 32, 32 };
	playerCrop = { 0, 0, 32, 32 };
}

Player::~Player()
{}

// Load assets
bool Player::Start()
{
	playerSprites = app->tex->Load("Output/Assets/textures/Kirby Spritesheet 32x32");

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
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerRect.x--;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		
	}
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	app->render->DrawTexture(playerSprites, playerRect.x, playerRect.y, &playerCrop);

	return true;
}

void Player::OnCollision(b2Body* bodyA, b2Body* bodyB)
{

}
