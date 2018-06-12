/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque cellule
 */

#ifndef __CELL_H_DEFINE__
#define __CELL_H_DEFINE__

#include <iostream>
#include "State.h"

using uint = unsigned int;

class Cell {
private:
    // Etat de la cellule
    State* _state;
    uint _generation;

public:
    // Constructeurs
    Cell(State* state): _state(state), _generation(0) {}

    // Getters
    State* getState() const { return _state; }
    uint getGeneration() const { return _generation; }

    // Setters
    void setState(State* state) { _state = state; }

    // Renvoi vrai si la cellule a changé d'état
    bool mutate(State** states, uint size);
};

#endif
