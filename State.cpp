#include "State.h"
#include "Rule.h"

#define uint unsigned int


State* State::getNextGeneration(State** states) {
    for (uint i = 0; i < _rulesNbr; i++) {
        if ((_rules[i])->isRuleCorrect(states))
            return (_rules[i])->getResultedState();
    }

    return this;
}
