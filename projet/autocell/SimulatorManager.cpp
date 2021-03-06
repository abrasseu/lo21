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
/**
 * \brief Implémente une grille de taille demandée
 * \param gridSize     taille de la grille à implémenter
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

/**
 * \brief Test si le simulateur existe
 * \return Renvoie un \em booléen pour indiquer si le simulateur existe
 */
bool SimulatorManager::simulatorExists() {
	return _simulator != nullptr;
}

/**
 * \brief Renvoie le simulateur instancié
 * \return Renvoie un \em pointeur sur le \em simulateur
 */
Simulator* SimulatorManager::getSimulator() {
	if (!simulatorExists())
		throw SimulatorException("Aucune simulation n'a été instanciée");
    else
        return _simulator;
}

/**
 * \brief Créer un simulateur de taille demandée
 * \param dimension     dimension de l'automate
 * \return Renvoie un \em pointeur sur le \em simulateur créé
 */
Simulator* SimulatorManager::createSimulator(uint dimension) {
	deleteSimulator();

	if (dimension == 0)
		dimension = _dimension;

	switch (dimension) {
		case 1:
			_simulator = new Simulator1D(_states.data(), _states.size(), _gridSize);
			break;
		case 2:
			_simulator = new Simulator2D(_states.data(), _states.size(), _gridSize);
			break;
		default:
			throw SimulatorException("Cette dimension de simulation n'est pas encore implémentée.");
	}

	_dimension = dimension;
	return _simulator;
}

/**
 * \brief Supprime le simulateur existant
 */
void SimulatorManager::deleteSimulator() {
	if (simulatorExists())
		delete _simulator;

	_simulator = nullptr;
}


/*
|--------------------------------------------------------------------------
|	States
|--------------------------------------------------------------------------
*/

/**
 * \brief Renvoie l'état à la position demandée
 * \param position  position de l'état
 * \return Renvoie un \em pointeur sur le \em état
 */
State* SimulatorManager::getState(uint position) {
	if (position >= _states.size())
		throw SimulatorException("L'état " + std::to_string(position) + " n'existe pas !");

	return _states[position];
}

/**
 * \brief Renvoie l'état avec le nom demandé
 * \param name  nom de l'état
 * \return Renvoie un \em pointeur sur le \em état
 */
State* SimulatorManager::getState(const std::string& name) {
	std::vector<State*>::iterator it = std::find_if(_states.begin(), _states.end(),
		[&name](State* state) { return state->getName() == name; });
	if (it == _states.end())
		throw SimulatorException("L'état n'existe pas");
	return (*it);
}

/**
 * \brief Crée un nouvel état avec les paramètres précisés
 * \param name  nom de l'état
 * \param color couleur de l'état à créer
 * \return Renvoie un \em pointeur sur l' \em état créé
 */
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

    if (simulatorExists())
        getSimulator()->setStates(_states.data(), _states.size());

	return state;
}

/**
 * \brief Supprime l'état demandé
 * \param state  pointeur sur l'état à supprimer
 */
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

    if (simulatorExists()) {
        getSimulator()->setStates(_states.data(), _states.size());

        for (uint i = 0; i < getSimulator()->getCellsNbr(); i++) {
            if (getSimulator()->getCell(i) == state)
                getSimulator()->setCell(_states[0], i);

            if (getSimulator()->getInitialCell(i) == state)
                getSimulator()->setInitialCell(_states[0], i);
        }
    }
}

/*
|--------------------------------------------------------------------------
|	Rules
|--------------------------------------------------------------------------
*/

/**
 * \brief Renvoie une règle
 * \param position  position de la règle
 * \return Renvoie un \em pointeur sur la \em règle
 */
Rule* SimulatorManager::getRule(uint position) {
	if (position >= _rules.size())
		throw SimulatorException("La règle " + std::to_string(position) + " n'existe pas !");

	return _rules[position];
}

/**
 * \brief Crée une nouvelle règle
 * \details L'état d'arrivée est l'état que deviendra l'état en question si la règle est respectée
 * \param states  vecteur d'état correspondant à la règle
 * \param endState  pointeur sur l'état d'arrivée de la règle
 * \return Renvoie un \em pointeur sur la \em règle
 */
Rule* SimulatorManager::createNewRule(std::vector<State*> states, State* endState) {
	_rules.push_back(new Rule(endState, states));

	return _rules.back();
}

/**
 * \brief Supprime la règle
 * \param rule  pointeur sur la règle à supprimer
 */
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

/**
 * \brief Supprime l'objet
 * \param object  pointeur sur l'objet à supprimer
 * \param container pointeur sur un vecteur d'objets
 */
template<class T>
void SimulatorManager::removeObject(T* object, std::vector<T*>* container) {
	typename std::vector<T*>::const_iterator it = find(container->begin(), container->end(), object);

	if (it == container->end())
		throw SimulatorException("L'objet n'existe pas");

	container->erase(it);
	delete object;
}

/**
 * \brief Cherche l'objet souhaité
 * \param object  pointeur sur l'objet à chercher
 * \param conainer pointuer sur le vecteur d'objets où chercher
 * \return Renvoie la position de l'objet
 */
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
/**
 * \brief Exporte la configuration à sauvegarder
 * \param path chemin du fichier à exporter
 */
void SimulatorManager::exportConfig(std::string path) {
	nlohmann::json states = nlohmann::json::array();
	nlohmann::json rules = nlohmann::json::array();

	// Première étape: on liste tous nos paramètres
	nlohmann::json simulator = {
	  {"dimension", _dimension},
	  {"grid_size", _gridSize},
	  {"initial_states", nlohmann::json::array()},
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

	// Cinquième étape: on liste l'état actuel et initial de notre simulation
	for (uint i = 0; i < getSimulator()->getCellsNbr(); i++)
		simulator["initial_states"] += findObject<State>(getSimulator()->getInitialCell(i), &_states);

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


/**
 * \brief Importe la configuration
 * \param path chemin du fichier à importer
 */
void SimulatorManager::importConfig(std::string path) {
    Simulator* beforeSimulator(_simulator);
    uint beforeDimension(_dimension);
    uint beforeGridSize(_gridSize);
    std::vector<State*> beforeStates(_states);
    std::vector<Rule*> beforeRules(_rules);

	try {
        std::ifstream importFile(path);
        nlohmann::json config;
        importFile >> config;

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

		for (nlohmann::json::const_iterator state = config["simulator"]["initial_states"].begin(); state != config["simulator"]["initial_states"].end(); state++) {
			uint position = state.value().get<uint>();
			if (position >= _states.size())
				throw SimulatorException("L'état n'existe pas !");

			_simulator->setInitialCell(_states[position], state - config["simulator"]["initial_states"].begin());
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

        throw SimulatorException("Le fichier n'est pas valide");
	}
}
