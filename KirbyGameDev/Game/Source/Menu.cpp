#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Menu.h"
#include "Scene.h"
#include "Textures.h"
#include "Player.h"
#include "Input.h"
#include "Audio.h"
#include "Window.h"
#include "Fonts.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "Defs.h"
#include "Log.h"
#include "Point.h"


Menu::Menu() 
{
	name.Create("menu");

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
	lifesAnim.PushBack({ 0, 164, 52, 48 });
	lifesAnim.PushBack({ 56, 164, 52, 48 });
	lifesAnim.PushBack({ 112, 164, 52, 48 });

	lifesAnim.loop = true;
	lifesAnim.speed = 0.1f;


	titleKirby = { SCREEN_WIDTH / 2 - 124, SCREEN_HEIGHT / 2 - 110, 248, 220 };
	
	baseHUDRect = { 0, 0, 1024, 256 };
	abilityHUDRect = { 0, 0, 128, 220 };
	abilityHUDCrop = { 0, 0, 128, 160 };

	collCountCrop = { 0, 312, 52, 48 };
	healthBarCrop = { 0, 364, 204, 33 };
	lifesCrop = { 36, 276 , 32, 32 };

	pauseRect = { 320, 224, 384, 256 };
	pauseCrop = { 0, 0, 384, 256 };
	pauseHandCrop = { 68, 120, 32, 32 };

	mouseRect = { 0, 0, 16, 24 };
	
	menuHandRect = { 0, 0, 64, 64 };
	menuHandCrop = { 0, 88, 64, 64 };

	musicVolumeRect = { 508, 220, 252, 36};
	musicVolumeCrop = { 0, 0, 252, 36 };

	sfxVolumeRect = { 508, 284, 252, 36 };
	sfxVolumeCrop = {0, 0, 252, 36 };

	fullscreenRect = { 580, 344, 44, 44 };
	fullscreenCrop = { 0, 40, 44, 44 };

	vsyncRect = { 580, 404, 44, 44 };
	vsyncCrop = { 0, 40, 44, 44 };

	
	currentButton = 0;
	previousButton = 0;

	saveDataAvailable = 0;

	currentMusVol = 128;
	currentSFXVol = 128;

	vsync = false;
	fullscreen = false;
}

	// Destructor
Menu:: ~Menu() {}

	// Called before render is available	
bool Menu::Awake() 
{
	pugi::xml_document c;
	pugi::xml_node config;
	pugi::xml_node configApp;
	return true;
}

bool Menu::Start() 
{
	//HUD Elements
	baseHUD = app->tex->Load("Assets/textures/HUD_base.png");
	abilityHUD = app->tex->Load("Assets/textures/HUD Sprites.png");
	pauseTexture = app->tex->Load("Assets/textures/Pause Menu.png");

	moveMouse = app->audio->LoadFx("Assets/audio/fx/2C - Moving Cursor Sound.wav");

	app->tex->UnLoad(menuHandTexture);
	menuHandTexture = app->tex->Load("Assets/maps/UI Elements Ver2.png");

	char lookupTable[] = { "0123456789" };
	timerFont = app->fonts->Load("Assets/textures/font_numbers.png", lookupTable, 1);

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
			app->render->camera.x = 0;
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

		case (SETTINGS):
		{
			app->render->camera.x = 0;
			menuBackground = app->tex->Load("Assets/maps/Settings Menu Ver3.png");
			titleMenu = false;

			optionSelected[0] = { 268, 204 };
			optionSelected[1] = { 268, 268 };
			optionSelected[2] = { 268, 332 };
			optionSelected[3] = { 268, 396 };
			optionSelected[4] = { 364, 460 };

			return true;
		}
		break;

		case (CREDITS):
		{
			menuBackground = app->tex->Load("Assets/maps/Credits Screen.png");
			
			titleMenu = false;

			optionSelected[0] = { 1024, 960 };
			optionSelected[1] = { 1024, 960 };
			optionSelected[2] = { 1024, 960 };
			optionSelected[3] = { 1024, 960 };
			optionSelected[4] = { 1024, 960 };

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
			baseHUD = app->tex->Load("Assets/textures/HUD_base.png");
			abilityHUD = app->tex->Load("Assets/textures/HUD Sprites.png");

			app->render->camera.x = 0;

			titleMenu = false;

			optionSelected[0] = { 430, 294 };
			optionSelected[1] = { 392, 326 };
			optionSelected[2] = { 414, 358 };
			optionSelected[3] = { 444, 390 };
			optionSelected[4] = { 444, 390 };
			return true;
		}
		break;
	}
}


