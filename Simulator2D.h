/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_2D_H_DEFINE__
#define __SIMULATOR_2D_H_DEFINE__

#include <iostream>
#include "Simulator1D.h"
#include "Cell.h"
#include "State.h"

#define uint unsigned int

class Simulator2D : public Simulator1D {
protected:
    // Constructeurs
    Simulator2D(State** states, uint stateNbr, uint cellsSize, uint dimension): Simulator1D::Simulator1D(states, stateNbr, cellsSize, dimension) {};

    using Simulator1D::createCells;
    State** getNeightborsState(State** states, uint position);

public:
    // Constructeurs
    Simulator2D(State** states, uint stateNbr, uint cellsSize): Simulator1D::Simulator1D(states, stateNbr, cellsSize, 2) {
        createCells();
    };

    // Getters
    using Simulator1D::getCell;
    Cell* getCell(uint x, uint y) const;

    void printCells();
};

#endif
