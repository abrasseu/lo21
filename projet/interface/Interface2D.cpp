#include "Interface2D.h"
#include <string>

Interface2D::Interface2D(bool draw) : SimulatorInterface(2) {

	grid_size = 650;

    if (draw)
        redrawGrid(view_layout);
}


// ----------------------- Methods to implement -----------------------

void Interface2D::redrawGrid(QBoxLayout* parent) {
	// Delete and recreate grid if exists
	if (grid_view != nullptr)
		delete grid_view;
	grid_view = new QTableWidget(grid_dimension, grid_dimension);
	parent->addWidget(grid_view);

	// Config grid
	grid_view->setFixedSize(grid_size + grid_dimension/3, grid_size + grid_dimension/3);
	grid_view->horizontalHeader()->setVisible(false);
	grid_view->verticalHeader()->setVisible(false);
	grid_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid_view->setEditTriggers(QAbstractItemView::NoEditTriggers);		// Non éditable
	grid_view->setSelectionMode(QAbstractItemView::NoSelection);		// Non sélectionnable

	for (unsigned int i=0; i < grid_dimension; i++) {
		grid_view->setColumnWidth(i, grid_size/grid_dimension);
		grid_view->setRowHeight(i, grid_size/grid_dimension);
		for (unsigned int j=0; j < grid_dimension; j++)
			grid_view->setItem(i, j, new QTableWidgetItem());
	}
	connect(grid_view, SIGNAL(cellClicked(int,int)), this, SLOT(rotateCellState(int, int)));

	changeGridCells();
}

void Interface2D::changeGridCells() {
	QColor color = QColor();
	simulator = SimulatorManager::getManager()->getSimulator();
	Simulator2D* sim2d = static_cast<Simulator2D*>(simulator);
	for (unsigned int i=0; i < grid_dimension; i++) {
		for (unsigned int j=0; j < grid_dimension; j++) {
			// Get and Set Color from each cell's state
			color.setNamedColor(QString::fromStdString(sim2d->getCell(i,j)->getColor()));
			grid_view->item(i,j)->setBackground(QBrush(color, Qt::SolidPattern));
		}
	}
}


// Slot

void Interface2D::rotateCellState(int i, int j) {
	if (changeCellEnabled) {
		simulator = SimulatorManager::getManager()->getSimulator();
		Simulator2D* sim2d = static_cast<Simulator2D*>(simulator);
        sim2d->incrementState(i, j);
		QColor color;
		color.setNamedColor(QString::fromStdString(sim2d->getCell(i,j)->getColor()));
		grid_view->item(i,j)->setBackground(color);
	}
}


void Interface2D::blockAfterChoosedAutomate(){
	grid_view->setEnabled(true);
}
void Interface2D::blockAfterChangedAutomate(){
	grid_view->setEnabled(false);
}
