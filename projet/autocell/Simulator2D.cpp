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

using uint = unsigned int;

/**
 * \brief Renvoie la cellule aux positions sélectionnées
 * \param x ligne de la cellule sélectionnée
 * \param y colonne de la cellule sélectionnée
 * \return Renvoie un \em pointeur d'état
 */
State* Simulator2D::getCell(uint x, uint y) const {
	return getCell((x * getCellsSize()) + y);
}

/**
 * \brief Met une cellule à jour
 * \param state pointeur de l'état à copier
 * \param x ligne de la cellule sélectionnée
 * \param y colonne de la cellule sélectionnée
 * \return Renvoie un \em booléen pour indiquer si la mise à jour a réussi
 */
bool Simulator2D::setCell(State* state, uint x, uint y) {
	return setCell(state, (x * getCellsSize()) + y);
}

/**
 * \brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à l'horizontal
 */
void Simulator2D::generateHorizontalSymetricRandomCells() {
	for (uint i = 0; i < ceil(getCellsSize() / 2); i++) {
		for (uint j = 0; j < getCellsSize(); j++) {
			setCell(_states[std::rand() % _stateNbr], i, j);
			setCell(getCell(i, j), getCellsSize() - 1 - i, j);
		}
	}
}

/**
 * \brief Génère la moitié des cellules aléatoirement et réalise la symétrie sur les autres cellules par rapport à la verticale
 */
void Simulator2D::generateVerticalSymetricRandomCells() {
	for (uint i = 0; i < getCellsSize(); i++) {
		for (uint j = 0; j < ceil(getCellsSize() / 2); j++) {
			setCell(_states[std::rand() % _stateNbr], i, j);
			setCell(getCell(i, j), i, getCellsSize() - 1 - j);
		}
	}
}
/**
 * \brief Retourne les états des voisins de la cellule
 * \param states     tableau de pointeurs d'états
 * \param position       position de la cellule
 * \return Renvoie un \em tableau \em de \em pointeurs d'états
 */
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

/**
 * \brief Affiche les cellules en console
 */
void Simulator2D::printCells() {
	for (uint i = 0; i < getCellsSize(); i++) {
		for (uint j = 0; j < getCellsSize(); j++)
			std::cout << getCell(i, j)->getName()[0];

		std::cout << std::endl;
	}
}
/**
 * \brief Incrémente un état
 * \param x     ligne de la cellule
 * \param y colonne de la cellule
 */
void Simulator2D::incrementState(uint x, uint y) {
    incrementState((x * getCellsSize()) + y);
}
