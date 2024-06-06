#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "survivor.hpp"

using namespace sf;

class Header {
public:
   
    Header(float& maxHealth, float& currentHealth, float& maxStamina, float& currentStamina);
    //visuals
    void draw(RenderWindow& window, View& view);
    void updateHealth(float newHealth);
    void updateStamina(float newStamina);

    float& getMaxHealth();
private:
    RectangleShape healthBar;
    RectangleShape staminaBar;
    float& maxHealth;
    float& currentHealth;
    float& maxStamina;
    float& currentStamina;
};
