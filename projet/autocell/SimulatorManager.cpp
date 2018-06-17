/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#include "SimulatorManager.h"
#include "Simulator1D.h"
#include "Simulator2D.h"

#include <algorithm>
#include <fstream>
#include "nlohmann/json.hpp"

using uint = unsigned int;

// Singleton
SimulatorManager* SimulatorManager::_instance = new SimulatorManager;

/*
|--------------------------------------------------------------------------
|	Grid size
|--------------------------------------------------------------------------
*/

void SimulatorManager::setGridSize(uint gridSize) {
	if (gridSize > 100)
		throw SimulatorException("Il n'est pas possible de générer une grille avec une taille supérieure à 100");

	_gridSize = gridSize;
}


/*
|--------------------------------------------------------------------------
|	Simulator
|--------------------------------------------------------------------------
*/

Simulator* SimulatorManager::getSimulator() {
	if (_simulator == nullptr)
		throw SimulatorException("Aucune simulation n'a été instanciée");
    else
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

	_simulator = nullptr;
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

	for (std::vector<Rule*>::const_iterator rule = getFirstRule(); rule != getLastRule();) {
		if ((*rule)->getState() != state) {
			bool isIn = false;

			for (std::vector<State*>::const_iterator stateOfRule = (*rule)->getFirstState(); stateOfRule != (*rule)->getLastState(); stateOfRule++) {
				if ((*stateOfRule) == state)
					isIn = true;
			}

			if (!isIn) {
				rule++;
				continue;
			}
		}

		removeRule((*rule));
	}
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

	for (std::vector<State*>::const_iterator state = getFirstState(); state != getLastState(); state++) {
		for (std::vector<Rule*>::const_iterator ruleOfState = (*state)->getFirstRule(); ruleOfState != (*state)->getLastRule();) {
			if ((*ruleOfState) == rule)
				(*state)->removeRule(ruleOfState);
			else
				ruleOfState++;
		}
	}
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

	deleteSimulator();
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

void SimulatorManager::exportConfig(std::string path) {
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

	std::ofstream exportFile(path);
	exportFile << std::setw(2) << config << std::endl;
}


void SimulatorManager::importConfig(std::string path) {
	std::ifstream importFile(path);
	nlohmann::json config;
	importFile >> config;

	Simulator* beforeSimulator(_simulator);
	uint beforeDimension(_dimension);
	uint beforeGridSize(_gridSize);
	std::vector<State*> beforeStates(_states);
	std::vector<Rule*> beforeRules(_rules);

	try {
		_simulator = nullptr;
		_states.clear();
		_rules.clear();

		for (nlohmann::json::const_iterator state = config["states"].begin(); state != config["states"].end(); state++)
			createNewState(state.value().at("name").get<std::string>(), state.value().at("color").get<std::string>());

		for (nlohmann::json::const_iterator rule = config["rules"].begin(); rule != config["rules"].end(); rule++) {
			std::vector<State*> states;

			for (nlohmann::json::const_iterator transition = rule.value().at("transition_states").begin(); transition != rule.value().at("transition_states").end(); transition++) {
				uint position = transition.value().get<uint>();
				if (position >= _states.size())
					throw SimulatorException("L'état n'existe pas !");

				states.push_back(_states[position]);
			}

			uint position = rule.value().at("state").get<uint>();
			if (position >= _states.size())
				throw SimulatorException("L'état n'existe pas !");

			createNewRule(states, _states[position]);
		}

		for (nlohmann::json::const_iterator state = config["states"].begin(); state != config["states"].end(); state++) {
			for (nlohmann::json::const_iterator transition = state.value().at("transition_rules").begin(); transition != state.value().at("transition_rules").end(); transition++) {
				uint position = transition.value().get<uint>();
				if (position >= _rules.size())
					throw SimulatorException("La règle n'existe pas !");

				_states[state - config["states"].begin()]->addANewRule(_rules[position]);
			}
		}

		setDimension(config["simulator"]["dimension"].get<uint>());
		setGridSize(config["simulator"]["grid_size"].get<uint>());

		createSimulator();

		if (config["simulator"]["states"].size() != _simulator->getCellsNbr())
			throw SimulatorException("Les états de la simulation ne correspondent pas à la grille donnée");

		for (nlohmann::json::const_iterator state = config["simulator"]["states"].begin(); state != config["simulator"]["states"].end(); state++) {
			uint position = state.value().get<uint>();
			if (position >= _states.size())
				throw SimulatorException("L'état n'existe pas !");

			_simulator->setCell(_states[position], state - config["simulator"]["states"].begin());
		}

		delete beforeSimulator;
	} catch (SimulatorException e) {
		_simulator = beforeSimulator;
		_dimension = beforeDimension;
		_gridSize = beforeGridSize;
		_states = beforeStates;
		_rules = beforeRules;

		throw e;
	} catch (...) {
		_simulator = beforeSimulator;
		_dimension = beforeDimension;
		_gridSize = beforeGridSize;
		_states = beforeStates;
		_rules = beforeRules;

		throw SimulatorException("Le fichier json n'est pas valide");
	}
}
