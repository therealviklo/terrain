#pragma once
#include <limits>
#include "image.h"
#include "matrix.h"
#include "geoutils.h"
#include "directv.h"

constexpr float tileWidth = 32.0f;
constexpr float tileHeight = 16.0f;
constexpr float tileTopHeight = 32.0f;

struct Tile
{
	struct TopImages {
		Image base;
		Image topEdge;
		Image rightEdge;
		Image bottomEdge;
		Image leftEdge;
		Image neCorner;
		Image seCorner;
		Image swCorner;
		Image nwCorner;
	} topImages;
	struct SideImages {
		Image base;
		Image rightEdge;
		Image leftEdge;
		Image grass;
	} sideImages;
	unsigned short height;
};

class World
{
private:
	Matrix<Tile> tiles;
public:
	World();

	void drawTile(int x, int y, int z, Point centrePos, DirectV& dv, images_t& images);

	unsigned getWidth() const noexcept {return tiles.getWidth();}
	unsigned getDepth() const noexcept {return tiles.getHeight();}
	constexpr unsigned getHeight() const noexcept {return std::numeric_limits<decltype(Tile::height)>::max() + 1;}

	int calculateStartX(Point centrePos, DirectV& dv);
	int calculateEndX(Point centrePos, DirectV& dv);
	int calculateStartY(Point centrePos, int z, DirectV& dv);
	int calculateEndY(Point centrePos, int z, DirectV& dv);

	Tile& tileAt(int x, int y) {return tiles.at(x, y);}
};