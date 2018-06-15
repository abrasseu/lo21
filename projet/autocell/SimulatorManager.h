/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_MANAGER_H_DEFINE__
#define __SIMULATOR_MANAGER_H_DEFINE__

#include <vector>

#include "Simulator.h"
#include "SimulatorException.h"
#include "State.h"
#include "Rule.h"

using uint = unsigned int;

class SimulatorManager {
	private:
		Simulator* _simulator;
		std::vector<State*> _states;
		std::vector<Rule*> _rules;

		// Singleton
		static SimulatorManager* _instance;
		SimulatorManager() {};
		~SimulatorManager() noexcept { delete _simulator; delete _instance; };
	public:
		// Singleton
		static SimulatorManager* getManager() {	return _instance; };

		// Getters
		State* getState(uint position);
		std::vector<State*>::const_iterator getFirstState() const { return _states.begin(); }
		std::vector<State*>::const_iterator getLastState() const { return _states.end(); }

		Rule* getRule(uint position);
		std::vector<Rule*>::const_iterator getFirstRule() const { return _rules.begin(); }
		std::vector<Rule*>::const_iterator getLastRule() const { return _rules.end(); }

		// Setters
		State* createNewState(std::string name, std::string color);
		Rule* createNewRule(std::vector states, std::string endState);

		void removeState(State* state);
		void removeRule(Rule* rule);



		void export(std::string uri);
		void import(std::string data);
};

#endif
