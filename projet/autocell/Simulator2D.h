/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_2D_H_DEFINE__
#define __SIMULATOR_2D_H_DEFINE__

#include <iostream>
#include "Simulator.h"
#include "Cell.h"
#include "State.h"

#define uint unsigned int

class Simulator2D : public Simulator {
protected:
	using Simulator::createCells;
	State** getNeighboursState(State** states, uint position);

public:
	// Constructeurs
	Simulator2D(State** states, uint stateNbr, uint cellsSize): Simulator(states, stateNbr, cellsSize, 2) {
		createCells();
	}

	// Getters
	using Simulator::getCell;
	Cell* getCell(uint x, uint y) const;

	using Simulator::incrementState;
	void incrementState(uint x, uint y);

	void printCells();
};

#endif
