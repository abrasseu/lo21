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

Simulator1D::Simulator1D(State** states, uint stateNbr, uint cellsNbr, uint cellsSize): _states(states), _stateNbr(stateNbr), _cellsSize(cellsSize), _cellsNbr(cellsNbr), _generation(0) {
    createRandomCells();
}

Simulator1D::Simulator1D(State** states, uint stateNbr, uint cellsNbr): _states(states), _stateNbr(stateNbr), _cellsSize(cellsNbr), _cellsNbr(cellsNbr), _generation(0) {
    createRandomCells();
}

void Simulator1D::createRandomCells() {
    _cells = new Cell*[_cellsNbr];

    for (uint i = 0; i < _cellsNbr; i++)
        _cells[i] = new Cell(_states[std::rand() % _stateNbr]);
}

Cell* Simulator1D::getCell(uint position) const {
    if (position >= _cellsNbr)
        return nullptr;

    return _cells[position];
}

State** Simulator1D::getCellsState() const {
    State** states(new State*[_cellsNbr]);

    for (uint i = 0; i < _cellsNbr; i++)
        states[i] = _cells[i]->getState();

    return states;
}

State** Simulator1D::getNeightborsState(State** states, uint position) {
    State** neighbors(new State*[getNeightborNbr()]);

    // On ajoute le précédent et le suivant:
    neighbors[0] = states[(position - 1) % _cellsNbr];
    neighbors[1] = states[(position + 1) % _cellsNbr];

    return neighbors;
}

bool Simulator1D::mutate() {
    State** statesOfThisGeneration = getCellsState();
    bool isNextGeneration = false;

    for (uint i = 0; i < _cellsNbr; i++) {
        State** neightborsState(getNeightborsState(statesOfThisGeneration, i));

        if (_cells[i]->mutate(neightborsState, getNeightborNbr()))
            isNextGeneration = true;

        delete[] neightborsState;
    }

    _generation += isNextGeneration;

    delete[] statesOfThisGeneration;
    return isNextGeneration;
}
