/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de créer des règles de changement d'état
 * Elle prend en compte les états des voisins (de manière organisé ou en quantité)
 */

#ifndef __RULE_H_DEFINE__
#define __RULE_H_DEFINE__

#include <iostream>
#include <vector>
#include "State.h"

using uint = unsigned int;

class State;

class Rule {
private:
    // Etat retourné pour la règle
    State* _state;

    // Liste des états à trouver
    std::vector<State*> _states;

public:
    // Constructeurs
    Rule(State* state, std::vector<State*> states): _state(state), _states(states) {}
    Rule(State* state, State** states, uint size): _state(state) {
        for (uint i = 0; i < size; i++)
            _states.push_back(states[i]);
    }

    // Getters
    State* getState() const { return _state; }
    std::vector<State*>::const_iterator getFirstState() const { return _states.begin(); }
	std::vector<State*>::const_iterator getLastState() const { return _states.end(); }

    // Permet de vérifier si la règle est vraie
    bool isTrue(State** states, uint size);
};

#endif
