#pragma once
#include "SFML/Graphics.hpp"
#include "barrier.hpp"
using namespace sf;

class Walls : Barriers {
  //construct walls with count of 60
	const static int wallCount = 60;
	RectangleShape walls[wallCount];
	void createBarriers();
public:
  //construct the barriers
	Walls();
	~Walls();
	void loadBarriers(RenderWindow& window);
	RectangleShape* getBarriers();
	int getBarriersCount();
};
