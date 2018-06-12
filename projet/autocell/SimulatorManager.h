
#ifndef __SIMULATOR_MANAGER_H_DEFINE__
#define __SIMULATOR_MANAGER_H_DEFINE__

#include <vector>

#include "Simulator.h"
#include "State.h"

using uint = unsigned int;
using namespace std;

class SimulatorManager {
	private:
		vector<Simulator> _simulators;

		// Singleton
		static SimulatorManager* _instance;
		SimulatorManager();
		~SimulatorManager();
	public:
		// Singleton
		static SimulatorManager* getManager() {
			if (!_instance)
				_instance = new SimulatorManager();
			return _instance;
		}
		static void freeManager() {
			delete _instance;
		}

		// Accesseurs
//		Simulator* createSimulator();
//		 vector<string> listSimulator();

};

#endif
