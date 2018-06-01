/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_1D_H_DEFINE__
#define __SIMULATOR_1D_H_DEFINE__

#include <iostream>
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
    uint _cellsNbr;
    uint _generation;

    Simulator1D(State** states, uint stateNbr, uint cellsNbr, uint cellsSize);
    void createRandomCells();
    State** getCellsState() const;
    State** getNeightborsState(State** states, uint position);
    uint getNeightborNbr() const { return 2; };

public:
    // Constructeurs
    Simulator1D(State** states, uint stateNbr, uint cellsNbr);

    // Getters
    State** getInitStates() const { return _states; }
    uint getCellsNbr() const { return _cellsNbr; };
    Cell* getCell(uint position) const;

    // Renvoi vrai si la grille a changé
    bool mutate();
};

#endif
