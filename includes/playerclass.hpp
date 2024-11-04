#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "wall.hpp"

//base class
class Player {
  public:
    //constructor
    Player();
    Player(const std::string& imagePath, float speed);
    //movement
    void move(float x, float y);
    void draw(sf::RenderWindow& window);
    //stop people from going off map
    bool CollidesWithWalls(Walls& walls, float dt);
    virtual void directionLook(sf::RenderWindow& window, float targetX, float targetY) = 0;
    //getters and setters
    sf::Vector2f getPosition();
    float getPlayerSpeed();
    void setSpeed(float speedMod);
    void setPosition(float x, float y);
  protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};
