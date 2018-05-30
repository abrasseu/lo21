#ifndef RULE_H_DEFINE
#define RULE_H_DEFINE value

#include <iostream>
#include "State.h"

#define uint unsigned int

class State;

class Rule {
private:
    State* _state;

public:
    Rule(State* state): _state(state) {}

    bool isRuleCorrect(State** states);
    State* getResultedState() const {
        return _state;
    }
};

#endif
