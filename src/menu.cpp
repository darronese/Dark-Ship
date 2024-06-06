#include "menu.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

//Constructor to load the font
Menu::Menu(float width, float height) : width(width), height(height), selection(0)
{
    //Error statement when loading fonts
    if (!font.loadFromFile("../data/images/pixel2.ttf"))
    {
        std::cout << "No font selected" << std::endl;
        return;
    }

    //Lauches music
    if (!mainMenuMusic.openFromFile("../data/music/Stardust.wav"))
    {
        std::cout << "Error loading the main menu music." << std::endl;
    }
    if (!gameplayMusic.openFromFile("../data/music/playBackground.wav"))
    {
        std::cout << "Error loading the gamplay music." << std::endl;
    }

    //Intializes menu header(title of game)
    std::string menuTitle = "Cool Game Made By Future FAANG Employees";
    titleCustomize.setFont(font);
    titleCustomize.setFillColor(sf::Color::White);
    titleCustomize.setPosition(135, 120);
    titleCustomize.setCharacterSize(78);
    titleCustomize.setString(menuTitle);
    //Initializes all menu items
    std::string menuItems[] = { "Play", "Rules", "Exit" };
    //set constructor to these values for when we draw
    for (int i = 0; i < 3; ++i)
    {
        mainMenu[i].setFont(font);
        //Font color is white initially, when selecting it will change it to be blue
        mainMenu[i].setFillColor(sf::Color::White);
        mainMenu[i].setString(menuItems[i]);
        mainMenu[i].setCharacterSize(70);
        mainMenu[i].setPosition(700, 270 + 100 * i);
    }
    mainMenu[selection].setFillColor(sf::Color::Blue); //Highlights first item
}

void Menu::printVictoryScreen()
{
    stopGameMusic();
    sf::RenderWindow afterWindow(sf::VideoMode(1920, 1080), "Victory Screen");
    afterWindow.setFramerateLimit(60);

    // Load the background
    sf::Texture afterTexture;
    if (!afterTexture.loadFromFile("../data/images/play.png")) {
        std::cerr << "Error loading image." << std::endl;
        return;
    }

    sf::RectangleShape afterBackground(sf::Vector2f(afterWindow.getSize().x, afterWindow.getSize().y));
    afterBackground.setTexture(&afterTexture);

    // Prepare text
    sf::Text victoryCustomize;
    victoryCustomize.setFont(font);
    victoryCustomize.setFillColor(sf::Color::Green);
    victoryCustomize.setString("Congratulations!");
    victoryCustomize.setCharacterSize(75);
    sf::FloatRect headerBounds = victoryCustomize.getLocalBounds();
    victoryCustomize.setOrigin(headerBounds.width / 2.0f, headerBounds.height / 2.0f);
    victoryCustomize.setPosition(afterWindow.getSize().x / 2.0f, 150);

    std::string victoryMessages[] = {
        "You Win!",
        "Your survival skills are unmatched!",
        "Unfortunately for you, the monsters could fly! Who would've known?",
        "They hunted you down mercilessly",
        "The end!",
    };

    sf::Text messageCustomize;
    messageCustomize.setFont(font);
    messageCustomize.setFillColor(sf::Color::White);
    messageCustomize.setCharacterSize(50);

    // Event loop
    while (afterWindow.isOpen()) {
        sf::Event event;
        while (afterWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stopGameMusic();
                afterWindow.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                stopGameMusic();
                Menu menu;
                afterWindow.close();
                menu.menuWrapper();
            }
        }

        afterWindow.clear();
        afterWindow.draw(afterBackground);
        afterWindow.draw(victoryCustomize);

        for (int i = 0; i < 5; ++i) {
            messageCustomize.setString(victoryMessages[i]);
            sf::FloatRect textBounds = messageCustomize.getLocalBounds();
            messageCustomize.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
            messageCustomize.setPosition(afterWindow.getSize().x / 2.0f, 300 + 70 * i);
            afterWindow.draw(messageCustomize);
        }

        afterWindow.display();
    }
}

