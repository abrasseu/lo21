#include "State.h"
#include "Rule.h"

#define uint unsigned int

State* State::getNextGeneration(State** states) {
    for (uint i = 0; i < _rules.size(); i++) {
        if ((_rules[i])->isRuleCorrect(states))
            return (_rules[i])->getResultedState();
    }

    return this;
}

void State::addANewRule(Rule* rule) {
    _rules.push_back(rule);
}


uint State::_statesNbr = 0;
