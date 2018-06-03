/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_1D_H_DEFINE__
#define __SIMULATOR_1D_H_DEFINE__

#include <iostream>
#include <cmath>
#include "Cell.h"
#include "State.h"

#define uint unsigned int

class Simulator1D {
protected:
    // Liste des états et cellules composant la simulation
    State** _states;
    uint _stateNbr;
    Cell** _cells;
    uint _cellsSize;
    uint _generation;
    const uint _dimension;

    // Constructeurs
    Simulator1D(State** states, uint stateNbr, uint cellsSize, uint dimension): _states(states), _stateNbr(stateNbr), _cellsSize(cellsSize), _generation(0), _dimension(dimension) {
        createRandomCells();
    }

    // Getters
    uint getDimension() const { return _dimension; }
    State** getCellsState() const;
    uint getNeightborNbr() const { return pow(3, getDimension()) - 1; };
    virtual State** getNeightborsState(State** states, uint position);

    void createRandomCells();

public:
    // Constructeurs
    Simulator1D(State** states, uint stateNbr, uint cellsSize): Simulator1D::Simulator1D(states, stateNbr, cellsSize, 1) {}

    // Getters
    State** getInitStates() const { return _states; }
    uint getCellsSize() const { return _cellsSize; };
    uint getCellsNbr() const { return pow(_cellsSize, getDimension()); };
    Cell* getCell(uint position) const;

    virtual void printCells();

    // Renvoi vrai si la grille a changé
    bool mutate();
};

#endif
