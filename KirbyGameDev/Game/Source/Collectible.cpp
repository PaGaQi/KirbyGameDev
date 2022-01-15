#include "App.h"
#include "Collectible.h"
#include "Log.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"
#include "Animation.h"
#include "Player.h"

Collectible::Collectible()
{
	name.Create("map");

	//ANIMATION
	collectAnim.PushBack({ 0, 0, 32, 32 });
	collectAnim.PushBack({ 34, 0, 32, 32 });
	collectAnim.PushBack({ 68, 0, 32, 32 });
	collectAnim.PushBack({ 102, 0, 32, 32 });

	collectAnim.loop = true;
	collectAnim.speed = 0.07f;


	collectRect;	
}
Collectible::~Collectible()
{

}

bool Collectible::Awake(pugi::xml_node& config)
{
	LOG("Loading Collectible");

	position.x = 85;
	position.y = 430;

	return true;
}

bool Collectible::Start()
{
	bool ret = true;
	
	collectTexture = app->tex->Load("Assets/textures/Collectible.png");

	if (app->currentScene == LEVEL_1)
	{
		LOG("Loading Collectible Sprite");		
		collectRect = { position.x, position.y, 32, 32};
		
		LOG("Creating Collectible Hitbox");
		collectiblePhys = app->physics->CreateRectangleSensor(position.x, position.y, 16, b2_kinematicBody);
		collectiblePhys->listener = this;
		collectiblePhys->id = 3;	

		drawCollectible = 1;
		
		b2PolygonShape sensorShape;
		sensorShape.SetAsBox(PIXEL_TO_METERS(16), PIXEL_TO_METERS(16));

		b2FixtureDef collectSensor;
		collectSensor.shape = &sensorShape;
		collectSensor.isSensor = true;

		collectibleSensor = collectiblePhys->body->CreateFixture(&collectSensor);	
		currentAnimation = &collectAnim;
	}

	return ret;
}

void Collectible::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (app->currentScene == LEVEL_1)
	{
		if (bodyB == nullptr)
		{}
		else if (bodyB->id == 1)
		{
			drawCollectible = false;
		}
	}
}

bool Collectible::PreUpdate()
{
	if (app->currentScene == LEVEL_1)
	{
		if (drawCollectible == true)
		{
			currentAnimation = &collectAnim;		
		}		
	}
	
	return true;
}

bool Collectible::Update(float dt)
{
	if (drawCollectible == true && app->currentScene == LEVEL_1) currentAnimation->Update();
	
	if ((app->currentScene != LEVEL_1) || (app->player->collectibleGet == true))
	{
		drawCollectible = false;
	}
	else if (app->player->collectibleGet == false)
	{
		drawCollectible = true;
	}
	
	if (drawCollectible) LOG("IS DRAWING", drawCollectible);

	return true;
}

bool Collectible::PostUpdate()
{
	//if (app->player->collectibleGet) LOG("COLLECTIBLE %i", app->player->collectibleGet);

	if (app->currentScene == LEVEL_1 && drawCollectible == true)
	{		
		app->render->DrawTexture(collectTexture, position.x - 16, position.y - 16, &currentAnimation->GetCurrentFrame());
	}


	return true;
}

bool Collectible::CleanUp()
{
	app->tex->UnLoad(collectTexture);

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