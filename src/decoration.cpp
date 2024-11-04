#include "decoration.hpp"

using sf::IntRect;

Decorations::Decorations() {
	createBarriers();
}

void Decorations::createBarriers()
{

    if (!texture.loadFromFile("../data/images/SciFi_Tiles.png")) {
        std::cerr << "Error loading texture from ../data/images/SciFi_Tiles.png" << std::endl;
    }
	//y = 4000 is bottom of map, x = 
	for (int i = 0; i < decorationCount; i++)
	{
		decorations[i].setTexture(texture);
		decorations[i].setScale(sf::Vector2f(5, 5));
		decorationBorder[i].setScale(sf::Vector2f(5, 5));
		decorationBorder[i].setFillColor(sf::Color::Red);
	}
	//Escape Pod terminal
	decorations[0].setTextureRect(IntRect(18 * 16, 0 * 16, 16, 16));
	decorations[0].setPosition(6400, 1840);
	decorations[1].setTextureRect(IntRect(19 * 16, 0 * 16, 16, 16));
	decorations[1].setPosition(6480, 1840);
	decorations[2].setTextureRect(IntRect(3 * 16, 0 * 16, 16, 16));
	decorations[2].setPosition(6400, 1920);
	decorations[3].setTextureRect(IntRect(4 * 16, 0 * 16, 16, 16));
	decorations[3].setPosition(6480, 1920);

	//Cockpit chairs
	decorations[4].setTextureRect(IntRect(79 * 16, 0 * 16, 16, 16));
	decorations[4].setPosition(6320, 1920);
	decorations[5].setTextureRect(IntRect(82 * 16, 0 * 16, 16, 16));
	decorations[5].setPosition(6560, 1920);
	//Cockpit flags
	decorations[6].setTextureRect(IntRect(43 * 16, 0 * 16, 16, 16));
	decorations[6].setPosition(6000, 2000);
	decorations[7].setTextureRect(IntRect(42 * 16, 0 * 16, 16, 16));
	decorations[7].setPosition(6000, 2080);
	decorations[8].setTextureRect(IntRect(43 * 16, 0 * 16, 16, 16));
	decorations[8].setPosition(6000, 1680);
	decorations[9].setTextureRect(IntRect(42 * 16, 0 * 16, 16, 16));
	decorations[9].setPosition(6000, 1760);

	//Cockpit windows
	decorations[10].setTextureRect(IntRect(84 * 16, 0 * 16, 16, 16));
	decorations[10].setPosition(77 * 80, 12.5 * 80);
	decorations[11].setTextureRect(IntRect(85 * 16, 0 * 16, 16, 16));
	decorations[11].setPosition(6240, 12.5 * 80);

	decorations[12].setTextureRect(IntRect(84 * 16, 0 * 16, 16, 16));
	decorations[12].setPosition(6480, 12.5 * 80);
	decorations[13].setTextureRect(IntRect(85 * 16, 0 * 16, 16, 16));
	decorations[13].setPosition(6560, 12.5 * 80);

	//Cockpit wall decor
	decorations[14].setTextureRect(IntRect(8 * 16, 0 * 16, 16, 16));
	decorations[14].setPosition(6320, 12.5 * 80);
	decorations[15].setTextureRect(IntRect(9 * 16, 0 * 16, 16, 16));
	decorations[15].setPosition(6400, 12.5 * 80);

	decorations[16].setTextureRect(IntRect(7 * 16, 0 * 16, 16, 16));
	decorations[16].setPosition(6640, 12.5 * 80);

	//Cockpit terminals
	decorations[17].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[17].setPosition(78 * 80, 17 * 80);
	decorations[18].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[18].setPosition(80 * 80, 17 * 80);
	decorations[19].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[19].setPosition(82 * 80, 17 * 80);
	decorations[20].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[20].setPosition(78 * 80, 32 * 80);
	decorations[21].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[21].setPosition(80 * 80, 32 * 80);
	decorations[22].setTextureRect(IntRect(40 * 16, 0 * 16, 16, 16));
	decorations[22].setPosition(82 * 80, 32 * 80);

	//Terminal Chairs
	decorations[23].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[23].setPosition(78 * 80, 16 * 80);
	decorations[24].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[24].setPosition(80 * 80, 16 * 80);
	decorations[25].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[25].setPosition(82 * 80, 16 * 80);
	decorations[26].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[26].setPosition(78 * 80, 31 * 80);
	decorations[27].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[27].setPosition(80 * 80, 31 * 80);
	decorations[28].setTextureRect(IntRect(83 * 16, 0 * 16, 16, 16));
	decorations[28].setPosition(82 * 80, 31 * 80);

	//Escape Door
	decorations[29].setTextureRect(IntRect(86 * 16, 0 * 16, 16, 16));
	decorations[29].setPosition(51 * 80, 8 * 80);
	decorations[30].setTextureRect(IntRect(87 * 16, 0 * 16, 16, 16));
	decorations[30].setPosition(52 * 80, 8 * 80);
	decorations[31].setTextureRect(IntRect(88 * 16, 0 * 16, 16, 16));
	decorations[31].setPosition(51 * 80, 7 * 80);
	decorations[32].setTextureRect(IntRect(89 * 16, 0 * 16, 16, 16));
	decorations[32].setPosition(52 * 80, 7 * 80);

}

Decorations::~Decorations()
{
}

void Decorations::loadBarriers(sf::RenderWindow& window)
{
	for (int i = 0; i < decorationCount; i++) {
		window.draw(decorations[i]);
		window.draw(decorationBorder[i]);
	}
}

sf::RectangleShape* Decorations::getBarriers()
{
	return nullptr;
}

int Decorations::getBarriersCount()
{
	return 0;
}
void Decorations::checkCollision(Survivor& survivor) {
	if (decorationBorder[32].getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
	}
}