//Prints requires testing!!!
void Menu::printDefeatScreen()
{
    stopGameMusic();
    sf::RenderWindow afterWindow(sf::VideoMode(1920, 1080), "Defeat Screen");
    afterWindow.setFramerateLimit(60);

    // Load the background
    sf::Texture afterTexture;
    if (!afterTexture.loadFromFile("images/play.png")) {
        std::cerr << "Error loading image." << std::endl;
        return;
    }

    sf::RectangleShape afterBackground(sf::Vector2f(afterWindow.getSize().x, afterWindow.getSize().y));
    afterBackground.setTexture(&afterTexture);

    // Prepare text
    sf::Text defeatCustomize;
    defeatCustomize.setFont(font);
    defeatCustomize.setFillColor(sf::Color::Red); // Red to signify defeat
    defeatCustomize.setString("Defeat!");
    defeatCustomize.setCharacterSize(75);
    sf::FloatRect headerBounds = defeatCustomize.getLocalBounds();
    defeatCustomize.setOrigin(headerBounds.width / 2.0f, headerBounds.height / 2.0f);
    defeatCustomize.setPosition(afterWindow.getSize().x / 2.0f, 150);

    std::string defeatMessages[] = {
        "You lose!",
        "Your survival skills are terrible!",
        "Who taught you how to run?",
        "The end(forever)!",
    };

    sf::Text messageCustomize;
    messageCustomize.setFont(font);
    messageCustomize.setFillColor(sf::Color::White);
    messageCustomize.setCharacterSize(50);

    // Event loop
    while (afterWindow.isOpen()) {
        sf::Event event;
        while (afterWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stopGameMusic();
                afterWindow.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                stopGameMusic();
                Menu menu;
                afterWindow.close();
                menu.menuWrapper();
            }
        }

        afterWindow.clear();
        afterWindow.draw(afterBackground);
        afterWindow.draw(defeatCustomize);

        for (int i = 0; i < sizeof(defeatMessages) / sizeof(std::string); ++i) {
            messageCustomize.setString(defeatMessages[i]);
            sf::FloatRect textBounds = messageCustomize.getLocalBounds();
            messageCustomize.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
            messageCustomize.setPosition(afterWindow.getSize().x / 2.0f, 300 + 70 * i);
            afterWindow.draw(messageCustomize);
        }

        afterWindow.display();
    }
}
//Destructor
Menu::~Menu()
{
    ;
}

//Getters
int Menu::getSelection() const
{
    return this->selection;
}
//Setters
void Menu::setNewSelection(const int& newSelection)
{
    this->selection = newSelection;
}

//Draws main menu
void Menu::draw(sf::RenderWindow& window)
{
    //Draw the menu title first
    window.draw(titleCustomize);
    //Print out the menu options in the array
    for (int i = 0; i < 3; ++i)
    {
        window.draw(mainMenu[i]);
    }
}

//Functions to move up and down with arrow keys
void Menu::moveUp()
{
    //Deselects first
    mainMenu[selection].setFillColor(sf::Color::White);
    //Move up (THIS BOUNDS THE RANGE FROM 0-3 because there are 3 items, which is why we have mod 3
    /*got hover idea from this video: https://www.youtube.com/watch?v=bOG8667yePY&t=613s */
    selection = (selection - 1 + 3) % 3;
    //Highlight new item
    mainMenu[selection].setFillColor(sf::Color::Blue);
}
//Same idea as move up
void Menu::moveDown()
{
    //Deselects first
    mainMenu[selection].setFillColor(sf::Color::White);
    //Move up
    selection = (selection + 1) % 3;
    //Highlight new item
    mainMenu[selection].setFillColor(sf::Color::Blue);
}

