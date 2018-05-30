#include "State.h"
#include "Rule.h"

#define uint unsigned int

State* State::getNextGeneration(State** states, uint size) {
    for (Rule* rule : _rules) {
        if (rule->isRuleCorrect(states, size))
            return rule->getResultedState();
    }

    return this;
}

void State::addANewRule(Rule* rule) {
    _rules.push_back(rule);
}


uint State::_statesNbr = 0;
