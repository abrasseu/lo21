/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_MANAGER_H_DEFINE__
#define __SIMULATOR_MANAGER_H_DEFINE__

#include <vector>
#include <QMessageBox>

#include "SimulatorException.h"
#include "Simulator.h"
#include "Simulator1D.h"
#include "Simulator2D.h"
#include "State.h"
#include "Rule.h"

#include <iostream>
using uint = unsigned int;

class SimulatorManager {
	private:
		Simulator* _simulator;
		uint _gridSize = 0;
		std::vector<State*> _states;
		std::vector<Rule*> _rules;

		// Singleton
		static SimulatorManager* _instance;
		SimulatorManager() {
			_simulator = nullptr;
		}
		~SimulatorManager() {
			if (_simulator != nullptr)
				delete _simulator;
		}

		// Template Methods
		template<class T>
		void removeObject(T* object, std::vector<T*>* container);

	public:
		// Singleton
		static SimulatorManager* getManager() { return _instance; }

		// Simulator
		Simulator* getSimulator();
		Simulator* createSimulator(uint dimension);
		void deleteSimulator();

		// Grid size
		uint getGridSize() { return _gridSize; }
		void setGridSize(uint gridSize) { _gridSize = gridSize; }

		// States
		State* getState(uint position);
		State* getState(const std::string& name);
		std::vector<State*>::const_iterator getFirstState() const { return _states.begin(); }
		std::vector<State*>::const_iterator getLastState() const { return _states.end(); }
		State* createNewState(std::string name, std::string color);
		void removeState(State* state);

		// Rules
		Rule* getRule(uint position);
		std::vector<Rule*>::const_iterator getFirstRule() const { return _rules.begin(); }
		std::vector<Rule*>::const_iterator getLastRule() const { return _rules.end(); }
		Rule* createNewRule(std::vector<State*> states, State* endState);
		void removeRule(Rule* rule);

		// Save & Load
		void exportConfig(std::string uri);
		void importConfig(std::string uri);
};

#endif
