#include "hitbox.h"

Hitbox::CollisionData Hitbox::collidingNorth(Point3D pos, World& w)
{
	CollisionData currCollision = {CollisionType::None, 0.0};
	const int startX = floor((pos.x - width / 2.0) / tileWidth);
	const int stopX = floor((pos.x + width / 2.0) / tileWidth);
	const int z = floor((pos.z - depth / 2.0) / tileTopHeight);
	for (int i = startX; i <= stopX; i++)
	{
		try
		{
			const double snapHeight = w.tileAt(i, z).height * tileHeight;
			const double heightDiff = snapHeight - pos.y;
			if (heightDiff > /* tileHeight */ 0.0)
			{
				currCollision.collisionType = CollisionType::Colliding;
			}
			// else if (heightDiff > 0.0 && currCollision.collisionType != CollisionType::Colliding)
			// {
			// 	currCollision.collisionType = CollisionType::SnapUp;
			// 	if (snapHeight > currCollision.snapHeight)
			// 	{
			// 		currCollision.snapHeight = snapHeight;
			// 	}
			// }
		}
		catch (...) {}
	}
	return currCollision;
}

Hitbox::CollisionData Hitbox::collidingWest(Point3D pos, World& w)
{
	CollisionData currCollision = {CollisionType::None, 0.0};
	const int x = floor((pos.x - width / 2.0) / tileWidth);
	const int startZ = floor((pos.z - depth / 2.0) / tileTopHeight);
	const int stopZ = floor((pos.z + depth / 2.0) / tileTopHeight);
	for (int i = startZ; i <= stopZ; i++)
	{
		try
		{
			const double snapHeight = w.tileAt(x, i).height * tileHeight;
			const double heightDiff = snapHeight - pos.y;
			if (heightDiff > /* tileHeight */ 0.0)
			{
				currCollision.collisionType = CollisionType::Colliding;
			}
			// else if (heightDiff > 0.0 && currCollision.collisionType != CollisionType::Colliding)
			// {
			// 	currCollision.collisionType = CollisionType::SnapUp;
			// 	if (snapHeight > currCollision.snapHeight)
			// 	{
			// 		currCollision.snapHeight = snapHeight;
			// 	}
			// }
		}
		catch (...) {}
	}
	return currCollision;
}

Hitbox::CollisionData Hitbox::collidingSouth(Point3D pos, World& w)
{
	CollisionData currCollision = {CollisionType::None, 0.0};
	const int startX = floor((pos.x - width / 2.0) / tileWidth);
	const int stopX = floor((pos.x + width / 2.0) / tileWidth);
	const int z = floor((pos.z + depth / 2.0) / tileTopHeight);
	for (int i = startX; i <= stopX; i++)
	{
		try
		{
			const double snapHeight = w.tileAt(i, z).height * tileHeight;
			const double heightDiff = snapHeight - pos.y;
			if (heightDiff > /* tileHeight */ 0.0)
			{
				currCollision.collisionType = CollisionType::Colliding;
			}
			// else if (heightDiff > 0.0 && currCollision.collisionType != CollisionType::Colliding)
			// {
			// 	currCollision.collisionType = CollisionType::SnapUp;
			// 	if (snapHeight > currCollision.snapHeight)
			// 	{
			// 		currCollision.snapHeight = snapHeight;
			// 	}
			// }
		}
		catch (...) {}
	}
	return currCollision;
}

Hitbox::CollisionData Hitbox::collidingEast(Point3D pos, World& w)
{
	CollisionData currCollision = {CollisionType::None, 0.0};
	const int x = floor((pos.x + width / 2.0) / tileWidth);
	const int startZ = floor((pos.z - depth / 2.0) / tileTopHeight);
	const int stopZ = floor((pos.z + depth / 2.0) / tileTopHeight);
	for (int i = startZ; i <= stopZ; i++)
	{
		try
		{
			const double snapHeight = w.tileAt(x, i).height * tileHeight;
			const double heightDiff = snapHeight - pos.y;
			if (heightDiff > /* tileHeight */ 0.0)
			{
				currCollision.collisionType = CollisionType::Colliding;
			}
			// else if (heightDiff > 0.0 && currCollision.collisionType != CollisionType::Colliding)
			// {
			// 	currCollision.collisionType = CollisionType::SnapUp;
			// 	if (snapHeight > currCollision.snapHeight)
			// 	{
			// 		currCollision.snapHeight = snapHeight;
			// 	}
			// }
		}
		catch (...) {}
	}
	return currCollision;
}

Hitbox::CollisionData Hitbox::collidingBottom(Point3D pos, World& w)
{
	CollisionData currCollision = {CollisionType::None, 0.0};
	const int startX = floor((pos.x - width / 2.0) / tileWidth);
	const int stopX = floor((pos.x + width / 2.0) / tileWidth);
	const int startZ = floor((pos.z - depth / 2.0) / tileTopHeight);
	const int stopZ = floor((pos.z + depth / 2.0) / tileTopHeight);
	for (int x = startX; x <= stopX; x++)
	{
		for (int z = startZ; z <= stopZ; z++)
		{
			try
			{
				const double snapHeight = w.tileAt(x, z).height * tileHeight;
				const double heightDiff = snapHeight - pos.y;
				if (heightDiff > 0.0)
				{
					currCollision.collisionType = CollisionType::SnapUp;
					if (snapHeight > currCollision.snapHeight)
					{
						currCollision.snapHeight = snapHeight;
					}
				}
			}
			catch (...) {}
		}
	}
	return currCollision;
}