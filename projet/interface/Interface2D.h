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

		void blockAfterChoosedAutomate();
		void blockAfterChangedAutomate();

	public:
		Interface2D();

	protected slots:
		void rotateCellState(int, int);
};

#endif // INTERFACE2D_H
