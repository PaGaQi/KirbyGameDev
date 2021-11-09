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
	shitRect = { 10, 10, SCREEN_WIDTH, SCREEN_HEIGHT };

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
			titleShit = app->tex->Load("Assets/maps/Shit.png");
		}
		break;
		case (DEATH):
		{

		}
		break;
	}
	return true;
}


bool Menu::PreUpdate() 
{
	currentAnimation = &welcomeKirby;
	return true;
}


bool Menu::Update(float dt) 
{
	currentAnimation->Update();
	return true;
}


bool Menu::PostUpdate() 
{
	app->render->DrawTexture(menuKirby, titleKirby.x, titleKirby.y, &currentAnimation->GetCurrentFrame());
	app->render->DrawTexture(titleShit, shitRect.x, shitRect.y, &shitRect);
	return true;
}


bool Menu::CleanUp() 
{
	app->tex->UnLoad(menuKirby);
	app->tex->UnLoad(titleShit);

	return true;
}


