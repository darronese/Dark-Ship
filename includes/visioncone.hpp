#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class VisionCone {
public:
    //constructor
    VisionCone();
    void update(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window);
private:
    sf::Sprite cone;
    sf::Texture texture;
};
