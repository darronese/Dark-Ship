#pragma once
#include "SFML/Graphics.hpp"
#include "barrier.hpp"

//our base walls inherits from barriers which stops players from moving out of bounds from the map
class Walls : Barriers 
{
  //construct walls with count of 60
  const static int wallCount = 60;
  sf::RectangleShape walls[wallCount];
  void createBarriers();
  public:
  //construct the barriers
  Walls();
  ~Walls();
  void loadBarriers(sf::RenderWindow& window);
  sf::RectangleShape* getBarriers();
  int getBarriersCount();
};
