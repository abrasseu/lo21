/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 2D
 */

#include <iostream>
#include <vector>
#include "Simulator1D.h"
#include "Simulator2D.h"
#include "State.h"
#include "Rule.h"

#define uint unsigned int

Cell* Simulator2D::getCell(uint x, uint y) const {
    return Simulator1D::getCell((x * getCellsSize()) + y);
}

State** Simulator2D::getNeightborsState(State** states, uint position) {
    State** neighbors(new State*[getNeightborNbr()]);
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
            std::cout << getCell(i, j)->getState()->getName();

        std::cout << std::endl;
    }
}

void Simulator2D::incrementState(uint x, uint y) {
    return Simulator1D::incrementState((x * getCellsSize()) + y);
}
