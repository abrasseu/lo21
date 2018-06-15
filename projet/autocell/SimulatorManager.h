/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_MANAGER_H_DEFINE__
#define __SIMULATOR_MANAGER_H_DEFINE__

#include <vector>

#include "SimulatorException.h"
#include "Simulator.h"
#include "Simulator1D.h"
#include "Simulator2D.h"
#include "State.h"
#include "Rule.h"

#include <iostream>
using namespace std;
using uint = unsigned int;

class SimulatorManager {
	private:
		Simulator* _simulator;
		vector<State*> _states;
		vector<Rule*> _rules;

		// Singleton
		static SimulatorManager* _instance;
		SimulatorManager() {
			_simulator = 0;
		}
		~SimulatorManager() {
			if (_simulator)
				delete _simulator;
			_simulator = 0;
		}

		// Template Methods
		template<class T>
		void removeObject(T* object, vector<T*> container);

	public:
		// Singleton
		static SimulatorManager* getManager(bool throwException = true) {
			if (!(_instance))
				_instance = new SimulatorManager();
			return _instance;
		}
		static void freeManager() {
			if (_instance)
				delete _instance;
			_instance = 0;
		}

		// Simulator
		Simulator* getSimulator(bool throwException = true);
		Simulator* createSimulator(uint dimension, uint cellsSize, vector<State*>* states = nullptr);
		void deleteSimulator();

		// States
		State* getState(uint position);
		vector<State*>::const_iterator getFirstState() const { return _states.begin(); }
		vector<State*>::const_iterator getLastState() const { return _states.end(); }
		State* createNewState(string name, string color);
		void removeState(State* state);

		// Rules
		Rule* getRule(uint position);
		vector<Rule*>::const_iterator getFirstRule() const { return _rules.begin(); }
		vector<Rule*>::const_iterator getLastRule() const { return _rules.end(); }
		Rule* createNewRule(vector<State*> states, string endState);
		void removeRule(Rule* rule);

		// Save & Load
		void exportConfig(string uri);
		void importConfig(string uri);
};

#endif
