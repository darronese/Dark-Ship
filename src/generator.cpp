#include "generator.hpp"
#include "survivor.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

using sf::Vector2f;

Generator::Generator(sf::Vector2f position, double baseWorkSpeed) : Interactable("../data/images/Character_Sheet.png"),
  abri(10.0f), abriDecreaseRate(.1f), mProgress(0.0), isComplete(false) 
{
  //---------------------------------------Sets sprite Location------------------------------------------------
  sprite.setPosition(position);
  mBaseWorkSpeed = baseWorkSpeed;

  //----------------------------------------Sets interaction Box Values-----------------------------------------
  interactBox.setScale(5, 5);
  interactBox.setSize(Vector2f(50, 50));
  interactBox.setFillColor(sf::Color(0, 0, 0, 0));
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

// Check if this is the door generator and if all other generators are not completed
void Generator::interactWithGenerator(Survivor& survivor, sf::RenderWindow& window, int& completedGens) 
{
  bool isDoorGenerator = (sprite.getPosition() == Vector2f(51 * 80, 8 * 80));
  bool inRange = isSurvivorInRange(survivor);

  if (isDoorGenerator && completedGens < 4 && inRange) 
  {
    // Display a message only when the survivor is near the door generator
    sf::Font font;
    font.loadFromFile("../data/images/pixel2.ttf");
    sf::Text text("Fix other generators first!", font, 50);
    text.setPosition(survivor.getPosition().x - text.getLocalBounds().width / 2, survivor.getPosition().y - 150.0f);
    window.draw(text);
    return; // Prevent further processing for this generator
  }

  // Draw the interaction box and progress bar
  window.draw(interactBox);
  window.draw(progressBar);

  // Continue with the interaction logic if this is not the door generator or all other generators are completed
  static bool isPressingE = false;
  if (inRange) 
  {
    bool currentEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    if (currentEPressed && !isComplete) 
    {
      isPressingE = true;
      if (abri > 0.f) 
      {
        abri -= abriDecreaseRate;
        if (abri < 0.f) abri = 0.f;
        updateProgressBar();
      } 
      else 
      {
        mProgress = 0.0;
        isComplete = true;
        completedGens++;
      }
    } 
    else 
    {
      isPressingE = false;
    }
  }

  if (isPressingE && !isComplete) 
  {
    mProgress += 0.1f;
    if (mProgress >= 12.5) 
    {
      mProgress = 10.0;
      isComplete = true;
    }
  }

  if (isComplete && inRange) 
  {
    showMessageBar(window, survivor.getPosition());
  }
}



//updates the progress bar when fixing generator (black bar)
void Generator::updateProgressBar() 
{
  float progress = (10.0f - abri) * 10.0f; 
  progressBar.setSize(Vector2f(progress, 10));
}


//checks to see if survivor is in range of the generator
bool Generator::isSurvivorInRange(Survivor& survivor) const 
{
  if (interactBox.getGlobalBounds().intersects(survivor.getPlayerSprite().getGlobalBounds())) 
  {
    return true;
  }
  else 
  {
    return false;
  }
}

double Generator::getProgress() const 
{
  return mProgress;
}

//spawn generators over each position from spawn positions and set the work speed for each generator to be worked on
void Generator::SpawnGenerators(std::vector<Generator>& generators, const std::vector<sf::Vector2f>& spawnPositions) 
{
  for (const auto& position : spawnPositions) 
  {
    double baseWorkSpeed = 0.05;
    Generator newGenerator(position, baseWorkSpeed);
    generators.push_back(newGenerator);
  }
}

//shows message after generator is done being repaired
void Generator::showMessageBar(sf::RenderWindow& window, const Vector2f& playerPosition) const 
{
  if (!isComplete) return; // Exit if the generator is not complete
  sf::Font font;
  font.loadFromFile("../data/images/pixel2.ttf");
  sf::Text text("Generator repaired!", font, 100);
  text.setPosition(playerPosition.x - text.getLocalBounds().width / 2, playerPosition.y - 180.0f); 
  window.draw(text);
}

//secondary depletion meter: when depleted generator is complete
void Generator::setabri(float rate)
{
  if (rate < 0) 
  {
    rate = 0;
  }
  else if (rate > 10) 
  {
    rate = 10;
  }
}

float Generator::getAbri()
{
  return abri;
}

//checks to make sure if escape ship is ready to be activated
bool Generator::EscapeCheck(int genCompleted) 
{
  if (genCompleted == 5) 
  {
    return true;
  }
  return false;
}

//escape logic
int Generator::Escape(Survivor& survivor) 
{
  if (position != Vector2f(51 * 80, 8 * 80)) 
  {
    if (isSurvivorInRange(survivor) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) 
    {
      return 0;
    }
  }
  return 1;
}
