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

using uint = unsigned int;

class State {
	private:
		// Définition
		std::string _name;
		std::string _color;

		// Règles définies pour le changement d'état
        std::vector<Rule*> _rules;

	public:
		// Constructeurs
		State(std::string name, std::string color = "#ffffff"): _name(name), _color(color) {}

		// Getters
		std::string getName() const { return _name; }
		std::string getColor() const { return _color; }
		std::vector<Rule*>::const_iterator getFirstRule() const { return _rules.begin(); }
		std::vector<Rule*>::const_iterator getLastRule() const { return _rules.end(); }
    std::vector<Rule*> getRules() const { return _rules; }

		// Setters
		void setName(std::string name) { _name = name; }
		void setColor(std::string color) { _color = color; }

		// Permet d'ajouter une nouvelle règle
		void addANewRule(Rule* rule);

		// Permet de récupérer l'état de la génération suivante en fonction des règles
		State* getNextGeneration(State** states, uint size);
};

#endif
