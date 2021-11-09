#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Menu.h"
#include "Box2D/Box2D/Box2D.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	switch (app->currentScene)
	{
		case TITLE:
		{
			menuBackground = app->tex->Load("Assets/maps/TitleScreenVer1.png");
			app->audio->PlayMusic("Assets/audio/music/01 - Title.ogg");
		}
		break;

		case LEVEL_1:
		{
			app->menu->CleanUp();
			app->map->Load("KirbyMapBackground.tmx");			
			app->audio->PlayMusic("Assets/audio/music/02 - Level 01.ogg");
		}
		break;
	}	

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		app->SaveGameRequest();
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		app->LoadGameRequest();
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	
	switch (app->currentScene)
	{
	case TITLE:
	{
		if (app->input->GetKey(SDL_SCANCODE_RETURN))
		{
			app->ChangeScene(LEVEL_1);
		}

		app->render->DrawTexture(menuBackground, 0, 0);
	}
	break;

	case LEVEL_1:
	{
			app->scene->CleanUp();
		//app->map->Draw();
	}
	break;
	}

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}



// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	switch (app->currentScene)
	{
	case TITLE:
	{
		
	}
	break;

	case LEVEL_1:
	{
		LOG("Unloading Background Texture");
		app->tex->UnLoad(menuBackground);
	}
	break;
	}

	return true;
}
