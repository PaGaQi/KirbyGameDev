#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Menu.h"
#include "Scene.h"
#include "Textures.h"
#include "Player.h"
#include "Input.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"
#include "Point.h"


Menu::Menu() 
{
	
	//Menu Animations----------------------------
	welcomeKirby.PushBack({ 0, 0, 248, 220 });
	welcomeKirby.PushBack({ 252, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });
	welcomeKirby.PushBack({ 0, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });
	welcomeKirby.PushBack({ 0, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });
	welcomeKirby.PushBack({ 0, 0, 248, 220 });
	welcomeKirby.PushBack({ 504, 0, 248, 220 });

	welcomeKirby.loop = true;
	welcomeKirby.speed = 0.2f;

	//HUD Animations-----------------------------

	abilityNormal.PushBack({ 0, 0, 128, 160 });
	abilityHit.PushBack({ 132, 0, 128, 160 });
	abilityLose.PushBack({ 264, 0, 128, 160 });
	abilityWin.PushBack({ 396, 0, 128, 160 });



	titleKirby = { SCREEN_WIDTH / 2 - 124, SCREEN_HEIGHT / 2 - 110, 248, 220 };
	
	baseHUDRect = { 0, 0, 1024, 256 };
	abilityHUDRect = { 0, 0, 128, 220 };
	mouseRect = { 0, 0, 16, 24 };

	menuHandRect = {0, 0, 64, 64};
	menuHandCrop = {0, 80, 64, 64};

	currentButton = 0;
	previousButton = 0;

	saveDataAvailable = 0;

}

	// Destructor
Menu:: ~Menu() {}

	// Called before render is available	
bool Menu::Awake() 
{
	return true;
}


bool Menu::Start() 
{
	//HUD Elements
	baseHUD = app->tex->Load("Assets/textures/HUD Base.png");
	abilityHUD = app->tex->Load("Assets/textures/HUD Sprites.png");

	moveMouse = app->audio->LoadFx("Assets/audio/fx/2C - Moving Cursor Sound.wav");
	
	menuHandTexture = app->tex->Load("Assets/maps/UI Elements.png");

	switch (app->currentScene)
	{
		case (TITLE):
		{
			LOG("Loading Title Animation");

			menuKirby = app->tex->Load("Assets/textures/TitleAnimation.png");
			menuBackground = app->tex->Load("Assets/maps/TitleScreenVer2.png");
			titleMenu = true;
			return true;
		}
		break;

		case (MENU):
		{
			if (!saveDataAvailable) menuBackground = app->tex->Load("Assets/maps/Main Menu (No SaveData) Ver2.png");
			else menuBackground = app->tex->Load("Assets/maps/Main Menu Ver2.png");
			titleMenu = false;

			optionSelected[0] = { 268, 204 };
			optionSelected[1] = { 300, 268 };
			optionSelected[2] = { 300, 332 };
			optionSelected[3] = { 320, 396 };
			optionSelected[4] = { 360, 460 };

			return true;
		}
		break;

		case (DEATH):
		{
			LOG("Loading Death Menu");
			
			menuBackground = app->tex->Load("Assets/maps/DeathScreen.png");
			
			app->render->camera.x = 0;

			titleMenu = false;		
			return true;
		}
		break;

		case (LEVEL_1):
		{
			LOG("Loading Player HUD");				
			baseHUD = app->tex->Load("Assets/textures/HUD Base.png");
			abilityHUD = app->tex->Load("Assets/textures/HUD Sprites.png");

			app->render->camera.x = 0;

			titleMenu = false;
			return true;
		}
		break;
	}
}


bool Menu::PreUpdate() 
{
	if (titleMenu) currentAnimation = &welcomeKirby;
	if (app->currentScene == LEVEL_1)
	{
		if (app->player->isDead == false)
		{
			currentAnimation = &abilityNormal;
		}
		else //if (app->player->isDead == true)
		{
			currentAnimation = &abilityLose;
		}
	}

	if (app->currentScene == MENU)
	{
		SDL_GetMouseState(&mouseRect.x, &mouseRect.y);
		
		if (mouseRect.y <= 270 ) currentButton = 0;
		else if (mouseRect.y > 270 && mouseRect.y < 334 && saveDataAvailable) currentButton = 1;
		else if (mouseRect.y >= 334 && mouseRect.y < 398) currentButton = 2;
		else if (mouseRect.y >= 398 && mouseRect.y < 462) currentButton = 3;
		else if (mouseRect.y >= 462) currentButton = 4;

	}

	return true;
}


bool Menu::Update(float dt) 
{	
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) saveDataAvailable = 1;

	if (app->currentScene != LEVEL_1)
	{
		app->render->DrawTexture(menuBackground, 0, 0);

		if (titleMenu)currentAnimation->Update();
	}

	if (app->currentScene == MENU)
	{
		//app->render->DrawRectangle(mouseRect, 0, 0, 255);
		app->render->DrawTexture(menuHandTexture, menuHandRect.x, menuHandRect.y, &menuHandCrop);

		menuHandRect.x = optionSelected[currentButton].x;
		menuHandRect.y = optionSelected[currentButton].y;	

		if (currentButton != previousButton) app->audio->PlayFx(moveMouse);

		previousButton = currentButton;
	}

	return true;
}


bool Menu::PostUpdate() 
{
	if (titleMenu) app->render->DrawTexture(menuKirby, titleKirby.x, titleKirby.y, &currentAnimation->GetCurrentFrame());
	
	if (app->currentScene == LEVEL_1) 
	{		
		app->render->DrawTexture(baseHUD, -(app->render->camera.x), 704, &baseHUDRect);
		app->render->DrawTexture(abilityHUD, 592 -(app->render->camera.x), 736, &currentAnimation->GetCurrentFrame());
		currentAnimation->Update();
	}

	return true;
}


bool Menu::CleanUp() 
{	
	switch (app->currentScene)
	{
		case (DEATH):
		{
			app->tex->UnLoad(baseHUD);
			app->tex->UnLoad(abilityHUD);
			return true;
		}
		break;

		case (LEVEL_1):
		{
			app->tex->UnLoad(menuBackground);
			return true;
		}
		break;
	}

	return true;
}


