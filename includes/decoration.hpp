#pragma once
#include "SFML/Graphics.hpp"
#include "barrier.hpp"
#include "survivor.hpp"

//decorations inherits from barriers so that player cannot walk through walls
class Decorations : public Barriers {
  public:
    Decorations();
    ~Decorations();
    void loadBarriers(sf::RenderWindow& window);
    sf::RectangleShape* getBarriers();
    int getBarriersCount();
    void checkCollision(Survivor& survivor);
  private:
    void createBarriers();
    const static int decorationCount = 33;
    sf::Sprite decorations[decorationCount];
    sf::RectangleShape decorationBorder[decorationCount];
    sf::Texture texture;
};
