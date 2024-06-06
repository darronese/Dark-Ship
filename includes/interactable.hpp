#pragma once
#pragma once
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics.hpp>
#include "barrier.hpp"
#include "survivor.hpp"
#include "monster.hpp"

using sf::Vector2f;

class Interactable {
public:
	Interactable() { ; }
	Interactable(const std::string& imagePath);

	void remove();

	void draw(RenderWindow& window, Vector2f position) const;

protected:
	//coordinate position on the map
	Vector2f mPosition;
	//max number of tiles between player and interactable for interaction to be allowed
	//0 == uninteractable, 1 == player must be in same tile, 2 == player must be in a surrounding tile, etc.
	int mInteractionRange;
	//whether the player can walk over this object
	bool mHasCollision;
	//whether the interactable should be drawn and interactable
	bool mExists;

	sf::Vector2f position;

	sf::Sprite sprite;
};

#endif // !INTERACTABLE_H
