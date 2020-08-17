#include <sstream>
#include <iomanip>
#include <algorithm>
#include "directv.h"
#include "player.h"
#include "image.h"
#include "world.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		srand(time(0));

		DirectV dv(hInstance, L"Terrain");
		Timer t(30.0);

		SolidBrush blackBrush = dv.createSolidBrush(D2D1::ColorF(D2D1::ColorF::Black));
		SolidBrush whiteBrush = dv.createSolidBrush(D2D1::ColorF(D2D1::ColorF::White));
		Font font = dv.createFont(L"Consolas", 16.0f, L"sv-se");
		images_t images;
		loadImages(dv, images);

		Player plr({10.0 * tileWidth, 0.0, 10.0 * tileTopHeight});
		World world;

		while (dv.windowExists() && !dv.keyDown(VK_ESCAPE))
		{
			Direction d = DIR_NONE;
			if (dv.keyDown('W'))
			{
				d = Direction(d | DIR_N);
			}
			if (dv.keyDown('A'))
			{
				d = Direction(d | DIR_W);
			}
			if (dv.keyDown('S'))
			{
				d = Direction(d | DIR_S);
			}
			if (dv.keyDown('D'))
			{
				d = Direction(d | DIR_E);
			}
			plr.logic(d, world, dv);

			dv.beginDraw();
			dv.clear();

			const float screenScale = sqrtf((dv.getWidth() * dv.getHeight()) / (1366.0f * 768.0f)) * 2.0f;
			dv.scaleTransform(screenScale, screenScale, 0.0f, 0.0f);

			const Point projectedPlayerPos = plr.pos.project() - Point{0.0, plr.image.getHeight() / 2.0};
			const Point centrePos = {
				std::clamp(projectedPlayerPos.x, dv.getEffWidth() / 2.0, world.getWidth() * tileWidth - dv.getEffWidth() / 2.0),
				std::clamp(projectedPlayerPos.y, dv.getEffHeight() / 2.0, world.getDepth() * tileTopHeight - dv.getEffHeight() / 2.0)
			};
			int worldStartX = world.calculateStartX(centrePos, dv);
			int worldEndX = world.calculateEndX(centrePos, dv);
			for (int z = 0; z < world.getDepth(); z++)
			{
				int worldStartY = world.calculateStartY(centrePos, z, dv);
				int worldEndY = world.calculateEndY(centrePos, z, dv);
				for (int y = worldStartY; y < worldEndY; y++)
				{
					for (int x = worldStartX; x < worldEndX; x++)
					{
						world.drawTile(x, y, z, centrePos, dv, images);
					}
					if (z == floor(plr.pos.z / tileTopHeight) && y == floor(plr.pos.y / tileHeight))
					{
						plr.image.draw(
							(dv.getEffWidth() - plr.image.getWidth()) / 2.0f - (centrePos.x - projectedPlayerPos.x),
							(dv.getEffHeight() - plr.image.getHeight()) / 2.0f - (centrePos.y - projectedPlayerPos.y),
							dv,
							images
						);
					}
				}
			}
			
			dv.scaleTransform(1.0f, 1.0f, 0.0f, 0.0f);

			dv.fillRectangle(0.0f, 0.0f, dv.getWidth(), 19.0f, blackBrush);
			std::wstringstream ss;
			ss << std::fixed << std::setprecision(2) << t.getFramerate();
			ss << L" FPS    Tryck på escape för att avsluta.";
			dv.drawText(0.0f, 1.0f, dv.getWidth(), 17.0, ss.str().c_str(), font, whiteBrush);

			dv.endDraw();
			dv.updateWindow();
			t.wait();
		}
	}
	catch (const DirectVException& e)
	{
		std::stringstream ss;
		ss << "DirectV-fel: ";
		ss << e.what();
		MessageBoxA(NULL, ss.str().c_str(), "Fel", 0);
	}
	catch (...)
	{
		MessageBoxW(NULL, L"Fel", L"Fel", 0);
	}
}