#include "App.h"
#include "Point.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
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
	if (app->currentScene == TITLE)
	{		
		menuBackground = app->tex->Load("Assets/maps/TitleScreenVer1.png");

	}
	if (app->currentScene == LEVEL_1)
	{
		Level1Platforms = app->tex->Load("Assets/maps/Level1Platforms.png");
		app->map->Load("KirbyMapBackground.tmx");
		app->map->Load("KirbyMapForeground.tmx");
		app->audio->PlayMusic("Assets/audio/music/Kirb.ogg");

		return true;
	}
	
	return true;
	// L03: DONE: Load map
	
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

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 5;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 5;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 5;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 5;
	
	if (app->currentScene == TITLE)
	{
		if (app->input->GetKey(SDL_SCANCODE_RETURN))
		{
			app->ChangeScene(LEVEL_1);
		}
	}

	if (app->currentScene == LEVEL_1)
	{
		if (app->player->isDead == 1)
		{
			app->ChangeScene(TITLE);
		}
	}

	if (app->currentScene == TITLE)
	{
		app->render->DrawTexture(menuBackground, 0, 0);
	}
	if (app->currentScene == LEVEL_1)
	{
		app->map->Draw();
	}

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more
	//app->render->DrawTexture()

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

	return true;
}
