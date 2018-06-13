#include "Interface2D.h"
#include <string>

// TODO : automate_dimension
Interface2D::Interface2D() : SimulatorInterface(automate_dimension) {
	// Set state list
	possible_state_list = new State*[3];
	possible_state_list[0] = new State("Mort", "#000000");
	possible_state_list[1] = new State("Vivant", "#ffffff");
	possible_state_list[2] = new State("Zombi", "#ff0000");

	simulator = new Simulator2D(possible_state_list, 3, grid_dimension*grid_dimension);
	resetSimulatorView(view_layout);
}


// ----------------------- Method to implement -----------------------

void Interface2D::setSimulatorView(QBoxLayout* parent) {
//	etats = new QTableWidget;
	resetSimulatorView(parent);
}

void Interface2D::resetSimulatorView(QBoxLayout* parent) {
	setInitialStates();
	if (grid_view != nullptr)
		delete grid_view;
	grid_view = new QTableWidget(grid_dimension, grid_dimension);
	parent->addWidget(grid_view);

	grid_view->setFixedSize(grid_size + grid_dimension/3, grid_size + grid_dimension/3);
	grid_view->horizontalHeader()->setVisible(false);
	grid_view->verticalHeader()->setVisible(false);
	grid_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid_view->setEditTriggers(QAbstractItemView::NoEditTriggers);		// Non éditable

	for (unsigned int i=0; i < grid_dimension; i++){
		grid_view->setColumnWidth(i, grid_size/grid_dimension);
		grid_view->setRowHeight(i, grid_size/grid_dimension);
		for (unsigned int j=0; j < grid_dimension; j++)
			grid_view->setItem(j, i, new QTableWidgetItem(""));
	}

	connect(grid_view, SIGNAL(cellClicked(int,int)), this, SLOT(rotateCellState(int, int)));

//	etats->item(i,j)->setBackgroundColor(Qt::white);
}

void Interface2D::setInitialStates() {
	initial_states = new State*[grid_dimension];
	// TODO
	for (unsigned int i = 0; i < grid_dimension; i++)
		initial_states[i] = possible_state_list[0];
}


// Slot

void Interface2D::rotateCellState(int i, int j) {
	if (changeCellEnabled) {
        simulator->incrementState(i, j, false);
        std::string color = simulator->getCell(i,j)->getColor();
        uint intcolor[3];
        for (uint i = 0; i < 3; i++)
            intcolor[i] = color[2*i + 1]+color[2*i + 2] - '0' - '0';
        grid_view->item(i,j)->setBackground(QColor::fromRgb(intcolor[0], intcolor[1], intcolor[2]));
	}
}
