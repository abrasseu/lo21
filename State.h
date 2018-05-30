#ifndef STATE_H_DEFINE
#define STATE_H_DEFINE value

#include <iostream>
#include <string>
#include <vector>
#include "Rule.h"

#define uint unsigned int

class Rule;

class State {
private:
    // Définition
    static uint _statesNbr;
    uint _id;
    std::string _color;

    // Règles définies pour le changement d'état
    std::vector<Rule*> _rules;

public:
    State(): _id(_statesNbr++), _color("#000000") {}
    State(uint id): _id(id), _color("#000000") { _statesNbr++; }
    State(std::string color): _id(_statesNbr++), _color(color) {}
    State(uint id, std::string color): _id(id), _color(color) { _statesNbr++; }

    uint getId() const { return _id; }
    std::string getColor() const { return _color; }

    void addANewRule(Rule* rule);

    State* getNextGeneration(State** states, uint size);
};

#endif
