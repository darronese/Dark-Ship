#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "survivor.hpp"

class Header {
  public:

    Header(float& maxHealth, float& currentHealth, float& maxStamina, float& currentStamina);
    //visuals
    void draw(sf::RenderWindow& window, sf::View& view);
    void updateHealth(float newHealth);
    void updateStamina(float newStamina);

    float& getMaxHealth();
  private:
    sf::RectangleShape healthBar;
    sf::RectangleShape staminaBar;
    float& maxHealth;
    float& currentHealth;
    float& maxStamina;
    float& currentStamina;
};
