#ifndef RULE_H_DEFINE
#define RULE_H_DEFINE value

#include <iostream>

#define uint unsigned int

class State;

class Rule {
private:
    State* state;

public:
    bool isRuleCorrect(State** states);
    State* getResultedState() const {
        return state;
    }
};

#endif
