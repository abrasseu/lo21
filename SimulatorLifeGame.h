/**
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_LIFE_GAME_H_DEFINE__
#define __SIMULATOR_LIFE_GAME_H_DEFINE__

#include <iostream>
#include "Simulator2D.h"
#include "Cell.h"
#include "State.h"

#define uint unsigned int

class SimulatorLifeGame : public Simulator2D {
protected:
public:
    // Constructeurs
    SimulatorLifeGame(uint cellsSize);
};

#endif
