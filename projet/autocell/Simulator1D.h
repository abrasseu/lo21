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

#define uint unsigned int

class Simulator1D : public Simulator {
private:
	State** getNeighboursState(State** states, uint position);

public:
	// Constructeurs
	Simulator1D(State** states, uint stateNbr, uint cellsSize): Simulator(states, stateNbr, cellsSize, 1) {
		generateCells();
	}

	// Getters
	void printCells();
};

#endif
