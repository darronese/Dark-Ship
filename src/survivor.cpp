#include "survivor.hpp"
#include "header.hpp"
#include "VisionCone.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using sf::IntRect;
using sf::Keyboard;

Survivor::Survivor(sf::RenderWindow& window) :Player("../data/images/Character_Sheet.png", 1.f),health(100.0f)//image location on file, speed
{
  size = sf::Vector2f(5.f, 5.f);
  stamina = 100;
  sprite.setTextureRect(IntRect(2 * 16, 0 * 16, 16, 16));
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
  sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}


sf::Vector2f Survivor::getSize() 
{
  return size;
}

float Survivor::getStamina() 
{
  return stamina;
}


void Survivor::setStamina(float adjustment) 
{
  if (stamina < 0) 
  {
    stamina = 0;
  }
  else if (stamina > 100) 
  {
    stamina = 100;
  }
  else 
  {
    stamina += adjustment;
  }
}

void Survivor::setHealth(float adjustment) 
{
  health += adjustment;
  if (health < 0) 
  {
    health = 0;
  }
  if (health > 100) 
  {
    health = 100;
  }
}



//survivor movement
void Survivor::handlePlayerMovement(float dt, Walls& walls)
{
  //loads in texture
  texture.loadFromFile("../data/images/Character_Sheet.png");
  sprite.setTexture(texture);
  //check to see if key is pressed with sprint
  if (Keyboard::isKeyPressed(Keyboard::LShift) && getStamina() > 0) 
  {
    setSpeed(.15f);
    setStamina(-.6f);
  }
  else 
  {
    setSpeed(0.075f);
    setStamina(.1f);
  }
  //left player movement
  if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) 
  {
    move(-1.f * dt, 0.f);

    //animation cycle
    ++animationCycle;
    if (animationCycle >= 0 && animationCycle < 10) 
    {
      sprite.setScale(-5, 5);
      sprite.setTextureRect(IntRect(128, 0 * 16, 16, 16));
    }
    if (animationCycle == 10) 
    {
      sprite.setScale(-5, 5);
      sprite.setTextureRect(IntRect(32, 0 * 16, 16, 16));
    }
    if (animationCycle == 20) 
    {
      sprite.setScale(-5, 5);
      sprite.setTextureRect(IntRect(144, 0 * 16, 16, 16));

    }
    if (animationCycle == 30) 
    {
      sprite.setScale(-5, 5);
      sprite.setTextureRect(IntRect(32, 0 * 16, 16, 16));
    }
    if (animationCycle >= 40) animationCycle = 0;
    //checks to see if collided with wall
    if (CollidesWithWalls(walls, dt)) 
    {
      move(1.f * dt, 0.f);
    }
  }
  //down player movement
  if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) 
  {
    move(0.f, 1.f * dt);
    ++animationCycle;
    if (animationCycle >= 0 && animationCycle < 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(64, 0 * 16, 16, 16));
    }
    if (animationCycle == 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(0, 0 * 16, 16, 16));
    }
    if (animationCycle == 20) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(80, 0 * 16, 16, 16));
    }
    if (animationCycle == 30) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(0, 0 * 16, 16, 16));
    }
    if (animationCycle >= 40)
    {
      animationCycle = 0;
    }

    if (CollidesWithWalls(walls, dt)) 
    {
      move(0.f, -1.f * dt);
    }
  }
  //right player movement
  if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) 
  {
    move(1.f * dt, 0.f);
    ++animationCycle;
    if (animationCycle >= 0 && animationCycle < 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(128, 0 * 16, 16, 16));
    }
    if (animationCycle == 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(32, 0 * 16, 16, 16));
    }
    if (animationCycle == 20) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(144, 0 * 16, 16, 16));
    }
    if (animationCycle == 30) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(32, 0 * 16, 16, 16));
    }
    if (animationCycle >= 40) 
    {
      animationCycle = 0;

    }
    if (CollidesWithWalls(walls, dt)) 
    {
      move(-1.f * dt, -1.f);
    }
  }
  //up player movement
  if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) 
  {
    move(0.f, -1.f * dt);
    ++animationCycle;
    if (animationCycle >= 0 && animationCycle < 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(96, 0 * 16, 16, 16));
    }
    if (animationCycle == 10) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(16, 0 * 16, 16, 16));
    }
    if (animationCycle == 20) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(112, 0 * 16, 16, 16));

    }
    if (animationCycle == 30) 
    {
      sprite.setScale(5, 5);
      sprite.setTextureRect(IntRect(16, 0 * 16, 16, 16));
    }
    if (animationCycle == 40)
    {
      animationCycle = 0;
    }
    if (CollidesWithWalls(walls, dt)) 
    {
      move(0.f, 1.f * dt);
    }
  }
}

void Survivor::directionUpdate(sf::RenderWindow& window) 
{
  sf::Mouse mouse;
  //init values
  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
  sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosition);

  float x2 = mousePosView.x;
  float y2 = mousePosView.y;

  VisionCone visionCone;
}

void Survivor::directionLook(sf::RenderWindow& window, float x2, float y2) 
{
  float x1 = sprite.getPosition().x;
  float y1 = sprite.getPosition().y;

  //pythag for finding angle of rotation
  float adj = x2 - x1;
  float op = y2 - y1;

  //calc angle for direction
  float angleRads = atan2(op, adj);
  float angleDeg = (angleRads * 180 / 3.141592654);

  //Adjust sprite based on direction looked
  if (angleDeg < 45 && angleDeg > -45 && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S)) 
  {
    sprite.setScale(5.f, 5.f);
    sprite.setTextureRect(IntRect(2 * 16, 0 * 16, 16, 16));
  }
  if (angleDeg < -45 && angleDeg > -135 && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S)) 
  {
    sprite.setTextureRect(IntRect(1 * 16, 0 * 16, 16, 16));
  }
  if (angleDeg < -135 && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) || angleDeg > 135 && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S)) 
  {
    sprite.setScale(-5.f, 5.f);
    sprite.setTextureRect(IntRect(2 * 16, 0 * 16, 16, 16));
  }
  if (angleDeg < 135 && angleDeg > 45 && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S)) 
  {
    sprite.setTextureRect(IntRect(0 * 16, 0 * 16, 16, 16));
  }
}

sf::Sprite Survivor::getPlayerSprite() 
{
  return sprite;
}

void Survivor::updateHealth(float damage) 
{
  health -= damage;
  if (health < 0) 
  {
    health = 0;
  }
}

float Survivor::getHealth() const 
{
  return health;
}
