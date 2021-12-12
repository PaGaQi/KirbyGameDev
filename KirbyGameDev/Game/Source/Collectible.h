#pragma once
#include "Physics.h"
#include "Module.h"
#include "App.h"
#include "Point.h"
#include "Animation.h"


class PhysBody;

class Collectible : public Module, public b2ContactListener
{
public:
	Collectible();
	~Collectible();


	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	//bool SaveState(pugi::xml_node&) const;

	void Die();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void Destroy();
private:
	bool Destroyed = false;
	bool draw = true;
	Point <int> position;
	PhysBody* collectiblePhysbody;
	b2Fixture* collectibleSensor;

	SDL_Texture* collectibleTexture;

	Animation* currentAnimation;

	Animation collectibleAnimation;
};