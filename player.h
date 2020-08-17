#pragma once
#include "geoutils.h"
#include "directv.h"
#include "image.h"
#include "world.h"
#include "hitbox.h"

class Player
{
private:
	Hitbox hitbox;
	double yVel;
public:
	constexpr static double speed = 5.0;

	Point3D pos;
	Image image;

	Player(Point3D pos);

	void logic(Direction dir, World& world, DirectV& dv);
};