//Function to print out game rules
void Menu::gameRules(sf::RenderWindow& window) const
{
    //rules header
    std::string rulesHeader = "Rules";
    //Set a variable to customize the rules header
    sf::Text ruleCustomize;
    sf::RenderWindow rulesWindow;
    //Customization for the rules header
    ruleCustomize.setFont(font);
    ruleCustomize.setFillColor(sf::Color::White);
    ruleCustomize.setString(rulesHeader);
    ruleCustomize.setCharacterSize(75);
    ruleCustomize.setPosition(700, 170);
    //Draw it
    window.draw(ruleCustomize);

    //An array of strings to contain the rules of the game
    std::string ruleBody[] = { "Your objective is to survive!", "There are 5 generators", "Turn on 5 of them in order to escape the monster!", "WASD to move, Shift to Sprint, E to interact", "ESC to go back"};
    //Displays everything within the loop
    for (int i = 0; i < 5; ++i)
    {
        //Set a customizable body
        sf::Text bodyCustomize;
        bodyCustomize.setFont(font);
        bodyCustomize.setFillColor(sf::Color::White);
        bodyCustomize.setString(ruleBody[i]);
        bodyCustomize.setCharacterSize(50);
        //Eveery time it prints a string, lower the "y" value so that it can be formatted in order
        bodyCustomize.setPosition(410, 380 + 60 * i);
        //draws the rule body
        window.draw(bodyCustomize);
    }

}

//Music playing
void Menu::playMainMenuMusic()
{
    mainMenuMusic.setLoop(true);
    mainMenuMusic.setVolume(20.f);
    mainMenuMusic.play();
}
void Menu::stopMainMenuMusic()
{
    gameplayMusic.setLoop(false);
    mainMenuMusic.stop();
}
void Menu::playGameMusic()
{
    if (!gameplayMusic.openFromFile("../data/music/playBackground.wav"))
    {
        std::cout << "Error loading the gameplay music." << std::endl;
        return;
    }
    gameplayMusic.setLoop(true);
    gameplayMusic.setVolume(20.f);
    gameplayMusic.play();
}
void Menu::stopGameMusic()
{
    gameplayMusic.setLoop(false);
    gameplayMusic.stop();
}

//Menu wrapper to conserve space for main.cpp
//Removed closing the main menu window when inputting play or rules, so that user can hit "esc" and return to main menu
void Menu::menuWrapper()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Main Menu", sf::Style::Default);
    Menu mainMenu(window.getSize().x, window.getSize().y);

    sf::RectangleShape mainBackground;
    mainBackground.setSize(sf::Vector2f(1920, 1080));
    sf::Texture mainTexture;
    if (!mainTexture.loadFromFile("../data/images/main.jpeg"))
    {
        std::cout << "Error loading image." << std::endl;
    }
    mainBackground.setTexture(&mainTexture);

    mainMenu.playMainMenuMusic();
    mainMenu.stopGameMusic();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    mainMenu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    mainMenu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    int choice = mainMenu.getSelection();

                    if (choice == 0) // Play
                    {
                        mainMenu.stopMainMenuMusic();
                        sf::RenderWindow afterWindow(sf::VideoMode(1920, 1080), "Play");
                        sf::RectangleShape afterBackground;
                        afterBackground.setSize(sf::Vector2f(1920, 1080));
                        sf::Texture afterTexture;
                        if (!afterTexture.loadFromFile("../data/images/play.png"))
                        {
                            std::cout << "Error loading image." << std::endl;
                        }
                        afterBackground.setTexture(&afterTexture);

                        Game mainGame;

                        mainGame.gameWrapper(afterWindow);

                        afterWindow.close();
                        mainMenu.playMainMenuMusic();
                    }
                    else if (choice == 1) // Rules
                    {
                        sf::RenderWindow rulesWindow(sf::VideoMode(1920, 1080), "Rules");
                        sf::RectangleShape rulesBackground;
                        rulesBackground.setSize(sf::Vector2f(1920, 1080));
                        sf::Texture rulesTexture;
                        if (!rulesTexture.loadFromFile("../data/images/rules.png"))
                        {
                            std::cout << "Error loading image." << std::endl;
                        }
                        rulesBackground.setTexture(&rulesTexture);

                        while (rulesWindow.isOpen())
                        {
                            sf::Event event;
                            while (rulesWindow.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    rulesWindow.close();
                                }
                                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                                {
                                    rulesWindow.close();
                                }
                            }
                            rulesWindow.clear();
                            rulesWindow.draw(rulesBackground);
                            mainMenu.gameRules(rulesWindow);
                            rulesWindow.display();
                        }
                    }
                    else if (choice == 2) // Exit
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(mainBackground);
        mainMenu.draw(window);
        window.display();
    }

    mainMenu.stopMainMenuMusic();
}
