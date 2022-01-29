#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "Box2D/Box2D/Box2D.h"
#include "Collectible.h"

#include "SDL_mixer/include/SDL_mixer.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	prevScene = MENU;
	playSaved = 1;
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
	app->map->Load("Test Map.tmx");	

	pressOk = app->audio->LoadFx("Assets/audio/fx/Ok  sound.wav");
	pressBack = app->audio->LoadFx("Assets/audio/fx/Back Sound.wav");


	switch (app->currentScene)
	{
		case TITLE:
		{
			//menuBackground = app->tex->Load("Assets/maps/TitleScreenVer2.png");
			app->audio->PlayMusic("Assets/audio/music/01 - Title.ogg");
		}
		break;

		case MENU:
		{
			prevScene = MENU;
			LOG("CLEARING MAIN MENU");
			app->menu->CleanUp();
			//app->audio->PlayMusic("Assets/audio/music/Menu Music - World Flower.ogg");
		}
		break;

		case LEVEL_1:
		{
			if (prevScene != LEVEL_1) app->audio->PlayMusic("Assets/audio/music/02 - Level 01.ogg");
			prevScene = LEVEL_1;
			LOG("CLEARING MAIN MENU");
			app->menu->CleanUp();
			
		}
		break;

		case DEATH:
		{
			app->menu->CleanUp();
			app->player->CleanUp();			
			app->audio->PlayMusic("music_spy.ogg");
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
	//playSaved = 1;

	Mix_VolumeMusic(app->menu->currentMusVol);
	
	switch (app->currentScene)
	{
		case TITLE:
		{
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
			{
				app->ChangeScene(MENU);

				app->audio->PlayMusic("Assets/audio/music/Menu Music - World Flower.ogg");
				app->render->camera.x = 0;
				app->scene->Start();
				return true;
			}
		}
		break;

		case MENU:
		{
			//playSaved = 0;
			prevScene = MENU;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				app->audio->PlayFx(pressOk);

				app->render->camera.x = 0;

				if (app->menu->currentButton == 0)
				{
					playSaved = 0;
					app->ChangeScene(LEVEL_1);
				}
				else if (app->menu->currentButton == 1)
				{
					playSaved = 1;
					app->ChangeScene(LEVEL_1);
				}
				else if (app->menu->currentButton == 2) app->ChangeScene(SETTINGS);
				else if (app->menu->currentButton == 3) app->ChangeScene(CREDITS);
				else if (app->menu->currentButton == 4) return false;
				
				app->scene->Start();
				return true;
			}

		}
		break;

		case SETTINGS:
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{										
				if (app->menu->currentButton == 4)
				{
					app->audio->PlayFx(pressBack);
					app->ChangeScene(prevScene);
					if (prevScene == LEVEL_1) app->LoadGameRequest();
				}
				else if (app->menu->currentButton == 3 || app->menu->currentButton == 2)
				{
					app->audio->PlayFx(pressOk);
				}
				
				return true;
			}
		}
		break;

		case CREDITS:
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
			{
				app->audio->PlayFx(pressBack);
				app->ChangeScene(MENU);

				return true;
			}
		}
		break;

		case LEVEL_1:
		{
			app->map->Draw();

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && app->player->paused)
			{
				if (app->menu->currentButton == 0)
				{
					app->audio->PlayFx(pressOk);
					app->player->paused = !app->player->paused;
				}
				else if (app->menu->currentButton == 1)
				{
					app->audio->PlayFx(pressOk);
					app->ChangeScene(MENU);
					app->audio->PlayMusic("Assets/audio/music/Menu Music - World Flower.ogg");
					app->player->CleanUp();
				}
				else if (app->menu->currentButton == 2)
				{
					app->audio->PlayFx(pressOk);					
					app->ChangeScene(SETTINGS);			
				}
				else if (app->menu->currentButton == 3) return false;

				if (app->menu->currentButton > 0) app->scene->Start();
				return true;
			}
		}
		break;

		case DEATH:
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				app->ChangeScene(TITLE);
				//app->menu->Start();
				app->render->camera.x = 0;
				return true;
			}
		}
		break;
	}

	return true;
	/*
	/ Draw map
	app->map->Draw();

	SString title("Kirby's Shit Adventure");
	("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());
	*/	
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

void Scene :: OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing Scene");

	switch (app->currentScene)
	{
		case LEVEL_1:
		{
			LOG("Unloading Background Texture");
			app->tex->UnLoad(menuBackground);
			return true;
		}
		break;

		case DEATH:
		{
			LOG("Unloading Background Music");
			app->audio->CleanUp();
			return true;
		}
		break;
	}

	return true;
}

