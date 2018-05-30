/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions cellule
 */

#include "Cell.h"
#include "State.h"

#define uint unsigned int

bool Cell::mutate(State** states, uint size) {
    State* lastState = _state;
    _state = _state->getNextGeneration(states, size);

    _generation++;

    return _state != lastState;
}
