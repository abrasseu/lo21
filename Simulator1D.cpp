/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur 1D
 */

#include <iostream>
#include <vector>
#include "Simulator1D.h"
#include "Cell.h"
#include "State.h"

#define uint unsigned int

void Simulator1D::createCells() {
    std::cout << getCellsNbr() << std::endl;
    _cells = new Cell*[getCellsNbr()];


    for (uint i = 0; i < getCellsNbr(); i++)
        _cells[i] = new Cell(_states[std::rand() % _stateNbr]);
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
        std::cout << _cells[i]->getState()->getName();

    std::cout << std::endl;
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
