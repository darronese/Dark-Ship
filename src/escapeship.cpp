#include "escapeship.hpp"

bool EscapeShip::checkIfOpenable(int requiredGenerators) const
{
  //start count at 0
  int count = 0;
  //get progress
  for (const auto& gen : *pGenerators) 
  {
    if (gen.getProgress() >= 100.f) ++count;
  }
  return count >= requiredGenerators;
}

bool EscapeShip::isOpen(void) const
{
  return mProgress >= 100;
}

//function checks if the generators are done to open the escape ship
void EscapeShip::interact(Survivor survivor)
{
  const int requiredGenerators = 5;
  if (!checkIfOpenable(requiredGenerators)) return;

  if (isOpen()) 
  {
    this->successValue = 0;
  }
  else 
  {
    mProgress += mBaseOpenSpeed /* * survivor.mPlayerWorkSpeedModifier */;
  }

}

//getter
int EscapeShip::getSuccessValue() const
{
  return this->successValue;
}
//Setter
void EscapeShip::setSuccessValue(const int newValue)
{
  this->successValue = newValue;
}
