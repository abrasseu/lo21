#include "Interface2D.h"
#include <string>

/**
 * \brief Constructeur de l'interface 2D
 * \details Construit l'interface 2D en héritant de la classe \em SimulatorInterface et de son constructeur
 */
Interface2D::Interface2D(bool draw) : SimulatorInterface(2) {

	grid_size = 650;

    if (draw)
        redrawGrid(view_layout);
}


// ----------------------- Methods to implement -----------------------

/**
 * \brief Affiche l'interface de simulation: la grille
 * \details Construit et affiche l'interface de simulation, crée et affiche la grille
 * \param parent    layout prévu pour l'interface de simulation
 */
void Interface2D::redrawGrid(QBoxLayout* parent) {
    grid_dimension = SimulatorManager::getManager()->getGridSize();

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

/**
 * \brief Affiche l'interface de simulation: la grille
 * \details Construit et affiche l'interface de simulation, crée et affiche la grille
 * \param parent    layout prévu pour l'interface de simulation
 */
void Interface2D::changeGridCells() {
	QColor color = QColor();
	simulator = SimulatorManager::getManager()->getSimulator();
    Simulator2D* sim2d = dynamic_cast<Simulator2D*>(simulator);
	for (unsigned int i=0; i < grid_dimension; i++) {
		for (unsigned int j=0; j < grid_dimension; j++) {
			// Get and Set Color from each cell's state
            color.setNamedColor(QString::fromStdString(sim2d->getCell(i,j)->getColor()));
			grid_view->item(i,j)->setBackground(QBrush(color, Qt::SolidPattern));
		}
	}
}


// Slots
/**
 * \brief Change l'état de la cellule cliquée
 * \details Slot. Augmente d'un état la cellule cliquée
 * \param i     ligne de la cellule cliquée
 * \param j     colonne de la cellule cliquée
 */
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

/**
 * \brief Autorise les clics sur la grille
 * \details \a Slot. Autorise les clics une fois que les paramètres du simulateur sont choisies, on peut de nouveau modifier
 *          la grille
 */
void Interface2D::blockAfterAutomateChosen(){
	grid_view->setEnabled(true);
}

/**
 * \brief Empêche les clics sur la grille
 * \details \a Slot. Empêche les clics pendant que l'utilisateur choisit les paramètres
 */
void Interface2D::blockAfterAutomateChanged(){
	grid_view->setEnabled(false);
}
