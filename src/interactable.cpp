#include "interactable.hpp"

Interactable::Interactable(const std::string& imagePath)
{
  sf::Texture texture;
	if (!texture.loadFromFile(imagePath)) {
		std::cerr << "fail to load ENGINE" << std::endl;
	}
	//sets sprite texture and coord to center of texture
	sprite.setTexture(texture);
	sprite.setScale(10, 10);
	float texWidth = sprite.getTextureRect().getPosition().x;
	float texHeight = sprite.getTextureRect().getPosition().y;
	float xOffset = -texWidth / 2.0f;
	float yOffset = -texHeight / 2.0f;
	sprite.setOrigin(texWidth / 2.0f, texHeight / 2.0f);
}

void Interactable::remove()
{
	mInteractionRange = 0;
	mHasCollision = false;
	mExists = false;
}

void Interactable::draw(sf::RenderWindow& window, sf::Vector2f position) const 
{
	sf::Texture generatorTexture;
	if (!generatorTexture.loadFromFile("../data/images/Engine.png")) 
  {
		std::cerr << "Failed to load generator texture!" << std::endl;
		return;
	}
	sf::Sprite generatorSprite(generatorTexture);
	generatorSprite.setScale(2.0f, 2.0f);
	generatorSprite.setPosition(position);
	window.draw(generatorSprite);
}
