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

using namespace std;

class State {
	private:
		// Définition
		string _name;
		string _color;

		// Règles définies pour le changement d'état
		vector<Rule*> _rules;

	public:
		// Constructeurs
		State(string name, string color = "#ffffff"): _name(name), _color(color) {}

		// Getters
		string getName() const { return _name; }
		string getColor() const { return _color; }

		// Setters
		void setName(string name) { _name = name; }
		void setColor(string color) { _color = color; }

		// Permet d'ajouter une nouvelle règle
		void addANewRule(Rule* rule);

		// Permet de récupérer l'état de la génération suivante en fonction des règles
		State* getNextGeneration(State** states, uint size);
};

#endif
