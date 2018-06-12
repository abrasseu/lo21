#ifndef INTERFACE1D_H
#define INTERFACE1D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator1D.h"
#include "../autocell/State.h"

class Interface1D : public SimulatorInterface
{
    protected:
        const short unsigned int automate_dimension;
	public:
        Interface1D();
        void setSimulatorView(QBoxLayout* parent);
        void resetSimulatorView();
        void setInitialStates();
};

#endif // INTERFACE1D_H
