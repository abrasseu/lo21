/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include "Simulator.h"
#include "Simulator1D.h"
#include "State.h"

using uint = unsigned int;
/**
 * \brief Retourne les états des voisins de la cellule
 * \param states     tableau de pointeurs d'états
 * \param position       position de la cellule
 * \return Renvoie un \em tableau \em de \em pointeurs d'états
 */
State** Simulator1D::getNeighboursState(State** states, uint position) {
    State** neighbours(new State*[getNeighbourNbr()]);

	// On ajoute le précédent et le suivant:
    neighbours[0] = states[(position - 1) % getCellsNbr()];
    neighbours[1] = states[(position + 1) % getCellsNbr()];

    return neighbours;
}

/**
 * \brief Affiche les cellules en console
 */
void Simulator1D::printCells() {
	for (uint i = 0; i < getCellsSize(); i++)
		std::cout << _cells[i]->getName()[0];

	std::cout << std::endl;
}
