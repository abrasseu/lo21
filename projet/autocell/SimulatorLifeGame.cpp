/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions pour un simulateur du jeu de la vie
 */

#include <iostream>
#include <vector>
#include "SimulatorLifeGame.h"
#include "Simulator2D.h"
#include "State.h"
#include "Rule.h"

using uint = unsigned int;

SimulatorLifeGame::SimulatorLifeGame(uint cellsSize): Simulator2D(new State*[2], 2, cellsSize) {
	_states[0] = new State(" - Mort"); // mort
	_states[1] = new State("0 - Vivant", "#FFFFFF"); // vivant

	// Si une cellule vivante est entourée d'au moins 7 cellules mortes, elle meurt à son tour
	std::vector<State*> forRule1({_states[0], _states[0], _states[0], _states[0], _states[0], _states[0], _states[0]});
	Rule* rule1 = new Rule(_states[0], forRule1);
	_states[1]->addANewRule(rule1);

	// Si une cellule morte est entourée de 3 cellules vivantes, elle vit à son tour
	std::vector<State*> forRule2({_states[1], _states[1], _states[1], _states[0], _states[0], _states[0], _states[0], _states[0]});
	Rule* rule2 = new Rule(_states[1], forRule2);
	_states[0]->addANewRule(rule2);

	// Si une cellule vivante est entourée d'au moins 4 cellules vivantes, elle meurt par étouffement
	std::vector<State*> forRule3({_states[1], _states[1], _states[1], _states[1]});
	Rule* rule3 = new Rule(_states[0], forRule3);
	_states[1]->addANewRule(rule3);

	Simulator2D::generateCells();
}
