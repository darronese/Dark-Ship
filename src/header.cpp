#include "header.hpp"

using sf::Vector2f;

Header::Header(float& maxHealthRef, float& currentHealthRef, float& maxStaminaRef, float& currentStaminaRef)
  : maxHealth(maxHealthRef), currentHealth(currentHealthRef), maxStamina(maxStaminaRef), currentStamina(currentStaminaRef)
{
  float initialHealthRatio = currentHealth / maxHealth;
  // create the height and width of the bar
  healthBar.setSize(Vector2f(initialHealthRatio * 100.0f, 10.0f)); 
  //changes color to red
  healthBar.setFillColor(sf::Color::Red);
  // create the height and width of the bar
  staminaBar.setSize(Vector2f(100.f, 10.0f));
  //changes color to green
  staminaBar.setFillColor(sf::Color::Green);
}


void Header::draw(sf::RenderWindow& window, sf::View& guiView) 
{
  //save the original game view
  sf::View originalView = window.getView();

  //set the gui view
  window.setView(guiView);

  //position the health and stamina bars relative to the GUI view
  //here, (20.f, 20.f) positions the health bar 20 pixels from the top-left corner
  healthBar.setPosition(20.f, 20.f); // Health bar
  staminaBar.setPosition(20.f, 40.f); // Stamina bar, 20 pixels below the health bar

  //adjust sizes based on window dimensions for responsiveness
  float barWidth = window.getSize().x * 0.095f;
  float barHeight = 10.f;

  //ensure that maxHealth and maxStamina are not zero to avoid division by zero
  float healthRatio = (maxHealth != 0) ? (currentHealth / maxHealth) : 0.f;
  float staminaRatio = (maxStamina != 0) ? (currentStamina / maxStamina) : 0.f;

  //clamp the ratios between 0 and 1
  healthRatio = std::max(0.f, std::min(healthRatio, 1.f));
  staminaRatio = std::max(0.f, std::min(staminaRatio, 1.f));

  //let the sizes of the bars based on current health and stamina
  healthBar.setSize(Vector2f(barWidth * healthRatio, barHeight));
  staminaBar.setSize(Vector2f(barWidth * staminaRatio, barHeight));

  //Adjust colors based on health/stamina levels
  if (healthRatio > 0.5f)
  {
    healthBar.setFillColor(sf::Color::Red);
  }
  else if (healthRatio > 0.2f)
  {
    healthBar.setFillColor(sf::Color::Yellow);
  }
  else if (healthRatio > 0.005f)
  {
    healthBar.setFillColor(sf::Color::White);
  }
  else
  {
    healthBar.setFillColor(sf::Color::Transparent);
  }
  //stamina
  if (staminaRatio > 0.5f)
  {
    staminaBar.setFillColor(sf::Color::Green);
  }
  else if (staminaRatio > 0.2f)
  {
    staminaBar.setFillColor(sf::Color::Yellow);
  }
  else if (staminaRatio > 0.005f)
  {
    staminaBar.setFillColor(sf::Color::White);
  }
  else
  {
    staminaBar.setFillColor(sf::Color::Transparent);
  }

  //Draw the bars
  window.draw(healthBar);
  window.draw(staminaBar);

  //Ensure that the outline doesn't scale with the bar size
  sf::RectangleShape healthOutline = healthBar;
  healthOutline.setSize(Vector2f(barWidth, barHeight));
  healthOutline.setFillColor(sf::Color::Transparent);
  healthOutline.setOutlineThickness(2.f);
  healthOutline.setOutlineColor(sf::Color::Black);
  window.draw(healthOutline);

  sf::RectangleShape staminaOutline = staminaBar;
  staminaOutline.setSize(Vector2f(barWidth, barHeight));
  staminaOutline.setFillColor(sf::Color::Transparent);
  staminaOutline.setOutlineThickness(2.f);
  staminaOutline.setOutlineColor(sf::Color::Black);
  window.draw(staminaOutline);

  //Reset to the original (game) view
  window.setView(originalView);
}


void Header::updateHealth(float newHealth) 
{
  //makes sure the health cannot exceed current health
  if (newHealth > currentHealth)
  {
    return;
  }

  currentHealth = newHealth;
  healthBar.setSize(Vector2f(currentHealth / maxHealth * 100, 10));
  //ensures health is within range
  if (currentHealth < 0)
  {
    currentHealth = 0;
  }
  else if (currentHealth > maxHealth)
  {
    currentHealth = maxHealth;
  }
}


//same logic as health
void Header::updateStamina(float newStamina) 
{
  currentStamina = newStamina;
  if (currentStamina < 0)
  {
    currentStamina = 0;
  }
  if (currentStamina > maxStamina)
  {
    currentStamina = maxStamina;

  }
}

float& Header::getMaxHealth()
{
  return maxHealth;
}
