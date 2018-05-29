#ifndef STATE_H_DEFINE
#define STATE_H_DEFINE value

#include <iostream>
#include <string>

#define uint unsigned int

class Rule;

class State {
private:
    // Définition
    static uint _statesNbr;
    uint _id;
    std::string _color;

    // Règles définies pour le changement d'état
    uint _rulesNbr;
    Rule** _rules;

public:
    State(): _id(_statesNbr++), _color("#000000"), _rulesNbr(0) {}
    State(uint id): _id(id), _color("#000000"), _rulesNbr(0) { _statesNbr++; }
    State(std::string color): _id(_statesNbr++), _color(color), _rulesNbr(0) {}
    State(uint id, std::string color): _id(id), _color(color), _rulesNbr(0) { _statesNbr++; }

    uint getId() const { return _id; }
    std::string getColor() const { return _color; }

    State* getNextGeneration(State** states);
};

uint State::_statesNbr = 0;

#endif
