#pragma once
#pragma once
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics.hpp>
#include "barrier.hpp"
#include "survivor.hpp"
#include "monster.hpp"

class Interactable {
  public:
    Interactable() { ; }
    Interactable(const std::string& imagePath);

    void remove();

    void draw(sf::RenderWindow& window, sf::Vector2f position) const;

  protected:
    //coordinate position on the map
    sf::Vector2f mPosition;
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
