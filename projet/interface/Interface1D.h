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

        bool changeCellEnabled = true;
        const short unsigned int automate_dimension = 1;
        QTableWidget* initial_view = nullptr;

        QTableWidget* grid_view = nullptr;

        unsigned int buffer_size;

	public:
        Interface1D();
        void setGridBufferLength(QBoxLayout*);
        void initSimulatorView(QBoxLayout*);
        void setInitialStates();

        void drawGrid(QTableWidget*, uint, uint);
        void drawGrid();
        void changeGridCells();

    private slots:
        void rotateCellState(QTableWidgetItem*);

        void grid_set_buf();
        void grid_reset_buf();
};

#endif // INTERFACE1D_H
