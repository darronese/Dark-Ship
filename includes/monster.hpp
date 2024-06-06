#pragma once
#include "playerclass.hpp"
#include "survivor.hpp"

class Monster : public Player {

public:
    Monster(RenderWindow& window);
    void handlePlayerMovement(float dt, Walls& walls, Survivor& survivor, RenderWindow& window);
    Vector2f getSize();
    void setPosition(float x, float y);
    void directionLook(RenderWindow& window, float targetX, float targetY);
    RectangleShape getMonsterRadius();
    RectangleShape getAttackRadius();
    sf::Vector2f changeDirection();
    void directionUpdate(RenderWindow& window, Survivor& survivor);
    void attackPlayer(Survivor& survivor);
    void resetAttackCooldown();

protected:
    Vector2f position;
    Vector2f size;
    float speed = .08f;
    // Pathfinding/Attack Radius
    RectangleShape MonsterRadius;
    RectangleShape attackRadius;
    // LOS variables
    RectangleShape LOS;
    bool lostLOS;
    // Initial movement direction
    sf::Vector2f moveDirection = sf::Vector2f(1.0f, 0.0f);

    // New member variables for attack behavior
    float attackCooldown = 5.0f; // Cooldown time for monster's attack
    sf::Clock attackClock; // Clock to track attack cooldown
    bool isFrozen = false; // Flag to indicate if the monster is frozen
    sf::Clock freezeClock; // Clock to track freeze duration

    
};


