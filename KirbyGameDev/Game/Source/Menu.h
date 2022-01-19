#include "Module.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"


class Menu : public Module
{
public:

	Menu();

	// Destructor
	virtual ~Menu();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	SDL_Rect mouseRect;

	int currentButton;
	int previousButton;

	float currentMusVol;
	float currentSFXVol;

	bool saveDataAvailable;

private:
	
	bool titleMenu;

	SDL_Texture* menuBackground;
	Animation* currentAnimation;

	//Menu Animations
	Animation welcomeKirby;	
	SDL_Texture* menuKirby;
	SDL_Rect titleKirby;

	//Death Screen Animations
	SDL_Texture* deathScreen;

	//HUD Base
	SDL_Texture* baseHUD;
	SDL_Rect baseHUDRect;		

	//HUD Lives Animations
	Animation lifesHUD;
	Animation damageBarHUD;

	//Abilites HUD
	Animation* currentAbilityAnim;
	SDL_Texture* abilityHUD;
	SDL_Rect abilityHUDRect;
	Animation abilityNormal;
	Animation abilityHit;
	Animation abilityLose;
	Animation abilityWin;

	//Main Menu Buttons
	SDL_Rect menuHandRect;
	SDL_Rect menuHandCrop;
	SDL_Texture* menuHandTexture;

	SDL_Texture* settingsTexture;

	SDL_Rect musicVolumeRect;
	SDL_Rect musicVolumeCrop;

	SDL_Rect sfxVolumeRect;
	SDL_Rect sfxVolumeCrop;

	SDL_Rect vsyncRect;
	SDL_Rect vsyncCrop;

	SDL_Rect fullscreenRect;
	SDL_Rect fullscreenCrop;


	SDL_Rect pauseRect;
	SDL_Rect pauseCrop;
	SDL_Texture* pauseTexture;
	
	SDL_Rect pauseHandCrop;
	
	bool vsync = 0;
	bool fullscreen = 0;

	b2Vec2 optionSelected[5];

	int moveMouse;
	int pressOk;
	int pressBack;
};
