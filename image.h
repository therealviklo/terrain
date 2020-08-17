#pragma once
#include <array>
#include <memory>
#include "directv.h"

/*
 * För att lägga till en ny bild ska du:
 * - Lägga till ett ID i ImageID
 * - Ändra storleken av images_t
 * - Lägga till en rad i loadImages() som laddar bilden
*/

enum ImageID
{
	LOWERCASEMU,
	TILES
};
typedef std::array<std::unique_ptr<Bitmap>, 2 /* <-- ska vara antalet bilder */> images_t;

void loadImages(DirectV& dv, images_t& images);

class Image
{
private:
	ImageID imageID;
	bool entireImage;
	float x;
	float y;
	float width;
	float height;
	float dispWidth;
	float dispHeight;
public:
	Image() noexcept;
	Image(ImageID imageID, float x, float y, float width, float height) noexcept;
	Image(ImageID imageID, float dispWidth, float dispHeight) noexcept;
	Image(ImageID imageID, float dispWidth, float dispHeight, float x, float y, float width, float height) noexcept;

	void draw(float x, float y, DirectV& dv, images_t& images) const;

	Bitmap& getBitmap(images_t& images) const {return *images[imageID];}
	const Bitmap& getBitmap(const images_t& images) const {return *images[imageID];}

	float getWidth() const noexcept {return dispWidth;}
	float getHeight() const noexcept {return dispHeight;}
	void setWidth(float width) {dispWidth = width;}
	void setHeight(float height) {dispHeight = height;}
};