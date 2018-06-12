/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions cellule
 */

#include "Cell.h"
#include "State.h"

using uint = unsigned int;

bool Cell::mutate(State** states, uint size) {
    State* lastState = _state;
    _state = _state->getNextGeneration(states, size);

    bool isNextGeneration = (_state != lastState);
    _generation += isNextGeneration;

    return isNextGeneration;
}
