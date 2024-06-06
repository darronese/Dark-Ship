#ifndef GENERATOR_H
#define GENERATOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "survivor.hpp"
#include "interactable.hpp"

class Generator : public Interactable {
public:
    Generator(sf::Vector2f position = sf::Vector2f(), double baseWorkSpeed = 0.5);
    void interactWithGenerator(Survivor& survivor, RenderWindow& window, int& completedGens);
    void updateProgressBar();
    /*EscapeShip escape;*/

    bool isSurvivorInRange(Survivor& survivor) const;

    //returns generator progress - Not sure what for yet
    double getProgress() const;

    //Initialize generator locations
    static void SpawnGenerators(std::vector<Generator>& generators, const std::vector<sf::Vector2f>& spawnPositions);

    //messages
    void showMessageBar(RenderWindow& window, const Vector2f& playerPosition) const;

    void setabri(float rate);

    void updateabri();

    float getAbri();

    bool EscapeCheck(int genCompleted);
    int Escape(Survivor& survivor);

    void setAbriDecreaseRate(float rate) { abriDecreaseRate = rate; }

    //Decrease rate(?)
    float getAbri() const { return abri; }
    void setAbri(float value) { abri = value; }


private:
    double mProgress;
    double mBaseWorkSpeed = 0.5;
    bool isRepairing;
    float abriDecreaseRate;
    float abri;
    bool isComplete = 0;
    sf::RectangleShape progressBar;
    sf::RectangleShape interactBox;
    bool isInteractable;
};

#endif // GENERATOR_H
