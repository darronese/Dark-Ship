#include "wall.hpp"

using sf::Vector2f;

Walls::Walls() 
{
	createBarriers();
}

Walls::~Walls()
{
}

void Walls::createBarriers()
{
	//y = 4000 is bottom of map, x = 
	for (int i = 0; i < wallCount; i++)
	{
		walls[i].setScale(Vector2f(5, 5));
		walls[i].setFillColor(sf::Color(0, 0, 0, 0));

		//debug walls color -- Remove Comment
		//walls[i].setFillColor(Color(255, 0, 0, 255));
	}
	//Left Wall
	walls[0].setPosition(0, 0);
	walls[0].setSize(Vector2f(16, 800));
	//Top Wall
	walls[1].setPosition(0, 0);
	walls[1].setSize(Vector2f(544, 16));
	//Bottom Wall
	walls[2].setPosition(0, 4000);
	walls[2].setSize(Vector2f(544, 16));

	//Left Section - Left Inner Walls
	walls[3].setPosition(560, 0);
	walls[3].setSize(Vector2f(32, 96));
	walls[4].setPosition(560, 720);
	walls[4].setSize(Vector2f(32, 96));
	walls[5].setPosition(560, 1120);
	walls[5].setSize(Vector2f(384, 16));
	walls[6].setPosition(560, 1440);
	walls[6].setSize(Vector2f(32, 192));
	walls[7].setPosition(560, 2640);
	walls[7].setSize(Vector2f(384, 16));
	walls[8].setPosition(0, 2000);
	walls[8].setSize(Vector2f(112, 16));
	walls[9].setPosition(560, 2640);
	walls[9].setSize(Vector2f(32, 112));
	walls[10].setPosition(560, 3440);
	walls[10].setSize(Vector2f(32, 112));

	//Left Section - Middle Inner Walls
	walls[11].setPosition(2320, 320);
	walls[11].setSize(Vector2f(32, 176));
	walls[12].setPosition(2320, 1440);
	walls[12].setSize(Vector2f(32, 192));
	walls[13].setPosition(2320, 2640);
	walls[13].setSize(Vector2f(32, 224));

	//Middle Section - top Walls--------------------------------------------

	walls[14].setPosition(2640, 0);
	walls[14].setSize(Vector2f(16, 128));
	walls[15].setPosition(2640, 560);
	walls[15].setSize(Vector2f(640, 16));

	walls[16].setPosition(2640, 4000);
	walls[16].setSize(Vector2f(16, -128));
	walls[17].setPosition(2640, 3280);
	walls[17].setSize(Vector2f(640, 16));
	//Middle Section - Room 2 Walls-------------------------------------------
	walls[14].setPosition(4000, 200);
	walls[14].setSize(Vector2f(1400, 2));
	walls[15].setPosition(2320, 320);
	walls[15].setSize(Vector2f(32, 176));
	walls[15].setPosition(2320, 1440);
	walls[15].setSize(Vector2f(32, 192));
	walls[15].setPosition(2320, 2640);
	walls[15].setSize(Vector2f(32, 224));
	//Middle Section - Room 3 Walls--------------------------------------------
	walls[14].setPosition(4000, 200);
	walls[14].setSize(Vector2f(1400, 2));
	walls[15].setPosition(2320, 320);
	walls[15].setSize(Vector2f(32, 176));
	walls[15].setPosition(2320, 1440);
	walls[15].setSize(Vector2f(32, 192));
	walls[15].setPosition(2320, 2640);
	walls[15].setSize(Vector2f(32, 224));
	//Middle Section - Room 4 Walls--------------------------------------------
	walls[14].setPosition(4000, 200);
	walls[14].setSize(Vector2f(1400, 2));
	walls[15].setPosition(2320, 320);
	walls[15].setSize(Vector2f(32, 176));
	walls[15].setPosition(2320, 1440);
	walls[15].setSize(Vector2f(32, 192));
	walls[15].setPosition(2320, 2640);
	walls[29].setSize(Vector2f(32, 224));

	//Right Section - Outer Walls
	walls[30].setPosition(5840, 2160);
	walls[30].setSize(Vector2f(32, 384));
	walls[31].setPosition(5840, 0);
	walls[31].setSize(Vector2f(32, 352));
	walls[32].setPosition(5840, 2880);
	walls[32].setSize(Vector2f(208, 32));
	walls[33].setPosition(5840, 880);
	walls[33].setSize(Vector2f(208, 32));
	walls[34].setPosition(7120, 1200);
	walls[34].setSize(Vector2f(32, 288));
	walls[35].setPosition(6880, 880);
	walls[35].setSize(Vector2f(32, 48));
	walls[36].setPosition(6960, 960);
	walls[36].setSize(Vector2f(32, 48));
	walls[37].setPosition(7040, 1040);
	walls[37].setSize(Vector2f(32, 48));

	walls[38].setPosition(6880, 2800);
	walls[38].setSize(Vector2f(32, 48));
	walls[39].setPosition(6960, 2720);
	walls[39].setSize(Vector2f(32, 48));
	walls[40].setPosition(7040, 2640);
	walls[40].setSize(Vector2f(32, 48));
}

void Walls::loadBarriers(sf::RenderWindow& window)
{
	for (int i = 0; i < wallCount; i++)
	{
		window.draw(walls[i]);
	}
}

sf::RectangleShape* Walls::getBarriers() {
	return walls;
}

int Walls::getBarriersCount() {
	return wallCount;
}
