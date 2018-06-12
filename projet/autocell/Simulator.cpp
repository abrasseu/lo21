/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include "Simulator.h"
#include "State.h"

using uint = unsigned int;

void Simulator::createCells() {
	std::cout << getCellsNbr() << std::endl;
	_cells = new State*[getCellsNbr()];


	for (uint i = 0; i < getCellsNbr(); i++)
		_cells[i] = (_states[std::rand() % _stateNbr]);
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

uint* Simulator::getCells(){        // retourne un tableau avec des 0 ou 1 (valide seulement pour 2 états dans le jeu de la vie)
    uint* _tab = new uint[getCellsNbr()];
    for (uint i = 0; i < getCellsNbr(); i++){
        if (getCell(i)->getName()[0] == ' ')
            _tab[i] = 0;
        else if (_cells[i]->getName()[0] == 0)
            _tab[i] = 1;
    }
    return _tab;
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
