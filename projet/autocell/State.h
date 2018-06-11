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
    std::string _name;
    std::string _color;

    // Règles définies pour le changement d'état
    std::vector<Rule*> _rules;

public:
    // Constructeurs
    State(std::string name, std::string color = "#000000"): _name(name), _color(color) {}

    // Getters
    std::string getName() const { return _name; }
    std::string getColor() const { return _color; }

    // Setters
    void setName(std::string name) { _name = name; }
    void setColor(std::string color) { _color = color; }

    // Permet d'ajouter une nouvelle règle
    void addANewRule(Rule* rule);

    // Permet de récupérer l'état de la génération suivante en fonction des règles
    State* getNextGeneration(State** states, uint size);
};

#endif
