#pragma once
#include "playerclass.hpp"
#include "header.hpp"
#include <SFML/Graphics.hpp>
#include <ostream>

//user can play as the survivor, therefore we inherit properties from player that is universal
class Survivor : public Player {
  public:
    //constructor
    Survivor(sf::RenderWindow& window);
    //player movement
    void handlePlayerMovement(float dt, Walls& walls);
    void directionUpdate(sf::RenderWindow& window);
    void directionLook(sf::RenderWindow& window, float targetX, float targetY);
    sf::Vector2f getSize();
    //health bar and stamina bar stuff
    float getStamina();
    float getHealth() const;
    sf::Sprite getPlayerSprite();
    void setStamina(float adjustment);
    void setHealth(float adjustment);
    void updateHealth(float damage);
  private:
    sf::Vector2f position;
    sf::Vector2f size;
    float stamina;
    float health;
    float currentHealth;
    int animationCycle = 0;
};
