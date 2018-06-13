#include "Interface2D.h"

// TODO : automate_dimension
Interface2D::Interface2D() : SimulatorInterface(automate_dimension) {
	// Set state list
	possible_state_list = new State*[2];
	possible_state_list[0] = new State("Mort", "#000000");
	possible_state_list[1] = new State("Vivant", "#ffffff");

//	simulator = new Simulator2D();
	resetSimulatorView(view_layout);
}

// Method to implement
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

	// Non éditable
	grid_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	for (unsigned int i=0; i < grid_dimension; i++){
		grid_view->setColumnWidth(i, grid_size/grid_dimension);
		grid_view->setRowHeight(i, grid_size/grid_dimension);
		for (unsigned int j=0; j < grid_dimension; j++)
			grid_view->setItem(j, i, new QTableWidgetItem(""));
	}

//	QObject::connect(grid_view, SIGNAL(cellClicked(int,int)), this, SLOT(rotateCellState(int, int)));

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
	/*
	if (changeCellEnabled){
		if (etats->item(i,j)->backgroundColor()== Qt::black)
			etats->item(i,j)->setBackgroundColor(Qt::white);
		else
			etats->item(i,j)->setBackgroundColor(Qt::black);
	}
	*/
}
