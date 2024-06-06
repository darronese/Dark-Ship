#pragma once
#ifndef ESCAPE_SHIP_H
#define ESCAPE_SHIP_H

#include "interactable.hpp"
#include "generator.hpp"

class EscapeShip : public Interactable {
public:
	EscapeShip() {};

	EscapeShip(Vector2f position, std::vector<Generator>* generators) :
		Interactable("placeholderImagePath"),
		mProgress(0),
		mBaseOpenSpeed(.5),
		pGenerators(generators) {}

	//scans map for # of requiredGenerators completed, returns true if enough are found
	bool checkIfOpenable(int requiredGenerators = 5) const;

	bool isOpen(void) const;

	void interact(Survivor survivor);

	//getter
	int getSuccessValue() const;
	//Setter
	void setSuccessValue(const int newValue);

private:
	double mProgress;
	double mBaseOpenSpeed;
	std::vector<Generator>* pGenerators;
	//0 is victory, 1 is defeat
	int successValue = 2;
};

#endif // !ESCAPE_SHIP_H
