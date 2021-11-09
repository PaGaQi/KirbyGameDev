#pragma once
#include "Module.h"
#include "Box2D/Box2D/Box2D.h"
#include "App.h"
#include "Player.h"



#define GRAVITY_X 0.0f
#define GRAVITY_Y -400.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() 
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class Physics : public Module, public b2ContactListener // TODO
{
public:
	Physics();
	~Physics();

	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();
	
	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type);
	PhysBody* CreateStaticRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);

	// b2ContactListener ---
	PhysBody* backgroundColliders;


	PhysBody* Platform1;
	PhysBody* Platform2;
	PhysBody* Platform3;
	PhysBody* Platform4;
	PhysBody* Platform5;
	PhysBody* Platform6;
	PhysBody* PlatformSky;
	
	void BeginContact(b2Contact* contact);
	

	List<PhysBody*> groundColliders;
private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouseJoint;
	b2Body* ground;
	b2Vec2 clickedBodyPos;
	
};