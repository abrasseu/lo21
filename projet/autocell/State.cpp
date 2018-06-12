/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions états
 */

#include "State.h"
#include "Rule.h"

using uint = unsigned int;

State* State::getNextGeneration(State** states, uint size) {
    for (Rule* rule : _rules) {
        if (rule->isTrue(states, size))
            return rule->getState();
    }

    return this;
}

void State::addANewRule(Rule* rule) {
    _rules.push_back(rule);
}
