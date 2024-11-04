#pragma once
#include <SFML/Graphics.hpp>

//base barriers class for decorations and so users cannot walk through walls
class Barriers 
{
  const static int barrierCount = 60;
  sf::RectangleShape barriers[barrierCount];
  protected:
  virtual void createBarriers() = 0;
  virtual void loadBarriers(sf::RenderWindow& window) = 0;
  virtual sf::RectangleShape* getBarriers() = 0;
  virtual int getBarriersCount() = 0;
};
