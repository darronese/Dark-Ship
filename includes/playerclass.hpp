#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "wall.hpp"

using namespace sf;
using std::cerr;
using std::endl;


// base class
class Player {

public:
    //constructor
    Player();
    Player(const std::string& imagePath, float speed);
    //movement
    void move(float x, float y);
    void draw(RenderWindow& window);
    //stop people from going off map
    bool CollidesWithWalls(Walls& walls, float dt);
    virtual void directionLook(RenderWindow& window, float targetX, float targetY) = 0;
    //getters and setters
    Vector2f getPosition();
    float getPlayerSpeed();
    void setSpeed(float speedMod);
    void setPosition(float x, float y);
protected:
    Sprite sprite;
    Texture texture;
    float speed;
};
