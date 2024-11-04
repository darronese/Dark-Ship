#pragma once
#include "playerclass.hpp"
#include "survivor.hpp"

//monster class inherits from player: in future updates, we can allow another person to play as the monster
class Monster : public Player 
{
  public:
    Monster(sf::RenderWindow& window);
    void handlePlayerMovement(float dt, Walls& walls, Survivor& survivor, sf::RenderWindow& window);
    sf::Vector2f getSize();
    void setPosition(float x, float y);
    void directionLook(sf::RenderWindow& window, float targetX, float targetY);
    sf::RectangleShape getMonsterRadius();
    sf::RectangleShape getAttackRadius();
    sf::Vector2f changeDirection();
    void directionUpdate(sf::RenderWindow& window, Survivor& survivor);
    void attackPlayer(Survivor& survivor);
    void resetAttackCooldown();

  protected:
    sf::Vector2f position;
    sf::Vector2f size;
    float speed = .08f;
    // Pathfinding/Attack Radius
    sf::RectangleShape MonsterRadius;
    sf::RectangleShape attackRadius;
    // LOS variables
    sf::RectangleShape LOS;
    bool lostLOS;
    // Initial movement direction
    sf::Vector2f moveDirection = sf::Vector2f(1.0f, 0.0f);

    // New member variables for attack behavior
    float attackCooldown = 5.0f; // Cooldown time for monster's attack
    sf::Clock attackClock; // Clock to track attack cooldown
    bool isFrozen = false; // Flag to indicate if the monster is frozen
    sf::Clock freezeClock; // Clock to track freeze duration
};


