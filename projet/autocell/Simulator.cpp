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
 * \brief Création du tableau cell
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
 * \brief Met toutes les cellules dans le première état
 * \param s     génère l'état \em s
 */
void Simulator::generateStateCells(uint s) {
	if (s >= getStateNbr())
		throw SimulatorException("Il n'y a que " + std::to_string(getStateNbr()) + " états possibles.");
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[s], i);

	setInitialCellsToActual();
}

/**
 * \brief Génère des cellules avec un état aléatoire
 */
void Simulator::generateRandomCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[std::rand() % _stateNbr], i);

	setInitialCellsToActual();
}

/**
 * \brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à l'horizontal
 */
void Simulator::generateHorizontalSymetricRandomCells() {
	setCell(_states[std::rand() % _stateNbr], 0);

	for (uint i = 1; i < getCellsNbr(); i++)
		setCell(getCell(0), i);

	setInitialCellsToActual();
}

/**
 * \brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à la verticale
 */
void Simulator::generateVerticalSymetricRandomCells() {
	for (uint i = 0; i < ceil(getCellsNbr() / 2); i++) {
		setCell(_states[std::rand() % _stateNbr], i);
		setCell(getCell(i), getCellsNbr() - 1 - i);
	}

	setInitialCellsToActual();
}

/**
 * \brief Génère des cellules de manière alternée: dans l'ordre des états croissant
 */
void Simulator::generateAlternedCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(_states[i % _stateNbr], i);

	setInitialCellsToActual();
}

/**
 * \brief Génère des cellules de manière alternée: dans l'ordre des états décroissant
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

/**
 * \brief Applique un état à une cellule
 * \param state     état
 * \param position  emplacement de la cellule
 * \return Renvoie un \em booléen
 */
bool Simulator::setCell(State* state, uint position) {
	if (position >= getCellsNbr())
		return false;

	State* lastState(getCell(position));
	_cells[position] = state;

	return state != lastState;
}

/**
 * \brief Remet les cellules de l'état initial à l'état actuel
 */
void Simulator::setInitialCellsToActual() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setInitialCell(getCell(i), i);
}

/**
 * \brief Remet les cellules de l'état actuel à l'état initial
 */
void Simulator::resetToInitialCells() {
	for (uint i = 0; i < getCellsNbr(); i++)
		setCell(getInitialCell(i), i);
}


/**
 * \brief Changer une cellule de l'état initial
 * \return Renvoie un \em booléen qui indique si la modification a réussi
 */
bool Simulator::setInitialCell(State* state, uint position) {
	if (position >= getCellsNbr())
		return false;

	State* lastState(getInitialCell(position));
	_initialCells[position] = state;

	return state != lastState;
}

/**
 * \brief Récupère l'état de la cellule
 * \param position       position de la cellule
 * \return Un \em pointeur \em d' \em état
 */
State* Simulator::getCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _cells[position];
}

/**
 * \brief Récupère l'état d'une cellule à l'état initial
 * \param position       position de la cellule
 * \return Un \em pointeur \em d' \em état
 */
State* Simulator::getInitialCell(uint position) const {
	if (position >= getCellsNbr())
		return nullptr;

	return _initialCells[position];
}

/**
 * \brief Applique la règle si les conditions sont respectées
 * \param states     liste des états
 * \param size       position de la règle
 * \return Renvoie un \em tableau \em de \em pointeurs d'états
 */
State** Simulator::getCellsState() const {
	State** states(new State*[getCellsNbr()]);

	for (uint i = 0; i < getCellsNbr(); i++)
		states[i] = _cells[i];

	return states;
}


/**
 * \brief Renvoie un tableau de 0 et 1 utilisé pour l'affichage du jeu de la vie en console
 * \return Renvoie un \em tableau \em d' \em entiers
 */
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

/**
 * \brief Incrémente un état
 * \param position     position de l'état
 * \param allowNullState   autorise un état nul
 */
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

/**
 * \brief Modifie les états possibles de la simulation
 */
void Simulator::setStates(State** states, uint stateNbr) {
    _stateNbr = stateNbr;
    _states = states;
}


/**
 * \brief Applique une mutation sur un simulateur
 * \return Renvoie un \em booléen signifiant qu'une mutation a été effectuée ou non
 */
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
