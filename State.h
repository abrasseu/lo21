/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de générer les états possibles pour une cellule.
 * Bien évidemment, un état peut se transformer en un autre via des règles
 */

#ifndef __STATE_H_DEFINE__
#define __STATE_H_DEFINE__

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
    // Constructeurs
    State(): _id(_statesNbr++), _color("#000000") {}
    State(uint id): _id(id), _color("#000000") { _statesNbr++; }
    State(std::string color): _id(_statesNbr++), _color(color) {}
    State(uint id, std::string color): _id(id), _color(color) { _statesNbr++; }

    // Getters
    uint getId() const { return _id; }
    std::string getColor() const { return _color; }

    // Setters
    void setColor(std::string color) { _color = color; }

    // Permet d'ajouter une nouvelle règle
    void addANewRule(Rule* rule);

    // Permet de récupérer l'état de la génération suivante en fonction des règles
    State* getNextGeneration(State** states, uint size);
};

#endif
