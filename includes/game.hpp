#pragma once
#include "map.hpp"
#include "game.hpp"
#include "decoration.hpp"
#include "survivor.hpp"
#include "monster.hpp"
#include "barrier.hpp"
#include "menu.hpp"
#include "generator.hpp"

using namespace sf;

class Game
{
public:
    void gameWrapper(sf::RenderWindow& app) const;
    int tilemap() const;
private:
    sf::Clock messageTimer;
    bool showMessage;
};
