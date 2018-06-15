/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#include "SimulatorManager.h"
#include "SimulatorException.h"
#include "Simulator.h"

using uint = unsigned int;

// Singleton
SimulatorManager* SimulatorManager::_instance = new SimulatorManager;

Rule* SimulatorManager::getRule(uint position) {
	if (position >= _rules.size())
		throw new SimulatorException("La règle " + std::to_string(position) + " n'existe pas !");

	return &_rules[position];
}
