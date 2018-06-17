/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Simulator.h"
#include "State.h"

using uint = unsigned int;

/**
 * @brief Création du tableau cell
 */
void Simulator::generateCells() {
	_cells = new State*[getCellsNbr()];
	_initialCells = new State*[getCellsNbr()];
	generateStateCells();
}

/*
|--------------------------------------------------------------------------
|	Générateurs
|--------------------------------------------------------------------------
*/

/**
 * @brief Met toutes les cellules dans le première état
 */
void Simulator::generateStateCells(uint s) {
	if (s >= getStateNbr())
		throw SimulatorException("Il n'y a que " + std::to_string(getStateNbr()) + " états possibles.");
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[s], i);

	setInitialCellsToActual();
}

/**
 * @brief Génère des cellules avec un état aléatoire
 */
void Simulator::generateRandomCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[std::rand() % _stateNbr], i);

	setInitialCellsToActual();
}

/**
 * @brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à l'horizontal
 */
void Simulator::generateHorizontalSymetricRandomCells() {
	setCell(_states[std::rand() % _stateNbr], 0);

	for (uint i = 1; i < getCellsNbr(); i++)
		setCell(getCell(0), i);

	setInitialCellsToActual();
}

/**
 * @brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à la verticale
 */
void Simulator::generateVerticalSymetricRandomCells() {
	for (uint i = 0; i < ceil(getCellsNbr() / 2); i++) {
		setCell(_states[std::rand() % _stateNbr], i);
		setCell(getCell(i), getCellsNbr() - 1 - i);
	}

	setInitialCellsToActual();
}

/**
 * @brief Génère des cellules de manière alternée: dans l'ordre des états croissant
 */
void Simulator::generateAlternedCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[i % _stateNbr], i);

	setInitialCellsToActual();
}

/**
 * @brief Génère des cellules de manière alternée: dans l'ordre des états décroissant
 */
void Simulator::generateDescAlternedCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[_stateNbr - (i % _stateNbr) - 1], i);

	setInitialCellsToActual();
}


/*
|--------------------------------------------------------------------------
|	Getters & Setters
|--------------------------------------------------------------------------
*/

bool Simulator::setCell(State* state, uint position) {
	if (position >= getCellsNbr())
		return false;

	State* lastState(getCell(position));
	_cells[position] = state;

	return state != lastState;
}

void Simulator::setInitialCellsToActual() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setInitialCell(getCell(i), i);
}

void Simulator::resetToInitialCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(getInitialCell(i), i);
}

bool Simulator::setInitialCell(State* state, uint position) {
	if (position >= getCellsNbr())
		return false;

	State* lastState(getInitialCell(position));
	_initialCells[position] = state;

	return state != lastState;
}

State* Simulator::getCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _cells[position];
}

State* Simulator::getInitialCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _initialCells[position];
}

State** Simulator::getCellsState() const {
	State** states(new State*[getCellsNbr()]);

	for (uint i = 0; i < getCellsNbr(); i++)
		states[i] = _cells[i];

	return states;
}


// retourne un tableau avec des 0 ou 1 (valide seulement pour 2 états dans le jeu de la vie)
// TODO : Pas ouf..
uint* Simulator::getCells() {
	uint* _tab = new uint[getCellsNbr()];
	for (uint i = 0; i < getCellsNbr(); i++){
		if (getCell(i)->getName()[0] == ' ')
			_tab[i] = 0;
		else if (_cells[i]->getName()[0] == 0)
			_tab[i] = 1;
	}
	return _tab;
}

void Simulator::incrementState(uint position) {
	State* cellToUpdate(getCell(position));
	uint toStateId = 0;

	for (uint i = 0; i < _stateNbr; i++) {
		if (_states[i] == cellToUpdate) {
			toStateId = (i + 1) % _stateNbr;

			break;
		}
	}

	setCell(_states[toStateId], position);
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

	if (isNextGeneration)
		_generation++;

	delete[] statesOfThisGeneration;
	return isNextGeneration;
}
