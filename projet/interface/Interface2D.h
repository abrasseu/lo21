#ifndef INTERFACE2D_H
#define INTERFACE2D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator2D.h"

class Interface2D : public SimulatorInterface
{
	Q_OBJECT
	protected:
		QTableWidget* grid_view = nullptr;

        void redrawGrid(QBoxLayout*);
        void changeGridCells();

        void blockAfterAutomateChosen();
        void blockAfterAutomateChanged();

    public:
        Interface2D(bool draw = false);

	protected slots:
		void rotateCellState(int, int);
};

#endif // INTERFACE2D_H
