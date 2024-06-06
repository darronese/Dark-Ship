#pragma once
#include "playerclass.hpp"
#include "header.hpp"
#include <SFML/Graphics.hpp>
#include <ostream>
using namespace sf;

class Survivor : public Player {

public:
  //constructor
	Survivor(RenderWindow& window);
  //player movement
	void handlePlayerMovement(float dt, Walls& walls);
	void directionUpdate(RenderWindow& window);
	void directionLook(RenderWindow& window, float targetX, float targetY);
	Vector2f getSize();
  //health bar and stamina bar stuff
	float getStamina();
	float getHealth() const;
	Sprite getPlayerSprite();
	void setStamina(float adjustment);
	void setHealth(float adjustment);
	void updateHealth(float damage);
private:
	Vector2f position;
	Vector2f size;
	float stamina;
	float health;
	float currentHealth;
	int animationCycle = 0;
};
