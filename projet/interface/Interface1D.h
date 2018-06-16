#ifndef INTERFACE1D_H
#define INTERFACE1D_H

#include "SimulatorInterface.h"
#include "../autocell/Simulator1D.h"
#include "../autocell/State.h"

class Interface1D : public SimulatorInterface
{
	Q_OBJECT
	protected:
		// === Buffer Controls
		QVBoxLayout* grid_buffer_length_controls;
		QHBoxLayout* grid_buffer_length_select;
		QHBoxLayout* grid_buffer_length_bts_layout;

		QLabel* grid_buffer_length_label;
		QSpinBox* grid_buffer_length_spin;
		QPushButton* grid_buffer_length_valid;
		QPushButton* grid_buffer_length_reset;

		bool changeCellEnabled;
		QTableWidget* initial_view = nullptr;
		QTableWidget* grid_view = nullptr;

		unsigned int buffer_size;
		void setGridBufferLength(QBoxLayout*);

        void redrawGrid(QBoxLayout*);
		void drawGrid(QTableWidget*, uint, uint);
		void changeGridCells();

		void blockAfterAutomateChosen();
		void blockAfterAutomateChanged();

	public:
        Interface1D(bool draw = false);

	private slots:
		void rotateCellState(QTableWidgetItem*);

		void step_simulation();
		void start_simulation();

		// To prevent selecting cells on grid_view
		void grid_view_clicked(QTableWidgetItem*);

		void grid_set_buf();
		void grid_reset_buf();
};

#endif // INTERFACE1D_H
