#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Fonts.h"
#include "Audio.h"
#include "Player.h"
#include"Menu.h"
#include "Scene.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Collectible.h"


#include "Map.h"
#include "Physics.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

#include "Box2D/Box2D/Box2D.h"

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	win = new Window();
	input = new Input();
	render = new Render();
	tex = new Textures();
	fonts = new Fonts();
	audio = new Audio();
	player = new Player();
	scene = new Scene();
	map = new Map();
	physics = new Physics();
	menu = new Menu();
	groundEnemy = new GroundEnemy();
	flyingEnemy = new FlyingEnemy();
	collectible = new Collectible();
	pathfinding = new PathFinding();
	


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(fonts);
	AddModule(audio);
	AddModule(physics);
	AddModule(player);
	AddModule(scene);
	AddModule(map);
	AddModule(menu);
	AddModule(groundEnemy);
	AddModule(flyingEnemy);
	AddModule(collectible);
	AddModule(pathfinding);


	// Render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		// L01: DONE 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			// L01: DONE 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	//win->Awake();

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}

pugi::xml_node App::LoadSave(pugi::xml_document& saveFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = saveFile.load_file(SAVE_STATE_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", SAVE_STATE_FILENAME, result.description());
	else ret = saveFile.child("config");

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	start = SDL_GetTicks();
	frameCount++;
	lastSecFrameCount++;
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) LoadGame();
	if (saveGameRequested == true) SaveGame();
	//if ((1000 / FPS) > SDL_GetTicks() - start) SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));

	float secondsSinceStartup = startupTime.ReadSec();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
		dt = 1 / averageFps;
	}

	static char title[256];
	sprintf_s(title, 256, "Kirby's Shit Adventure - Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	
	app->win->SetTitle(title);
	if ((1000 / FPS) > SDL_GetTicks() - start) SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	//app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest()
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist
	loadGameRequested = true;
}

// ---------------------------------------
void App::SaveGameRequest() const
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	saveGameRequested = true;
}

// ---------------------------------------
// L02: TODO 5: Create a method to actually load an xml file
// then call all the modules to load themselves
bool App::LoadGame()
{
	bool ret = false;

	pugi::xml_document saveFile;
	pugi::xml_node save;
	save = LoadSave(saveFile);

	ListItem<Module*>* item;
	item = modules.start;
	//LOG("name: %s", item->data->name.GetString());
	while (item != NULL)
	{
		SString name = item->data->name;
		//LOG("name: %s", name.GetString());
		ret = item->data->LoadState(save.child(name.GetString()));
		item = item->next;
	}
	
	loadGameRequested = false;

	return ret;
}

// L02: DONE 7: Implement the xml save method for current state
bool App::SaveGame() const
{
	bool ret = true;

	pugi::xml_document saveFile;
	pugi::xml_node save;

	save = LoadSave(saveFile);

	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL)
	{
		//LOG("name: %s", item->data->name.GetString());
		SString name = item->data->name;
		//LOG("name: %s", name.GetString());
		ret = item->data->SaveState(save.child(name.GetString()));
		item = item->next;
	}

	ret = saveFile.save_file("save_game.xml");

	saveGameRequested = false;

	return ret;
}


void App::ChangeScene(sceneType nextScene)
{
	currentScene = nextScene;

	/*CleanUp();
	Awake();*/

	Start();

}



