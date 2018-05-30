#ifndef RULE_H_DEFINE
#define RULE_H_DEFINE value

#include <iostream>
#include <vector>
#include "State.h"

#define uint unsigned int

class State;

class Rule {
private:
    // Etat retourné pour la règle
    State* _state;
    // Liste des états à trouver
    std::vector<State*> _states;
    bool _orderedStates;

public:
    Rule(State* state, std::vector<State*> states, bool orderedStates = false): _state(state), _states(states), _orderedStates(orderedStates) {}
    Rule(State* state, State** states, uint size, bool orderedStates = false): _state(state), _orderedStates(orderedStates) {
        for (uint i = 0; i < size; i++)
            _states.push_back(states[i]);
    }


    bool isRuleCorrect(State** states, uint size);
    State* getResultedState() const {
        return _state;
    }
};

#endif
