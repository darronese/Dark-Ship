#include "generator.hpp"
#include "survivor.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std::chrono;

Generator::Generator(sf::Vector2f position, double baseWorkSpeed) : Interactable("../data/images/Character_Sheet.png"),
abri(10.0f), abriDecreaseRate(.1f), mProgress(0.0), isComplete(false) {
    //---------------------------------------Sets sprite Location------------------------------------------------
    sprite.setPosition(position);
    mBaseWorkSpeed = baseWorkSpeed;

    //----------------------------------------Sets interaction Box Values-----------------------------------------
    interactBox.setScale(5, 5);
    interactBox.setSize(Vector2f(50, 50));
    interactBox.setFillColor(Color(0, 0, 0, 0));
    interactBox.setOrigin(interactBox.getLocalBounds().width / 2, interactBox.getLocalBounds().height / 2);
    interactBox.setPosition(sprite.getPosition());

    //Debugging color for box
    //interactBox.setFillColor(Color::Red);

    //----------------------------------------Sets Progress Bar Values------------------------------------------
    progressBar.setSize(Vector2f(abriDecreaseRate / abri,10));
    progressBar.setFillColor(sf::Color::Black);
    progressBar.setPosition(position.x, position.y - 5.0f);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Generator::interactWithGenerator(Survivor& survivor, RenderWindow& window, int& completedGens) {
    if (completedGens == 5 || position != Vector2f(51 * 80, 8 * 80)) {
    }
    window.draw(interactBox);
    window.draw(progressBar);
    bool inRange = isSurvivorInRange(survivor);
    static bool isPressingE = false; // Track whether 'E' key is being pressed
    if (inRange) {
        bool currentEPressed = Keyboard::isKeyPressed(Keyboard::E); // Check if 'E' key is currently pressed
        if (currentEPressed && !isComplete) {
            isPressingE = true; // Set flag indicating 'E' is being pressed
            if (abri > 0.f) {
                abri -= abriDecreaseRate; // Decrease abri
                if (abri < 0.f) abri = 0.f; // Ensure abri doesn't go below 0
                updateProgressBar();
                /*sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("Music/wrench.wav"))
                {
                    std::cout << "There was an error with the sounds" << std::endl;
                }
                sf::Sound wrench;
                wrench.setBuffer(buffer);
                while (!isComplete)
                {
                    wrench.play();
                }*/
                std::cout << mProgress << std::endl; // Test Case
            }
            else {
                mProgress = 0.0; // Set progress to 0 when generator is complete
                isComplete = true;
                completedGens++;
            }
        }
        else {
            isPressingE = false; // Reset flag when 'E' key is released
        }
    }

    // If 'E' key is held down but generator is not complete, increase time
    if (isPressingE && !isComplete) {
        mProgress += 0.1f; // Increase progress by 0.1 per frame
        if (mProgress >= 12.5) {
            mProgress = 10.0;
            isComplete = true;
        }
    }
    // Display message when generator is complete and survivor is in range
    if (isComplete && inRange) {
        showMessageBar(window, survivor.getPosition());
    }

}



void Generator::updateProgressBar() {
    float progress = (10.0f - abri) * 10.0f; 
    progressBar.setSize(Vector2f(progress, 10));
}


bool Generator::isSurvivorInRange(Survivor& survivor) const {
    if (interactBox.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}

double Generator::getProgress() const {
    return mProgress;
}

void Generator::SpawnGenerators(std::vector<Generator>& generators, const std::vector<sf::Vector2f>& spawnPositions) {
    for (const auto& position : spawnPositions) {
        double baseWorkSpeed = 0.05;
        Generator newGenerator(position, baseWorkSpeed);
        generators.push_back(newGenerator);
    }
}

void Generator::showMessageBar(RenderWindow& window, const Vector2f& playerPosition) const {
    if (!isComplete) return; // Exit if the generator is not complete
    Font font;
    font.loadFromFile("../data/images/pixel2.ttf");
    Text text("Generator repaired!", font, 100);
    text.setPosition(playerPosition.x - text.getLocalBounds().width / 2, playerPosition.y - 180.0f); 
    window.draw(text);
}


void Generator::setabri(float rate)
{
    if (rate < 0) {
        rate = 0;
    }
    else if (rate > 10) {
        rate = 10;
    }
    else {
    }
}

void Generator::updateabri()
{
    abri = abri;
}

float Generator::getAbri()
{
    return abri;
}

bool Generator::EscapeCheck(int genCompleted) {
    if (genCompleted == 5) {
        return true;
    }
    return false;
}

int Generator::Escape(Survivor& survivor) {
    if (position != Vector2f(51 * 80, 8 * 80)) {
        if (isSurvivorInRange(survivor) && Keyboard::isKeyPressed(Keyboard::E)) {
            return 0;
        }
    }
    return 1;
}
