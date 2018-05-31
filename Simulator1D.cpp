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

Simulator1D::Simulator1D(State** states, uint stateNbr, uint cellsSize): _states(states), _stateNbr(stateNbr), _cellsSize(cellsSize), _generation(0) {
    _cells = new Cell*[getCellNbr()];

    for (uint i = 0; i < getCellNbr(); i++)
        _cells[i] = new Cell(_states[std::rand() % _stateNbr]);
}

uint Simulator1D::getCellNbr() const {
    return _cellsSize;
}

Cell* Simulator1D::getCell(uint position) const {
    if (position >= getCellNbr())
        return nullptr;

    return _cells[position];
}

State** Simulator1D::getCellsState() const {
    State** states(new State*[getCellNbr()]);

    for (uint i = 0; i < getCellNbr(); i++)
        states[i] = _cells[i]->getState();

    return states;
}

State** Simulator1D::getNeightborsState(State** states, uint position) {
    State** neighbors(new State*[getNeightborNbr()]);

    // On ajoute le précédent et le suivant:
    neighbors[0] = states[(position - 1) % getCellNbr()];
    neighbors[1] = states[(position + 1) % getCellNbr()];

    return neighbors;
}

bool Simulator1D::mutate() {
    State** statesOfThisGeneration = getCellsState();
    bool isNextGeneration = false;

    for (uint i = 0; i < getCellNbr(); i++) {
        State** neightborsState(getNeightborsState(statesOfThisGeneration, i));

        if (_cells[i]->mutate(neightborsState, getNeightborNbr()))
            isNextGeneration = true;

        delete[] neightborsState;
    }

    _generation += isNextGeneration;

    delete[] statesOfThisGeneration;
    return isNextGeneration;
}
