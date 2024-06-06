#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Barriers {
	const static int barrierCount = 60;
	RectangleShape barriers[barrierCount];
protected:
	virtual void createBarriers() = 0;
	virtual void loadBarriers(RenderWindow& window) = 0;
	virtual RectangleShape* getBarriers() = 0;
	virtual int getBarriersCount() = 0;
};
