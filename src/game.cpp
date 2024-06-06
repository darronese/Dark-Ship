#include "game.hpp"
#include "survivor.hpp"
#include "monster.hpp"
#include "menu.hpp"
#include "generator.hpp"
#include "decoration.hpp"
#include "wall.hpp"
#include "escapeship.hpp"
#include <iostream>

//main game loop
//we call this functino inside ofg menu. and call menu inside of main
void Game::gameWrapper(sf::RenderWindow& app) const
{
    //set framerate to avoid some bugs
    app.setFramerateLimit(60);
    //create an event
    sf::Event event;
    Walls walls;
    int CompletedGens = 0;

    // Setting health and Stamina
    float currentHealth = 100.0f;
    float maxHealth = 100.0f;
    float maxStamina = 100.0f;
    float currentStamina = 100.0f;
    Header header(maxHealth, currentHealth, maxStamina, currentStamina);

    //initialize the monsters
    Monster monster1(app);
    monster1.setPosition(300 * 16, 120 * 16);
    Monster monster2(app);
    monster2.setPosition(400 * 16, 80 * 16);
    Monster monster3(app);
    monster3.setPosition(100 * 16, 120 * 16);

    //initialize the player
    Survivor survivor(app);
    survivor.setPosition(70 * 16, 40 * 16);

    //set the view
    sf::View view(app.getView().getCenter(), sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2));
    view.setCenter(survivor.getPosition());

    // Background texture
    sf::Texture bgTexture;
    float texWidth = bgTexture.getSize().x;
    float texHeight = bgTexture.getSize().y;
    float xOffset = -texWidth / 2.0f;
    float yOffset = -texHeight / 2.0f;
    if (!bgTexture.loadFromFile("../data/images/pixelart_starfield.png"))
    {
        std::cerr << "Error loading background texture." << std::endl;
    }
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(10, 10);

    // Frame independence
    sf::Clock clock;
    float dt;
    float multiplier = 3750.f;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("../data/images/pixel2.ttf"))
    {
        std::cerr << "Error loading font." << std::endl;
    }

    // Define the level with an array of tile indices
    const int level[4500] = { /* your level data */ };

    // Create the tilemap from the level definition
    Map map;
    map.setScale(sf::Vector2f(5, 5));
    if (!map.load("../data/images/SciFi_Tiles.png", sf::Vector2u(16, 16), level, 90, 50))
    {
        std::cerr << "Error loading map." << std::endl;
        return;
    }

    // Generator setup
    std::vector<Generator> generators;
    std::vector<sf::Vector2f> spawnPositions = { sf::Vector2f(280, 100), sf::Vector2f(280, 3900), sf::Vector2f(1500, 900), sf::Vector2f(3200,750), sf::Vector2f(51 * 80, 8 * 80), sf::Vector2f(80 * 80, 23 * 80) };
    Generator::SpawnGenerators(generators, spawnPositions);

    for (auto& generator : generators) {
        generator.setAbriDecreaseRate(0.5f);
    }

    // Decorations setup
    Decorations decorations;
    Menu menu;
    menu.playGameMusic();

    // Main game loop
    while (app.isOpen())
    {
        EscapeShip win;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menu.stopGameMusic();
                app.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            menu.stopGameMusic();
            app.close();
            menu.menuWrapper();
        }

        if (view.getCenter() != survivor.getPosition()) {
            float xMove = view.getCenter().x - survivor.getPosition().x;
            float yMove = view.getCenter().y - survivor.getPosition().y;
            view.move(xMove / -1.f, yMove / -1.f);
        }

        //prompts victory or defeat screen
        if (survivor.getHealth() <= 0)
        {
            menu.stopGameMusic();
            app.close();
            menu.printDefeatScreen();
        }

        if (win.getSuccessValue() == 0)
        {
            menu.stopGameMusic();
            app.close();
            menu.printVictoryScreen();
        }
        if (win.getSuccessValue() == 1)
        {
            menu.stopGameMusic();
            app.close();
            menu.printDefeatScreen();
        }

        if (survivor.getHealth() <= 0)
        {
            win.setSuccessValue(1);
        }

        dt = clock.restart().asSeconds() * multiplier;

        app.setView(view);
        app.clear(sf::Color::Black);
        bgSprite.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y);
        app.draw(bgSprite);

        app.setView(view);
        app.draw(map);

        walls.loadBarriers(app);
        monster1.draw(app);
        monster2.draw(app);
        monster3.draw(app);
        survivor.draw(app);

        survivor.handlePlayerMovement(dt, walls);
        monster1.handlePlayerMovement(dt, walls, survivor, app);
        monster2.handlePlayerMovement(dt, walls, survivor, app);
        monster3.handlePlayerMovement(dt, walls, survivor, app);

        decorations.checkCollision(survivor);

        if (survivor.getPlayerSprite().getGlobalBounds().intersects(monster1.getAttackRadius().getGlobalBounds())) {
            monster1.attackPlayer(survivor);
        }
        if (survivor.getPlayerSprite().getGlobalBounds().intersects(monster2.getAttackRadius().getGlobalBounds())) {
            monster2.attackPlayer(survivor);
        }
        if (survivor.getPlayerSprite().getGlobalBounds().intersects(monster3.getAttackRadius().getGlobalBounds())) {
            monster3.attackPlayer(survivor);
        }

        header.updateHealth(survivor.getHealth());
        header.updateStamina(survivor.getStamina());

        for (const auto& generator : generators) {
            for (auto& position : spawnPositions)
            {
                generator.draw(app, position);
            }
        }

        decorations.loadBarriers(app);
        survivor.directionUpdate(app);
        monster1.directionUpdate(app, survivor);
        monster2.directionUpdate(app, survivor);
        monster3.directionUpdate(app, survivor);

        for (auto& generator : generators) {
            generator.interactWithGenerator(survivor, app, CompletedGens);
            if (generator.EscapeCheck(CompletedGens)) {
                if (generator.Escape(survivor) == 0)
                {
                    menu.stopGameMusic();
                    app.close();
                    menu.printVictoryScreen();
                }
            }
        }

        header.draw(app, view);

        app.display();

    }
}
