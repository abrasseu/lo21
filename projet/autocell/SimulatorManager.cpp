/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#include "SimulatorManager.h"
#include "Simulator1D.h"
#include "Simulator2D.h"
#include "SimulatorLifeGame.h"
#include <algorithm>

using uint = unsigned int;

// Singleton
SimulatorManager* SimulatorManager::_instance = new SimulatorManager;

/*
|--------------------------------------------------------------------------
|	Simulator
|--------------------------------------------------------------------------
*/

Simulator* SimulatorManager::getSimulator() {
	if (_simulator == nullptr)
		throw SimulatorException("Le simulateur n'existe pas");
	return _simulator;
}

Simulator* SimulatorManager::createSimulator(uint dimension) {
	deleteSimulator();

	switch (dimension) {
		case 1:
			_simulator = new Simulator1D(&_states[0], _states.size(), _gridSize);
			break;
		case 2:
			_simulator = new Simulator2D(&_states[0], _states.size(), _gridSize);
			break;
		case 21:
			_simulator = new SimulatorLifeGame(_gridSize);
			break;
		default:
			throw SimulatorException("Cette dimension de simulation n'est pas encore implémentée.");
	}

	return _simulator;
}

void SimulatorManager::deleteSimulator() {
	if (_simulator != nullptr)
		delete _simulator;
}


/*
|--------------------------------------------------------------------------
|	States
|--------------------------------------------------------------------------
*/

State* SimulatorManager::getState(uint position) {
	if (position >= _states.size())
		throw SimulatorException("L'état n'existe pas");
	return _states[position];
}

State* SimulatorManager::getState(const std::string& name) {
	std::vector<State*>::iterator it = std::find_if(_states.begin(), _states.end(),
		[&name](State* state) { return state->getName() == name; });
	if (it == _states.end())
		throw SimulatorException("L'état n'existe pas");
	return (*it);
}

State* SimulatorManager::createNewState(std::string name, std::string color) {
	bool already_exists = false;
	// Verification de doublon
	for (std::vector<State*>::const_iterator it = _states.begin(); it != _states.end(); ++it) {
		if ((*it)->getName() == name)
			already_exists = true;
		if ((*it)->getColor() == color)
			already_exists = true;
		if (already_exists)
			throw SimulatorException("L'état existe déjà");
	}
	// Add State to the vector
	State* state = new State(name, color);
	_states.push_back(state);
	return state;
}
void SimulatorManager::removeState(State* state) {
	removeObject<State>(state, &_states);
}

/*
|--------------------------------------------------------------------------
|	Rules
|--------------------------------------------------------------------------
*/

Rule* SimulatorManager::getRule(uint position) {
	if (position >= _rules.size())
		throw new SimulatorException("La règle " + std::to_string(position) + " n'existe pas !");

	return _rules[position];
}

Rule* SimulatorManager::createNewRule(std::vector<State*> states, State* endState) {
	_rules.push_back(new Rule(endState, states));

	return _rules.back();
}
void SimulatorManager::removeRule(Rule* rule) {
	removeObject<Rule>(rule, &_rules);
}


/*
|--------------------------------------------------------------------------
|	Template Methods
|--------------------------------------------------------------------------
*/

template<class T>
void SimulatorManager::removeObject(T* object, std::vector<T*>* container) {
	typename std::vector<T*>::const_iterator it;
	it = find(container->begin(), container->end(), object);
	if (it == container->end())
		throw SimulatorException("L'objet n'existe pas");
	container->erase(it);
	delete object;
}
