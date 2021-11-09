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
	
	Animation* currentAnimation;

	Animation welcomeKirby;	
	SDL_Texture* menuKirby;
	SDL_Rect titleKirby;

	SDL_Texture* deathScreen;
	Animation losingKirby;

};
