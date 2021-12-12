#include "App.h"
#include "Collectible.h"
#include "Log.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"
#include "Animation.h"

Collectible::Collectible()
{
	//ANIMATION
	isMoving = false;
	collectibleAnimation.PushBack({ 0, 0, 32, 32 });
	
}
Collectible::~Collectible()
{

}

bool Collectible::Awake(pugi::xml_node& config)
{
	LOG("Loading Collectible");

	position.x = 0;
	position.y = 45;

	return true;
}

bool Collectible::Start()
{
	bool ret = true;



	if (app->currentScene == LEVEL_1)
	{
		collectiblePhysbody = app->physics->CreateCircle(position.x, position.y, 25, b2_kinematicBody);

		collectiblePhysbody->body->GetFixtureList()->SetFriction(5.0f);

		b2PolygonShape sensorShape;
		sensorShape.SetAsBox(PIXEL_TO_METERS(30), PIXEL_TO_METERS(30));


		b2FixtureDef sensorFix;
		sensorFix.shape = &sensorShape;
		sensorFix.isSensor = true;

		collectibleSensor = collectiblePhysbody->body->CreateFixture(&sensorFix);
		collectibleTexture = app->tex->Load("Assets/sprites/Collectible.png");
		collectiblePhysbody->listener = this;

	}




	return ret;
}
void Collectible::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{
		LOG("NOT COLLECTIBLE COLLISION");
	}
	else LOG("COLLECTIBLE COLLISION");
}
bool Collectible::PreUpdate()
{
	currentAnimation = &collectibleAnimation;
	if (Destroyed) Die();
	return true;
}
bool Collectible::Update(float dt)
{
	return true;
}
bool Collectible::PostUpdate()
{
	if (app->currentScene == LEVEL_1 && draw)
	{
		SDL_Rect section = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(collectibleTexture, 0, 576);
	
	}

	return true;
}
void Collectible::Die()
{
	//app->physics->world->DestroyBody(collectiblePhysbody->body);
	Destroyed = false;
	draw = false;

}
bool Collectible::CleanUp()
{
	return true;
}
bool Collectible::LoadState(pugi::xml_node&)
{
	return true;
}
/*bool Collectible::SaveState(pugi::xml_node&)
{
	return true;
}*/
void Collectible::Destroy()
{

}