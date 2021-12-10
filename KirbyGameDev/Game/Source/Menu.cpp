#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Menu.h"
#include "Scene.h"
#include "Textures.h"

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
	return true;
}


bool Menu::Update(float dt) 
{	
	if (app->currentScene != LEVEL_1)
	{
		app->render->DrawTexture(menuBackground, 0, 0);

		if (titleMenu)currentAnimation->Update();
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