bool Menu::PreUpdate() 
{
	if (titleMenu) currentAnimation = &welcomeKirby;
	if ((app->currentScene == LEVEL_1 && app->player->paused) || (app->currentScene != LEVEL_1)) SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

	//Preparing HUD and GUI for MAIN MENU--------------------------------------------------------------------------------------------------------------------------------
	if (app->currentScene == MENU)
	{
		//BUTTON SELECT BY HOVERING WITH MOUSE
		if (mouseRect.y <= 270 ) currentButton = 0;
		else if (mouseRect.y > 270 && mouseRect.y < 334 && saveDataAvailable) currentButton = 1;
		else if (mouseRect.y >= 334 && mouseRect.y < 398) currentButton = 2;
		else if (mouseRect.y >= 398 && mouseRect.y < 462) currentButton = 3;
		else if (mouseRect.y >= 462) currentButton = 4;
	}

	//Preparing HUD and GUI for SETTINGS MENU--------------------------------------------------------------------------------------------------------------------------------
	else if (app->currentScene == SETTINGS)
	{
		//BUTTON SELECT BY HOVERING WITH MOUSE
		if (mouseRect.y <= 270) currentButton = 0;
		else if (mouseRect.y > 270 && mouseRect.y < 334) currentButton = 1;
		else if (mouseRect.y >= 334 && mouseRect.y < 398) currentButton = 2;
		else if (mouseRect.y >= 398 && mouseRect.y < 462) currentButton = 3;
		else if (mouseRect.y >= 462) currentButton = 4;

		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP) && ((currentButton == 0) || (currentButton == 1))) app->audio->PlayFx(app->scene->pressOk);
		
		//SETTINGS MENU CHANGING VALUES
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			if (currentButton == 0)
			{
				if (mouseRect.x >= 508 && mouseRect.x <= 652)
				{
					musicVolumeRect.x = mouseRect.x - 126;					
				}

				if (musicVolumeRect.x < 400) musicVolumeRect.x = 400;
				else if (musicVolumeRect.x > 508) musicVolumeRect.x = 508;

				currentMusVol = 128 * (musicVolumeRect.x - 400) / 108;

			}
			else if (currentButton == 1)
			{
				if (mouseRect.x >= 508 && mouseRect.x <= 652)
				{
					sfxVolumeRect.x = mouseRect.x - 126;
				}

				if (sfxVolumeRect.x < 400) sfxVolumeRect.x = 400;
				else if (sfxVolumeRect.x > 508) sfxVolumeRect.x = 508;

				currentSFXVol = 128 * (sfxVolumeRect.x - 400) / 108;
			}
		}
		
		else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (currentButton == 2)
			{
				fullscreen = !fullscreen;
				if (!fullscreen)
				{
					fullscreenCrop = { 0, 40, 44, 44 };
					SDL_SetWindowFullscreen(app->win->window, 0);
					
					//SDL_RestoreWindow(app->win->window);
				}
				else
				{
					fullscreenCrop = { 48, 40, 44, 44 };					
					
					SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP); //CHANGE TO NORMAL FULLSCREEN WHEN POSSIBLE
				}						

				LOG("FULLSCREEN %i", fullscreen);
				LOG("REAL FULLSCREEN %i", app->win->fullscreen_window);

			}
			//VSYNC TOGGLE
			else if (currentButton == 3)
			{
				vsync = !vsync;
				if (!vsync) vsyncCrop = { 0, 40, 44, 44 };
				else vsyncCrop = { 48, 40, 44, 44 };
			
				SDL_GL_SetSwapInterval(vsync);
			}
		}
	}
	//Preparing HUD and GUI for CREDITS--------------------------------------------------------------------------------------------------------------------------------
	else if (app->currentScene == CREDITS) currentButton = 0;

	//Preparing HUD and GUI for LEVEL 1--------------------------------------------------------------------------------------------------------------------------------
	else if (app->currentScene == LEVEL_1)
	{
		currentAnimation = &lifesAnim;

		if (mouseRect.y <= 327) currentButton = 0;
		else if (mouseRect.y > 327 && mouseRect.y < 359) currentButton = 1;
		else if (mouseRect.y >= 359 && mouseRect.y < 391) currentButton = 2;
		else if (mouseRect.y >= 391) currentButton = 3;

		if (app->player->collectibleGet == 1) collCountCrop = { 56, 312, 52, 48 };
		else collCountCrop = { 0, 312, 52, 48 };

		healthBarCrop.w = app->player->health * 2;

		if (app->player->isDead == false)
		{
			abilityHUDCrop = { 0, 0, 128, 160 };
			lifesCrop = { 36, 276 , 32, 32 };
		}
		else
		{
			abilityHUDCrop.x = 264;
			lifesCrop.x = 0;
		}
	}
	return true;
}


