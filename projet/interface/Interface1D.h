#ifndef INTERFACE1D_H
#define INTERFACE1D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator1D.h"
#include "../autocell/State.h"

class Interface1D : public SimulatorInterface
{
    Q_OBJECT
    protected:
        bool changeCellEnabled = true;
        const short unsigned int automate_dimension = 1;
        QTableWidget* grid_view = nullptr;
	public:
        Interface1D();
        void setSimulatorView(QBoxLayout*);
        void resetSimulatorView(QBoxLayout*);
        void setInitialStates();

    private slots:
        void rotateCellState(int, int);
};

#endif // INTERFACE1D_H
