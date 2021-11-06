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
	// L03: DONE: Load map
	app->map->Load("KirbyMapBackground.tmx");
	app->map->Load("KirbyMapForeground.tmx");
	app->audio->PlayMusic("Assets/audio/music/Kirb.ogg");

	int Platform1_vertex[8] = {
	0, 479,
	0, 352,
	192, 352,
	192, 479
	};

	int Platform2_vertex[8] = {
	224, 480,
	224, 352,
	256, 352,
	256, 480
	};

	int Platform3_vertex[8] = {
	288, 480,
	288, 352,
	384, 352,
	384, 480
	};

	int Platform4_vertex[8] = {
	448, 479,
	448, 320,
	576, 320,
	576, 480
	};

	int Platform5_vertex[16] = {
	736, 478,
	736, 320,
	1024, 320,
	1024, 288,
	1120, 289,
	1120, 224,
	1280, 224,
	1280, 481
	};

	int Platform6_vertex[12] = {
	1440, 480,
	1440, 288,
	1472, 288,
	1472, 320,
	1536, 320,
	1536, 479
	};

	int PlatformSky_vertex[8] = {
	32, 256,
	32, 224,
	128, 224,
	128, 256
	};

	/*Platform1 = app->physics->CreateChain(0, 0, Platform1_vertex, 8 );
	Platform2 = app->physics->CreateChain(0, 0, Platform2_vertex, 8 );
	Platform3 = app->physics->CreateChain(0, 0, Platform3_vertex, 8 );
	Platform4 = app->physics->CreateChain(0, 0, Platform4_vertex, 8 );
	Platform5 = app->physics->CreateChain(0, 0, Platform5_vertex, 16 );
	Platform6 = app->physics->CreateChain(0, 0, Platform6_vertex, 12);
	PlatformSky = app->physics->CreateChain(0, 0, PlatformSky_vertex, 8);*/
	
	

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
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
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

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
