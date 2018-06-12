#include "SimulatorManager.h"

// Singleton
SimulatorManager* SimulatorManager::_instance = nullptr;

// Constructeurs et Destructeurs
SimulatorManager::SimulatorManager() {
	_simulators = vector<Simulator>();
}
