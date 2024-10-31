#include "visioncone.hpp"

VisionCone::VisionCone() {
  texture.loadFromFile("../data/images/visionCone.png");
  cone.setTexture(texture);
}

void VisionCone::update(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) 
{
  // Calculate angle between player and mouse
  float x1 = playerPosition.x;
  float y1 = playerPosition.y;

  //pythag for finding angle of rotation
  float adj = mousePosition.x - x1;
  float op = mousePosition.y - y1;

  //calc angle for direction
  float angleRads = atan2(op, adj);
  float angleDeg = (angleRads * 180 / 3.141592654);
  cone.setScale(15, 15);
  cone.setOrigin(cone.getLocalBounds().width / 2, cone.getLocalBounds().height / 2 + 1);
  cone.setPosition(playerPosition.x, playerPosition.y - 50);
  cone.setRotation(angleDeg + 90);
}

void VisionCone::draw(sf::RenderWindow& window) {
  /*
  //let it so the environment outside the cone isn't completely dark
  cone.setColor(sf::Color(255, 255, 255, 225));
  window.draw(cone);
  */
}
