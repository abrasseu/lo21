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

	public:
		// Singleton
		static SimulatorManager* getManager() {
			if (!(_instance))
				_instance = new SimulatorManager();
			return _instance;
		}
		static void freeManager() {
			if (_instance)
				delete _instance;
			_instance = 0;
		}



		// Getters
		State* getState(uint position);
		vector<State*>::const_iterator getFirstState() const { return _states.begin(); }
		vector<State*>::const_iterator getLastState() const { return _states.end(); }

		Rule* getRule(uint position);
		vector<Rule*>::const_iterator getFirstRule() const { return _rules.begin(); }
		vector<Rule*>::const_iterator getLastRule() const { return _rules.end(); }

		// Setters
		State* createNewState(string name, string color);
		Rule* createNewRule(vector<State*> states, string endState);

		void removeState(State* state);
		void removeRule(Rule* rule);



		void exportConfig(string uri);
		void importConfig(string data);
};

#endif
