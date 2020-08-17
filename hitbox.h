#pragma once
#include "world.h"

class Hitbox
{
public:
	enum CollisionType
	{
		None,
		SnapUp,
		Colliding
	};
	struct CollisionData
	{
		CollisionType collisionType;
		double snapHeight;
	};

	double width;
	double height;
	double depth;

	CollisionData collidingNorth(Point3D pos, World& w);
	CollisionData collidingWest(Point3D pos, World& w);
	CollisionData collidingSouth(Point3D pos, World& w);
	CollisionData collidingEast(Point3D pos, World& w);
	CollisionData collidingBottom(Point3D pos, World& w);
};