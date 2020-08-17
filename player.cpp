#include "player.h"

Player::Player(Point3D pos)
	: hitbox{16.0, 16.0, 16.0},
	  yVel(0.0),
	  pos(pos),
	  image(ImageID::LOWERCASEMU, 16.0, 16.0) {}
	  
void Player::logic(Direction dir, World& world, DirectV& dv)
{
	bool snap = false;
	double snapHeight = 0.0;
	switch (dir)
	{
		case DIR_N:
		{
			pos.z -= speed;
			Hitbox::CollisionData collisionData = hitbox.collidingNorth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = floor(pos.z / tileTopHeight) * tileTopHeight + hitbox.depth / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_W:
		{
			pos.x -= speed;
			Hitbox::CollisionData collisionData = hitbox.collidingWest(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = floor(pos.x / tileWidth) * tileWidth + hitbox.width / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_S:
		{
			pos.z += speed;
			Hitbox::CollisionData collisionData = hitbox.collidingSouth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = nextafter((floor(pos.z / tileTopHeight) + 1) * tileTopHeight - hitbox.depth / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_E:
		{
			pos.x += speed;
			Hitbox::CollisionData collisionData = hitbox.collidingEast(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = nextafter((floor(pos.x / tileWidth) + 1) * tileWidth - hitbox.width / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_NW:
		{
			pos.z -= speed * invSqrt2;
			Hitbox::CollisionData collisionData = hitbox.collidingNorth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = floor(pos.z / tileTopHeight) * tileTopHeight + hitbox.depth / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
			pos.x -= speed * invSqrt2;
			collisionData = hitbox.collidingWest(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = floor(pos.x / tileWidth) * tileWidth + hitbox.width / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_NE:
		{
			pos.z -= speed * invSqrt2;
			Hitbox::CollisionData collisionData = hitbox.collidingNorth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = floor(pos.z / tileTopHeight) * tileTopHeight + hitbox.depth / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
			pos.x += speed * invSqrt2;
			collisionData = hitbox.collidingEast(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = nextafter((floor(pos.x / tileWidth) + 1) * tileWidth - hitbox.width / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_SW:
		{
			pos.z += speed * invSqrt2;
			Hitbox::CollisionData collisionData = hitbox.collidingSouth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = nextafter((floor(pos.z / tileTopHeight) + 1) * tileTopHeight - hitbox.depth / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
			pos.x -= speed * invSqrt2;
			collisionData = hitbox.collidingWest(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = floor(pos.x / tileWidth) * tileWidth + hitbox.width / 2.0;
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_SE:
		{
			pos.z += speed * invSqrt2;
			Hitbox::CollisionData collisionData = hitbox.collidingSouth(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.z = nextafter((floor(pos.z / tileTopHeight) + 1) * tileTopHeight - hitbox.depth / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
			pos.x += speed * invSqrt2;
			collisionData = hitbox.collidingEast(pos, world);
			if (collisionData.collisionType == Hitbox::CollisionType::Colliding)
			{
				pos.x = nextafter((floor(pos.x / tileWidth) + 1) * tileWidth - hitbox.width / 2.0, -INFINITY);
			}
			else if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
			{
				snap = true;
				if (collisionData.snapHeight > snapHeight) snapHeight = collisionData.snapHeight;
			}
		}
		break;
		case DIR_NONE:
		break;
	}
	if (snap)
	{
		pos.y = snapHeight;
	}

	if (yVel > -25.0) yVel -= 1.0;
	pos.y += yVel;
	Hitbox::CollisionData collisionData = hitbox.collidingBottom(pos, world);
	if (collisionData.collisionType == Hitbox::CollisionType::SnapUp)
	{
		pos.y = collisionData.snapHeight;
		if (dv.keyDown(VK_SPACE))
			yVel = 7.5;
		else
			yVel = 0.0;
	}
}