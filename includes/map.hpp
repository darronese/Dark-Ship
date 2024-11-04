#pragma once

#include "SFML/Graphics.hpp"

//the map inherits from SFML's drawable and transformable class
//the drawable class allows for the map to be drawn onto the screen
//in order to do so, we would need map to inherit from drawable
//the transformable class allows flexibility and allowed us to be able to manage the map
class Map : public sf::Drawable, public sf::Transformable
{
  public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray mVertices;
    sf::Texture mTileset;
};
