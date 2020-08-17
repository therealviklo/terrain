#include "world.h"

void loadImagesAt(Tile& tile, float x, float y)
{
	int yOffsetTop = 0;
	auto loadTopImage = [&](Image& i) -> void {
		i = Image(
			TILES,
			tileWidth,
			tileTopHeight,
			x,
			y + yOffsetTop * tileTopHeight,
			tileWidth,
			tileTopHeight
		);
		yOffsetTop++;
	};
	loadTopImage(tile.topImages.base);
	loadTopImage(tile.topImages.topEdge);
	loadTopImage(tile.topImages.rightEdge);
	loadTopImage(tile.topImages.bottomEdge);
	loadTopImage(tile.topImages.leftEdge);
	loadTopImage(tile.topImages.neCorner);
	loadTopImage(tile.topImages.seCorner);
	loadTopImage(tile.topImages.swCorner);
	loadTopImage(tile.topImages.nwCorner);

	int yOffsetSide = 0;
	auto loadSideImage = [&](Image& i) -> void {
		i = Image(
			TILES,
			tileWidth,
			tileHeight,
			x,
			y + (yOffsetTop * tileTopHeight + yOffsetSide * tileHeight),
			tileWidth,
			tileHeight
		);
		yOffsetSide++;
	};
	loadSideImage(tile.sideImages.base);
	loadSideImage(tile.sideImages.rightEdge);
	loadSideImage(tile.sideImages.leftEdge);
	loadSideImage(tile.sideImages.grass);
}

World::World()
	: tiles(50, 50)
{
	for (unsigned y = 0; y < tiles.getHeight(); y++)
	{
		for (unsigned x = 0; x < tiles.getWidth(); x++)
		{
			loadImagesAt(tiles[x][y], 0.0f, 0.0f);
			tiles[x][y].height = static_cast<unsigned short>(rand() % 3);
		}
	}
}

void World::drawTile(int x, int y, int z, Point centrePos, DirectV& dv, images_t& images)
{
	auto& currTile = tiles.at(x, z);
	if (y == currTile.height)
	{
		const int diff = currTile.height - (z == tiles.getHeight() - 1 ? 0 : tiles.at(x, z + 1).height);
		if (diff >= -1)
		{
			const float xPos = dv.getEffWidth() / 2.0f + x * tileWidth - centrePos.x;
			const float yPos = dv.getEffHeight() / 2.0f + z * tileTopHeight - y * tileHeight - centrePos.y;

			// Rita bas.
			currTile.topImages.base.draw(
				xPos,
				yPos,
				dv,
				images
			);

			// Rita kanter.
			if (x > 0 && currTile.height > tiles.at(x - 1, z).height)
				currTile.topImages.leftEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (z > 0 && currTile.height > tiles.at(x, z - 1).height)
				currTile.topImages.topEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (x < tiles.getWidth() - 1 && currTile.height > tiles.at(x + 1, z).height)
				currTile.topImages.rightEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (z < tiles.getHeight() - 1 && currTile.height > tiles.at(x, z + 1).height)
				currTile.topImages.bottomEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);

			// Rita hörn.
			if (x > 0 && z > 0 && currTile.height > tiles.at(x - 1, z - 1).height)
				currTile.topImages.nwCorner.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (x < tiles.getWidth() - 1 && z > 0 && currTile.height > tiles.at(x + 1, z - 1).height)
				currTile.topImages.neCorner.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (x > 0 && z < tiles.getHeight() - 1 && currTile.height > tiles.at(x - 1, z + 1).height)
				currTile.topImages.swCorner.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (x < tiles.getWidth() - 1 && z < tiles.getHeight() - 1 && currTile.height > tiles.at(x + 1, z + 1).height)
				currTile.topImages.seCorner.draw(
					xPos,
					yPos,
					dv,
					images
				);
		}
	}
	else if (y <= currTile.height - 1)
	{
		const int diff = y - (z == tiles.getHeight() - 1 ? 0 : tiles.at(x, z + 1).height);
		if (diff >= 0)
		{
			const float xPos = dv.getEffWidth() / 2.0f + x * tileWidth - centrePos.x;
			const float yPos = dv.getEffHeight() / 2.0f + z * tileTopHeight + tileTopHeight - (y + 1) * tileHeight  - centrePos.y;

			// Rita basen.
			currTile.sideImages.base.draw(
				xPos,
				yPos,
				dv,
				images
			);

			// Rita kanter.
			if (x > 0 && y >= tiles.at(x - 1, z).height)
				currTile.sideImages.leftEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);
			if (x < tiles.getWidth() - 1 && y >= tiles.at(x + 1, z).height)
				currTile.sideImages.rightEdge.draw(
					xPos,
					yPos,
					dv,
					images
				);

			// Rita gräs.
			if (y == currTile.height - 1)
			{
				currTile.sideImages.grass.draw(
					xPos,
					yPos,
					dv,
					images
				);
			}
		}
	}
}

int World::calculateStartX(Point centrePos, DirectV& dv)
{
	const int a = floor((0.0 - dv.getEffWidth() / 2.0 + centrePos.x) / tileWidth);
	const int lowerBound = 0;
	const int upperBound = tiles.getWidth();
	return a > lowerBound ? a < upperBound ? a : upperBound : lowerBound;
}

int World::calculateEndX(Point centrePos, DirectV& dv)
{
	const int a = floor((dv.getEffWidth() / 2.0 + centrePos.x) / tileWidth) + 1;
	const int lowerBound = 0;
	const int upperBound = tiles.getWidth();
	return a > lowerBound ? a < upperBound ? a : upperBound : lowerBound;
}

int World::calculateStartY(Point centrePos, int z, DirectV& dv)
{
	const int a = floor((0.0 - dv.getEffHeight() / 2.0 + centrePos.y - z * tileTopHeight) / tileTopHeight);
	const int lowerBound = 0;
	const int upperBound = getHeight();
	return a > lowerBound ? a < upperBound ? a : upperBound : lowerBound;
}

int World::calculateEndY(Point centrePos, int z, DirectV& dv)
{
	const int a = floor((dv.getEffHeight() + centrePos.y - z * tileTopHeight) / tileTopHeight) + 1;
	const int lowerBound = 0;
	const int upperBound = getHeight();
	return a > lowerBound ? a < upperBound ? a : upperBound : lowerBound;
}