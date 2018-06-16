/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_EXCEPTION_H_DEFINE__
#define __SIMULATOR_EXCEPTION_H_DEFINE__

#include <iostream>
#include <string>

class SimulatorException {
	private:
		const std::string& _info;
	public:
        SimulatorException(const std::string& s) : _info(s) { }
		const std::string& what() const { return _info; }
};

#endif
