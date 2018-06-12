/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 2D
 */

#include <iostream>
#include <vector>
#include "Simulator.h"
#include "Simulator2D.h"
#include "State.h"
#include "Rule.h"

#define uint unsigned int

State* Simulator2D::getCell(uint x, uint y) const {
	return getCell((x * getCellsSize()) + y);
}

bool Simulator2D::setCell(State* state, uint x, uint y) {
	return setCell(state, (x * getCellsSize()) + y);
}

void Simulator2D::generateHorizontalSymetricRandomCells() {
	for (uint i = 0; i < ceil(getCellsSize() / 2); i++) {
		for (uint j = 0; j < getCellsSize(); j++) {
			setCell(_states[std::rand() % _stateNbr], i, j);
			setCell(getCell(i, j), getCellsSize() - 1 - i, j);
		}
	}
}

void Simulator2D::generateVerticalSymetricRandomCells() {
	for (uint i = 0; i < getCellsSize(); i++) {
		for (uint j = 0; j < ceil(getCellsSize() / 2); j++) {
			setCell(_states[std::rand() % _stateNbr], i, j);
			setCell(getCell(i, j), i, getCellsSize() - 1 - j);
		}
	}
}

State** Simulator2D::getNeighboursState(State** states, uint position) {
	State** neighbors(new State*[getNeighbourNbr()]);
	int x = position % getCellsSize();
	int y = (position - x) / getCellsSize();

	// On ajoute les précédents et les suivants:
	uint line = (y == 0 ? getCellsSize() - 1 : ((y - 1) % getCellsSize())) * getCellsSize();
	neighbors[0] = states[(line + (x == 0 ? getCellsSize() - 1 : ((x - 1) % getCellsSize()))) % getCellsNbr()];
	neighbors[1] = states[(line + x) % getCellsNbr()];
	neighbors[2] = states[(line + ((x + 1) % getCellsSize())) % getCellsNbr()];

	neighbors[3] = states[((y * getCellsSize()) + (x == 0 ? getCellsSize() - 1 : ((x - 1) % getCellsSize()))) % getCellsNbr()];
	neighbors[4] = states[((y * getCellsSize()) + ((x + 1) % getCellsSize())) % getCellsNbr()];

	line = (y + 1) % getCellsSize() * getCellsSize();
	neighbors[5] = states[(line + (x == 0 ? getCellsSize() - 1 : ((x - 1) % getCellsSize()))) % getCellsNbr()];
	neighbors[6] = states[(line + x) % getCellsNbr()];
	neighbors[7] = states[(line + ((x + 1) % getCellsSize())) % getCellsNbr()];

	return neighbors;
}

void Simulator2D::printCells() {
	for (uint i = 0; i < getCellsSize(); i++) {
		for (uint j = 0; j < getCellsSize(); j++)
			std::cout << getCell(i, j)->getName()[0];

		std::cout << std::endl;
	}
}

void Simulator2D::incrementState(uint x, uint y, bool allowNullState) {
	incrementState((x * getCellsSize()) + y, allowNullState);
}
