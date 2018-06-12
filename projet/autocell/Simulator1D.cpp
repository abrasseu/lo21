/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include "Simulator.h"
#include "Simulator1D.h"
#include "Cell.h"
#include "State.h"

using uint = unsigned int;

State** Simulator1D::getNeighboursState(State** states, uint position) {
	State** neighbors(new State*[getNeighbourNbr()]);

	// On ajoute le précédent et le suivant:
	neighbors[0] = states[(position - 1) % getCellsNbr()];
	neighbors[1] = states[(position + 1) % getCellsNbr()];

	return neighbors;
}

void Simulator1D::printCells() {
	for (uint i = 0; i < getCellsSize(); i++)
		std::cout << _cells[i]->getState()->getName();

	std::cout << std::endl;
}

void Simulator1D::incrementState(uint position) {
	Cell* cellToUpdate(getCell(position));
	State* currentState(cellToUpdate->getState());
	uint toState = 0;

	for (uint i = 0; i < _stateNbr; i++) {
		if (_states[i] == currentState) {
			toState = (i + 1) % _stateNbr;

			break;
		}
	}

	cellToUpdate->setState(_states[toState]);
}
