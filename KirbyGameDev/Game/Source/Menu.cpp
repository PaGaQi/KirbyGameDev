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
	//Menu Animations---------------------------
	welcomeKirby.PushBack({ 0, 0, 124, 110 });
	welcomeKirby.PushBack({ 126, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });
	welcomeKirby.PushBack({ 0, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });
	welcomeKirby.PushBack({ 0, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });
	welcomeKirby.PushBack({ 0, 0, 124, 110 });
	welcomeKirby.PushBack({ 252, 0, 124, 110 });

	welcomeKirby.loop = true;
	welcomeKirby.speed = 0.2f;

	titleKirby = { SCREEN_WIDTH / 2 - 62, SCREEN_HEIGHT / 2 - 55, 124, 110 };

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
			LOG("Loading Menu Animation");

			menuKirby = app->tex->Load("Assets/textures/TitleAnimation.png");
			menuBackground = app->tex->Load("Assets/maps/TitleScreenVer2.png");
			titleMenu = true;
		}
		break;

		case (DEATH):
		{
			app->tex->UnLoad(menuBackground);
			menuBackground = app->tex->Load("Assets/maps/DeathScreen.png");
			titleMenu = false;
		}
		break;
	}
	return true;
}


bool Menu::PreUpdate() 
{
	if (titleMenu) currentAnimation = &welcomeKirby;
	return true;
}


bool Menu::Update(float dt) 
{
	app->render->DrawTexture(menuBackground, 0, 0);
	
	if (titleMenu) currentAnimation->Update();
	
	return true;
}


bool Menu::PostUpdate() 
{
	if (titleMenu) app->render->DrawTexture(menuKirby, titleKirby.x, titleKirby.y, &currentAnimation->GetCurrentFrame());

	return true;
}


bool Menu::CleanUp() 
{	
	app->tex->UnLoad(menuKirby);
	app->tex->UnLoad(menuBackground);	
	
	return true;
}


