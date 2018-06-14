#ifndef INTERFACE2D_H
#define INTERFACE2D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator2D.h"

class Interface2D : public SimulatorInterface
{
	Q_OBJECT
	protected:
		const short unsigned int automate_dimension = 2;
		QTableWidget* grid_view = nullptr;
	public:

		Interface2D();
		void initSimulatorView(QBoxLayout*);
		void setInitialStates();
		void redrawGrid(QBoxLayout*);
		void changeGridCells();

	protected slots:
		void rotateCellState(int, int);
};

#endif // INTERFACE2D_H
