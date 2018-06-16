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
#include <fstream>
#include "nlohmann/json.hpp"

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
		throw SimulatorException("Aucune simulation n'a été instanciée");

	return _simulator;
}

Simulator* SimulatorManager::createSimulator(uint dimension) {
	deleteSimulator();

	if (dimension == 0)
		dimension = _dimension;

	switch (dimension) {
		case 1:
			_simulator = new Simulator1D(&_states[0], _states.size(), _gridSize);
			break;
		case 2:
			_simulator = new Simulator2D(&_states[0], _states.size(), _gridSize);
			break;
		default:
			throw SimulatorException("Cette dimension de simulation n'est pas encore implémentée.");
	}

	_dimension = dimension;
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
		throw SimulatorException("L'état " + std::to_string(position) + " n'existe pas !");

	return _states[position];
}

State* SimulatorManager::createNewState(std::string name, std::string color) {
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
		throw SimulatorException("La règle " + std::to_string(position) + " n'existe pas !");

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
	typename std::vector<T*>::const_iterator it = find(container->begin(), container->end(), object);

	if (it == container->end())
		throw SimulatorException("L'objet n'existe pas");

	container->erase(it);
	delete object;
}

template<class T>
uint SimulatorManager::findObject(T* object, std::vector<T*>* container) {
	typename std::vector<T*>::const_iterator it = find(container->begin(), container->end(), object);

	if (it == container->end())
		throw SimulatorException("L'objet n'existe pas");

	return it - container->begin();
}


/*
|--------------------------------------------------------------------------
|	Import/Export Methods
|--------------------------------------------------------------------------
*/

void SimulatorManager::exportConfig(std::string uri) {
	nlohmann::json states = nlohmann::json::array();
	nlohmann::json rules = nlohmann::json::array();

	// Première étape: on liste tous nos paramètres
	nlohmann::json simulator = {
	  {"dimension", _dimension},
	  {"grid_size", _gridSize},
	  {"states", nlohmann::json::array()},
	};

	// Deuxième étape: on liste tous nos états possibles
	for (std::vector<State*>::const_iterator state = getFirstState(); state != getLastState(); state++) {
		states += {
			{"name", (*state)->getName()},
			{"color", (*state)->getColor()},
		};
	}

	// Troisième étape: on liste toutes nos règles possibles
	for (std::vector<Rule*>::const_iterator rule = getFirstRule(); rule != getLastRule(); rule++) {
		nlohmann::json transitions = nlohmann::json::array();

		for (std::vector<State*>::const_iterator transition = (*rule)->getFirstState(); transition != (*rule)->getLastState(); transition++)
			transitions += findObject<State>((*transition), &_states);

		rules += {
			{"state", findObject<State>((*rule)->getState(), &_states)},
			{"transition_states", transitions},
		};
	}

	// Quatrième étape: on liste les règles utilisées par chaque état
	for (std::vector<State*>::const_iterator state = getFirstState(); state != getLastState(); state++) {
		nlohmann::json transitions = nlohmann::json::array();

		for (std::vector<Rule*>::const_iterator transition = (*state)->getFirstRule(); transition != (*state)->getLastRule(); transition++)
			transitions += findObject<Rule>((*transition), &_rules);

		states[state - getFirstState()]["transition_rules"] = transitions;
	}

	// Cinquième étape: on liste l'état actuel de notre simulation
	for (uint i = 0; i < getSimulator()->getCellsNbr(); i++)
		simulator["states"] += findObject<State>(getSimulator()->getCell(i), &_states);

	// Sixième étape: on exporte la configuration
	nlohmann::json config = {
		{"rules", rules},
		{"states", states},
		{"simulator", simulator},
	};

	std::ofstream exportFile;
	exportFile.open(uri);
	exportFile << config.dump(2);
	exportFile.close();
}
