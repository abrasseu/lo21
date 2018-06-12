/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "Simulator.h"
#include "State.h"

#define uint unsigned int

void Simulator::generateCells() {
	_cells = new State*[getCellsNbr()];

	generateFirstStateCells();
}

void Simulator::generateFirstStateCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[0], i);
}

void Simulator::generateRandomCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[std::rand() % _stateNbr], i);
}

void Simulator::generateHorizontalSymetricRandomCells() {
	setCell(_states[std::rand() % _stateNbr], 0);

	for (uint i = 1; i < getCellsNbr(); i++)
		setCell(getCell(0), i);
}

void Simulator::generateVerticalSymetricRandomCells() {
	for (uint i = 0; i < ceil(getCellsNbr() / 2); i++) {
		setCell(_states[std::rand() % _stateNbr], i);
		setCell(getCell(i), getCellsNbr() - 1 - i);
	}
}

void Simulator::generateAlternedCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[i % _stateNbr], i);
}

void Simulator::generateDescAlternedCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[_stateNbr - (i % _stateNbr) - 1], i);
}

bool Simulator::setCell(State* state, uint position) {
	if (position >= getCellsNbr())
	 	return false;

	State* lastState(getCell(position));
	_cells[position] = state;

	return state != lastState;
}

State* Simulator::getCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _cells[position];
}

State** Simulator::getCellsState() const {
	State** states(new State*[getCellsNbr()]);

	for (uint i = 0; i < getCellsNbr(); i++)
		states[i] = _cells[i];

	return states;
}

void Simulator::printCells() {
	for (uint i = 0; i < getCellsSize(); i++)
		std::cout << _cells[i]->getName();

	std::cout << std::endl;
}

void Simulator::incrementState(uint position, bool allowNullState) {
	State* cellToUpdate(getCell(position));
	State* toState;
	uint toStateId = 0;

	for (uint i = 0; i < _stateNbr; i++) {
		if (_states[i] == cellToUpdate) {
			toStateId = (i + 1) % _stateNbr;

			break;
		}
	}

	if (toStateId == 0 && allowNullState)
		toState = nullptr;
	else
		toState = _states[toStateId];

	setCell(toState, position);
}

bool Simulator::mutate() {
	State** statesOfThisGeneration = getCellsState();
	bool isNextGeneration = false;

	for (uint i = 0; i < getCellsNbr(); i++) {
		State** neighboursState(getNeighboursState(statesOfThisGeneration, i));

		if (setCell(_cells[i]->getNextGeneration(neighboursState, getNeighbourNbr()), i))
			isNextGeneration = true;

		delete[] neighboursState;
	}

	_generation += isNextGeneration;

	delete[] statesOfThisGeneration;
	return isNextGeneration;
}
