#include "header.hpp"
using namespace sf;

Header::Header(float& maxHealthRef, float& currentHealthRef, float& maxStaminaRef, float& currentStaminaRef)
    : maxHealth(maxHealthRef), currentHealth(currentHealthRef), maxStamina(maxStaminaRef), currentStamina(currentStaminaRef)
{

    float initialHealthRatio = currentHealth / maxHealth;
    // create the height and width of the bar
    healthBar.setSize(Vector2f(initialHealthRatio * 100.0f, 10.0f)); 
    //changes color to red
    healthBar.setFillColor(Color::Red);

    // create the height and width of the bar
    staminaBar.setSize(Vector2f(100.f, 10.0f));
    //changes color to green
    staminaBar.setFillColor(Color::Green);
}


void Header::draw(RenderWindow& window, View& view) {
    // Health bar
    healthBar.setSize(Vector2f(currentHealth / maxHealth * 100, 10)); 
    healthBar.setPosition(view.getCenter().x - 465, view.getCenter().y + 210);
    healthBar.setOutlineThickness(4.f);
    healthBar.setOutlineColor(Color::Black);
    window.draw(healthBar);

    // Stamina bar
    staminaBar.setSize(Vector2f(currentStamina / maxStamina * 100, 10));
    staminaBar.setPosition(view.getCenter().x - 465, view.getCenter().y + 240);
    staminaBar.setOutlineThickness(4.f);
    staminaBar.setOutlineColor(Color::Black);
    window.draw(staminaBar);
}


void Header::updateHealth(float newHealth) {
    if (newHealth > currentHealth)
        return;

    currentHealth = newHealth;

    healthBar.setSize(Vector2f(currentHealth / maxHealth * 100, 10));
    if (currentHealth < 0)
        currentHealth = 0;
    else if (currentHealth > maxHealth)
        currentHealth = maxHealth;
}


void Header::updateStamina(float newStamina) {
    currentStamina = newStamina;

    if (currentStamina < 0)
        currentStamina = 0;
    if (currentStamina > maxStamina)
        currentStamina = maxStamina;
}

float& Header::getMaxHealth()
{
    return maxHealth;
}
