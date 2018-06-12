/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include "Simulator.h"
#include "Cell.h"
#include "State.h"

using uint = unsigned int;

void Simulator::createCells() {
	std::cout << getCellsNbr() << std::endl;
	_cells = new Cell*[getCellsNbr()];


	for (uint i = 0; i < getCellsNbr(); i++)
		_cells[i] = new Cell(_states[std::rand() % _stateNbr]);
}
/*
State** Simulator1D::getNeighboursState(State** states, uint position) {
	State** neighbours(new State*[getNeightborNbr()]);

	// On ajoute le précédent et le suivant:
	neighbours[0] = states[(position - 1) % getCellsNbr()];
	neighbours[1] = states[(position + 1) % getCellsNbr()];

	return neighbours;
}
*/
Cell* Simulator::getCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _cells[position];
}

State** Simulator::getCellsState() const {
	State** states(new State*[getCellsNbr()]);

	for (uint i = 0; i < getCellsNbr(); i++)
		states[i] = _cells[i]->getState();

	return states;
}

void Simulator::printCells() {
	for (uint i = 0; i < getCellsSize(); i++)
		std::cout << _cells[i]->getState()->getName();

	std::cout << std::endl;
}

void Simulator::incrementState(uint position) {
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

bool Simulator::mutate() {
	State** statesOfThisGeneration = getCellsState();
	bool isNextGeneration = false;

	for (uint i = 0; i < getCellsNbr(); i++) {
		State** neighboursState(getNeighboursState(statesOfThisGeneration, i));

		if (_cells[i]->mutate(neighboursState, getNeighbourNbr()))
			isNextGeneration = true;

		delete[] neighboursState;
	}

	_generation += isNextGeneration;

	delete[] statesOfThisGeneration;
	return isNextGeneration;
}
