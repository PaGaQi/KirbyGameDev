#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Point.h"
#include "Physics.h"

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

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

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	int pressOk;
	int pressBack;

private:
	SDL_Texture* img;

	SDL_Texture* menuBackground;
	SDL_Texture* Level1Platforms;
	
	PhysBody* Platform1;
	PhysBody* Platform2;
	PhysBody* Platform3;
	PhysBody* Platform4;
	PhysBody* Platform5;
	PhysBody* Platform6;
	PhysBody* PlatformSky;
	
};

#endif // __SCENE_H__