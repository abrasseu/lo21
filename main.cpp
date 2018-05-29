#include <iostream>
#include "Rule.h"
#include "State.h"

#define uint unsigned int

int main() {
    std::cout << "Coucou" << std::endl;

    State state;
    State** states;
    states = new State*[5];

    for (uint i = 0; i < 5; i++)
        states[i] = new State;

    std::cout << (states[1])->getId() << std::endl;

    return 0;
}
