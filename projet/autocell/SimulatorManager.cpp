/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#include "SimulatorManager.h"
#include <algorithm>

using namespace std;
using uint = unsigned int;

// Singleton
SimulatorManager* SimulatorManager::_instance = 0;


/*
|--------------------------------------------------------------------------
|	Simulator
|--------------------------------------------------------------------------
*/
Simulator* SimulatorManager::getSimulator(bool throwException) {
	if (_simulator)
		return _simulator;
	if (throwException)
		throw SimulatorException("Le simulateur n'exite pas");
	return 0;
}

Simulator* SimulatorManager::createSimulator(uint dimension, uint cellsSize, vector<State >* states) {
	if (_simulator)
		throw SimulatorException("Un simulateur existe déjà");
	if (states == nullptr)
		states = &_states;
	switch (dimension) {
		case 1:
			_simulator = new Simulator1D(states, states->size(), cellsSize);
			break;
		case 2:
			_simulator = new Simulator2D(states, states->size(), cellsSize);
			break;
		default:
			throw SimulatorException("Cette dimension de simulation n'est pas encore implémentée.");
	}
	return _simulator;
}
void SimulatorManager::deleteSimulator() {
	if (_simulator)
		delete _simulator;
}


/*
|--------------------------------------------------------------------------
|	States
|--------------------------------------------------------------------------
*/

State* SimulatorManager::createNewState(string name, string color) {
	State* state = new State(name, color);
	_states.push_back(state);
	return state;
}
void SimulatorManager::removeState(State* state) {
	removeObject(state, _states);
}

/*
|--------------------------------------------------------------------------
|	Rules
|--------------------------------------------------------------------------
*/

Rule* SimulatorManager::getRule(uint position) {
	if (position >= _rules.size())
		throw new SimulatorException("La règle " + to_string(position) + " n'existe pas !");

	return _rules[position];
}

Rule* SimulatorManager::createNewRule(vector<State*> states, string endState) {
	_rules.push_back(new Rule(endState, states));

	return _rules.back();
}
void SimulatorManager::removeRule(Rule* rule) {
	removeObject(rule, _rules);
}


/*
|--------------------------------------------------------------------------
|	Template Methods
|--------------------------------------------------------------------------
*/

template<class T>
void SimulatorManager::removeObject(T* object, vector<T*>* container) {
	vector<T*>::const_iterator it;
	it = find(container->begin(), container->end(), object);
	if (it == container->end())
		throw SimulatorException("L'objet n'existe pas");
	container->erase(it);
	delete object;
}
