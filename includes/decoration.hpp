#pragma once
#include "SFML/Graphics.hpp"
#include "barrier.hpp"
#include "survivor.hpp"
using namespace sf;

class Decorations : public Barriers {
public:
	Decorations();
	~Decorations();
	void loadBarriers(RenderWindow& window);
	RectangleShape* getBarriers();
	int getBarriersCount();
	void checkCollision(Survivor& survivor);
private:
	void createBarriers();
	const static int decorationCount = 33;
	Sprite decorations[decorationCount];
	RectangleShape decorationBorder[decorationCount];
	Texture texture;
};
