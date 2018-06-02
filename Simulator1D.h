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

    Simulator1D(State** states, uint stateNbr, uint cellsSize, uint dimension): _states(states), _stateNbr(stateNbr), _cellsSize(cellsSize), _generation(0), _dimension(dimension) {
        createRandomCells();
    }
    void createRandomCells();
    State** getCellsState() const;
    State** getNeightborsState(State** states, uint position);

    uint getNeightborNbr() const { return pow(3, _dimension) - 1; };

public:
    // Constructeurs
    Simulator1D(State** states, uint stateNbr, uint cellsSize): _states(states), _stateNbr(stateNbr), _cellsSize(cellsSize), _generation(0), _dimension(1) {
        createRandomCells();
    }

    // Getters
    State** getInitStates() const { return _states; }
    uint getCellsSize() const { return _cellsSize; };
    uint getCellsNbr() const { return pow(_cellsSize, _dimension); };
    Cell* getCell(uint position) const;

    void printCells();

    // Renvoi vrai si la grille a changé
    bool mutate();
};

#endif
