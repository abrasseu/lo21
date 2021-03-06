/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_1D_H_DEFINE__
#define __SIMULATOR_1D_H_DEFINE__

#include <iostream>
#include <cmath>
#include "State.h"
#include "Simulator.h"

using uint = unsigned int;

class Simulator1D : public Simulator {
private:
	State** getNeighboursState(State** states, uint position);

public:
	// Constructeurs
	Simulator1D(State** states, uint stateNbr, uint cellsSize): Simulator(states, stateNbr, cellsSize, 1) {
		generateCells();
	}
	~Simulator1D() {}

	// Getters
	void printCells();
};

#endif
