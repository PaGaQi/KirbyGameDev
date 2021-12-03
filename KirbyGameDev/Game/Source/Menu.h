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

};
