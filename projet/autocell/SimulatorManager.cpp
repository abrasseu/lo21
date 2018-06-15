/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#include "SimulatorManager.h"

using namespace std;
using uint = unsigned int;

// Singleton
SimulatorManager* SimulatorManager::_instance = 0;


Rule* SimulatorManager::getRule(uint position) {
	if (position >= _rules.size())
		throw new SimulatorException("La règle " + to_string(position) + " n'existe pas !");

	return _rules[position];
}

State* SimulatorManager::createNewState(string name, string color) {
	_states.push_back(new State(name, color));

	return _states.back();
}

Rule* SimulatorManager::createNewRule(vector<State*> states, string endState) {
//	_rules.push_back(new Rule(endState, states));

	return _rules.back();
}
