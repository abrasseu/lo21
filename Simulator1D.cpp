/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions règles
 */

#include <iostream>
#include <vector>
#include "Simulator1D.h"
#include "Cell.h"
#include "State.h"

#define uint unsigned int

void Simulator1D::createRandomCells() {
    _cells = new Cell*[getCellsNbr()];

    std::cout << "Simu: " << getCellsNbr() << std::endl;

    for (uint i = 0; i < getCellsNbr(); i++)
        _cells[i] = new Cell(_states[std::rand() % _stateNbr]);
}

Cell* Simulator1D::getCell(uint position) const {
    if (position >= getCellsNbr())
        return nullptr;

    return _cells[position];
}

State** Simulator1D::getCellsState() const {
    State** states(new State*[getCellsNbr()]);

    for (uint i = 0; i < getCellsNbr(); i++)
        states[i] = _cells[i]->getState();

    return states;
}

State** Simulator1D::getNeightborsState(State** states, uint position) {
    State** neighbors(new State*[getNeightborNbr()]);

    // On ajoute le précédent et le suivant:
    neighbors[0] = states[(position - 1) % getCellsNbr()];
    neighbors[1] = states[(position + 1) % getCellsNbr()];

    return neighbors;
}

void Simulator1D::printCells() {
    for (uint i = 0; i < getCellsSize(); i++)
        std::cout << _cells[i]->getState()->getId();

    std::cout << std::endl;
}

bool Simulator1D::mutate() {
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
