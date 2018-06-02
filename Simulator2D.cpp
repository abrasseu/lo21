/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions règles
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

    // On ajoute les précédents et les suivants:
    neighbors[0] = states[(position - getCellsSize() - 1) % getCellsNbr()];
    neighbors[1] = states[(position - getCellsSize()) % getCellsNbr()];
    neighbors[2] = states[(position - getCellsSize() + 1) % getCellsNbr()];
    neighbors[3] = states[(position - 1) % getCellsNbr()];
    neighbors[4] = states[(position + 1) % getCellsNbr()];
    neighbors[5] = states[(position + getCellsSize() - 1) % getCellsNbr()];
    neighbors[6] = states[(position + getCellsSize()) % getCellsNbr()];
    neighbors[7] = states[(position + getCellsSize() + 1) % getCellsNbr()];

    return neighbors;
}

void Simulator2D::printCells() {
    for (uint i = 0; i < getCellsSize(); i++) {
        for (uint j = 0; j < getCellsSize(); j++)
            std::cout << getCell(i, j)->getState()->getId();

        std::cout << std::endl;
    }
}

bool Simulator2D::mutate() {
    State** statesOfThisGeneration = getCellsState();
    bool isNextGeneration = false;

    for (uint i = 0; i < getCellsNbr(); i++) {
        State** neightborsState(getNeightborsState(statesOfThisGeneration, i));

        if (_cells[i]->mutate(neightborsState, getNeightborNbr()))
            isNextGeneration = true;

        delete[] neightborsState;
    }

    _generation += isNextGeneration;

    delete[] statesOfThisGeneration;
    return isNextGeneration;
}