bool Menu::Update(float dt) 
{	
	if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) saveDataAvailable = 1;

	if (app->currentScene != LEVEL_1)
	{
		if (app->currentScene == SETTINGS)
		{
			app->render->DrawTexture(menuHandTexture, musicVolumeRect.x, musicVolumeRect.y, &musicVolumeCrop);
			app->render->DrawTexture(menuHandTexture, sfxVolumeRect.x, sfxVolumeRect.y, &sfxVolumeCrop);
		}
		
		app->render->DrawTexture(menuBackground, 0, 0);

		if (titleMenu)currentAnimation->Update();
	}

	if (app->currentScene >= MENU)
	{
		//app->render->DrawRectangle(mouseRect, 0, 0, 255);
		app->render->DrawTexture(menuHandTexture, menuHandRect.x, menuHandRect.y, &menuHandCrop);
		
		menuHandRect.x = optionSelected[currentButton].x;
		menuHandRect.y = optionSelected[currentButton].y;	

		if (currentButton != previousButton) app->audio->PlayFx(moveMouse);

		previousButton = currentButton;
	}	

	else if (app->currentScene == LEVEL_1 && app->player->paused == true)
	{
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
	

	if (app->currentScene == SETTINGS)
	{
		app->render->DrawTexture(menuHandTexture, vsyncRect.x, vsyncRect.y, &vsyncCrop);
		app->render->DrawTexture(menuHandTexture, fullscreenRect.x, fullscreenRect.y, &fullscreenCrop);
	}

	if (app->currentScene == LEVEL_1)
	{
		if (app->player->paused)
		{
			app->render->DrawTexture(pauseTexture, pauseRect.x - (app->render->camera.x), pauseRect.y, &pauseCrop);
			app->render->DrawTexture(menuHandTexture, menuHandRect.x - (app->render->camera.x), menuHandRect.y, &pauseHandCrop);
		}
		
		if (baseHUD == NULL) LOG("NO HUD TEXTURE");
		app->render->DrawTexture(baseHUD, -(app->render->camera.x), 704, &baseHUDRect);
		
		app->render->DrawTexture(abilityHUD, 880 - (app->render->camera.x), 832, &lifesCrop);							//Lifes Counter
		app->render->DrawTexture(abilityHUD, 764 - (app->render->camera.x), 816, &currentAnimation->GetCurrentFrame()); //Lifes Animation
		app->render->DrawTexture(abilityHUD, 304 - (app->render->camera.x), 768, &healthBarCrop);						//Health Bar
		app->render->DrawTexture(abilityHUD, 848 - (app->render->camera.x), 752, &collCountCrop);						//Collectible Counter
		app->render->DrawTexture(abilityHUD, 592 -(app->render->camera.x), 736, &abilityHUDCrop);						//Kirby Ability
		
		sprintf_s(timerText, 8, "%7d", (int)app->player->timer);
		app->fonts->BlitText(304, 832, timerFont, timerText);

		currentAnimation->Update();
	}
	
	Mix_Volume(pressOk, currentSFXVol);
	Mix_Volume(moveMouse, currentSFXVol);

	return true;
}

bool Menu::LoadState(pugi::xml_node& data)
{
	
	return true;
}
bool Menu::SaveState(pugi::xml_node& data) const
{
	
	return true;
}

bool Menu::CleanUp() 
{	
	switch (app->currentScene)
	{
		case (TITLE):
		{
			app->tex->UnLoad(menuBackground);
			app->tex->UnLoad(abilityHUD);
			app->tex->UnLoad(baseHUD);
		}
		break;
	
		case (MENU):
		{
			app->tex->UnLoad(abilityHUD);
			app->tex->UnLoad(baseHUD);
			app->tex->UnLoad(pauseTexture);			

			app->fonts->UnLoad(timerFont);
			return true;
		}
		break;

		case (DEATH):
		{
			app->tex->UnLoad(abilityHUD);
			app->tex->UnLoad(baseHUD);

			app->fonts->UnLoad(timerFont);
			return true;
		}
		break;

		case (LEVEL_1):
		{
			app->tex->UnLoad(menuBackground);
			return true;
		}
		break;

		case (SETTINGS):
		{
			app->tex->UnLoad(menuBackground);
			app->tex->UnLoad(menuHandTexture);

			delete &menuBackground;
			return true;
		}
		break;
	}

	return true;
}


