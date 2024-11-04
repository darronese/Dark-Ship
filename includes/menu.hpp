#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "game.hpp"

//Class menu
class Menu
{
  public:
    //Initialize constructor with the width and height at 0
    Menu(float width = 0.0, float height = 0.0);
    //Destructor
    ~Menu();
    //Draws the menu through sfml render window
    void draw(sf::RenderWindow& window);
    //Functions to move up and downn with arrow keys
    void moveUp();
    void moveDown();
    //Getters
    int getSelection() const;
    //Setters
    void setNewSelection(const int& newSelection);
    //Function to print out game rules
    void gameRules(sf::RenderWindow& window) const;
    //Wrapper
    void menuWrapper();
    //Music playing
    void playMainMenuMusic();
    void stopMainMenuMusic();
    void playGameMusic();
    void stopGameMusic();
    void printVictoryScreen();
    void printDefeatScreen();
    //Helper Functions
    void initializeMenu(const sf::RenderWindow& window);
    void handleKeyReleased(const sf::Event& event, sf::RenderWindow& window);
    void handleChoice(int choice, sf::RenderWindow& window);
    void handlePlay(sf::RenderWindow& window);
    void handleRules(sf::RenderWindow& window);
  private:
    //Private members
    float width;
    float height;
    //Selection
    int selection;
    //Font we will be using
    sf::Font font;
    //Main menu selection, has 4 options
    sf::Text mainMenu[3];
    //Text for name of game
    sf::Text titleCustomize;
    //Music
    sf::Music mainMenuMusic;
    sf::Music gameplayMusic;
};
