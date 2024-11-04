#include "playerclass.hpp"

Player::Player()
{
  ;
}

Player::Player(const std::string& imagePath, float speed) : speed(speed)
{
  if (!texture.loadFromFile(imagePath)) 
  {
    std::cerr << "fail to load player" << std::endl;
  }
  sprite.setScale(sf::Vector2f(5, 5));
  //sets sprite texture and coord to center of texture
  sprite.setTexture(texture);
  float texWidth = sprite.getTextureRect().getPosition().x;
  float texHeight = sprite.getTextureRect().getPosition().y;
  float xOffset = -texWidth / 2.0f;
  float yOffset = -texHeight / 2.0f;
  sprite.setOrigin(texWidth / 2.0f, texHeight / 2.0f);
}

void Player::move(float x, float y)
{
  sprite.move(x * speed, y * speed);
}

void Player::draw(sf::RenderWindow& window)
{
  window.draw(sprite);
}

sf::Vector2f Player::getPosition() 
{
  return sprite.getPosition();
}

float Player::getPlayerSpeed() 
{
  return speed;
}

void Player::setSpeed(float speedMod) 
{
  speed = speedMod;
}

void Player::setPosition(float x, float y) 
{
  sprite.setPosition(x, y);
}

// Check for collisions with walls
bool Player::CollidesWithWalls(Walls& walls, float dt) 
{
  sf::RectangleShape* worldBarriers = walls.getBarriers();
  for (int i = 0; i < walls.getBarriersCount(); i++)
  {
    if (worldBarriers[i].getGlobalBounds().intersects(sprite.getGlobalBounds())) 
    {
      return true;
    }
  }
  return false;
}
