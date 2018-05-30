#include <iostream>
#include "Rule.h"
#include "State.h"

#define uint unsigned int

int main() {
    std::cout << "Coucou" << std::endl;

    State** states;
    states = new State*[5];

    for (uint i = 0; i < 5; i++)
        states[i] = new State;

    Rule rule(states[4], states, 5);
    states[1]->addANewRule(&rule);

    std::cout << "Passage de l'état 1 à l'état " << (states[1])->getNextGeneration(states, 5)->getId() << std::endl;

    return 0;
}
