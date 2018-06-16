#ifndef INTERFACE2D_H
#define INTERFACE2D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator2D.h"

class Interface2D : public SimulatorInterface
{
	Q_OBJECT
	protected:
		QTableWidget* grid_view = nullptr;
	public:

		Interface2D();
		void initSimulatorView(QBoxLayout*);
        void setInitialStates();
		void redrawGrid(QBoxLayout*);
		void changeGridCells();

        void blockAfterAutomateChosen();
        void blockAfterAutomateChanged();

	protected slots:
        void set_default_grid();
		void rotateCellState(int, int);
};

#endif // INTERFACE2D_H
