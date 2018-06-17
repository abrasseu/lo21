#include "Interface1D.h"

/**
 * \brief Constructeur de l'interface 1D
 * \details Construit l'interface 1D en héritant de la classe \em SimulatorInterface et de son constructeur
 */
Interface1D::Interface1D(bool draw): SimulatorInterface(1), buffer_size(10) {
	// Set state list
	setGridBufferLength(grid_dim_controls);

    if (draw)
        redrawGrid(view_layout);
}

/**
 * \brief Affiche l'interface concernant le choix de la taille du buffer
 * \details Construit l'interface concernant le choix de la taille du buffer, avec les boutons et autres widgets
 */
void Interface1D::setGridBufferLength(QBoxLayout* parent){
	grid_buffer_length_controls = new QVBoxLayout;
	parent->addLayout(grid_buffer_length_controls);
	grid_buffer_length_select = new QHBoxLayout;
	grid_buffer_length_bts_layout = new QHBoxLayout;
	grid_buffer_length_controls->addLayout(grid_buffer_length_select);
	grid_buffer_length_controls->addLayout(grid_buffer_length_bts_layout);

	grid_buffer_length_label = new QLabel("Choisissez le nombre de buffers: ");
	grid_buffer_length_select->addWidget(grid_buffer_length_label);
	grid_buffer_length_spin = new QSpinBox;
	grid_buffer_length_spin->setRange(0,100);
	grid_buffer_length_spin->setValue(10);
	grid_buffer_length_spin->setAlignment(Qt::AlignHCenter);
	grid_buffer_length_select->addWidget(grid_buffer_length_spin);

	grid_buffer_length_valid = new QPushButton("Valider");
	grid_buffer_length_reset = new QPushButton("Reset");
	grid_buffer_length_bts_layout->addWidget(grid_buffer_length_valid);
	grid_buffer_length_bts_layout->addWidget(grid_buffer_length_reset);

	QObject::connect(grid_buffer_length_valid, SIGNAL(clicked()), this, SLOT(grid_set_buf()));
	QObject::connect(grid_buffer_length_reset, SIGNAL(clicked()), this, SLOT(grid_reset_buf()));
}

/**
 * \brief Génère les deux grilles d'affichage
 * \details Supprime et construit les deux grilles d'affichage, avec la ligne initiale et la grille contenant les états successifs
 *          au sein du layout parent
 * \param parent    layout contenant tous les widgets
 */
void Interface1D::redrawGrid(QBoxLayout* parent) {
	simulator = SimulatorManager::getManager()->getSimulator();
    grid_dimension = simulator->getCellsSize();
    grid_reset_dim();

//    QMessageBox::warning(this, "taille", QString::number(grid_dimension));
	// Initialisation de la ligne de départ
	if (initial_view != nullptr)
		delete initial_view;
	initial_view = new QTableWidget(1, grid_dimension);
	parent->addWidget(initial_view);

	drawGrid(initial_view, 1, grid_dimension);

	QColor color = QColor();
	for (uint i = 0; i < grid_dimension; i++) {
		color.setNamedColor(QString::fromStdString(simulator->getCell(i)->getColor()));
		initial_view->item(0, i)->setBackground(QBrush(color, Qt::SolidPattern));
	}
	QObject::connect(initial_view, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(rotateCellState(QTableWidgetItem*)));

	// Initialisation de la grille d'affichage
	if (grid_view != nullptr)
		delete grid_view;
	grid_view = new QTableWidget(buffer_size, grid_dimension);
	parent->addWidget(grid_view);

	drawGrid(grid_view, buffer_size, grid_dimension);
	changeGridCells();

	QObject::connect(grid_view, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(grid_view_clicked(QTableWidgetItem*)));
}

/**
 * \brief Actualise une grille d'affichage avec les tailles prescrites
 * \details Permet d'actualiser une grille avec les paramètres, les tailles sont prises en compte en fonction de la dimension
 *          de l'automate
 * \param grid      Grille passée en paramètre pour être actualisée
 * \param nbRow     Nombre de lignes de la grille à manipuler
 * \param nbColumn  Nombre de colonnes de la grille à manipuler
 */
void Interface1D::drawGrid(QTableWidget* grid, uint nbRow, uint nbColumn) {
	// nbRow if one line table
	if (nbRow == 1)
		grid->setFixedSize(grid_size, grid_size/nbColumn);
	else
		grid->setFixedSize(grid_size, grid_size);
	// Config grid
	grid->horizontalHeader()->setVisible(false);
	grid->verticalHeader()->setVisible(false);
	grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	grid->setSelectionMode(QAbstractItemView::NoSelection);		// Non sélectionnable
	grid->setEditTriggers(QAbstractItemView::NoEditTriggers);	// Non éditable

	// Set size of cells
	for (unsigned int j = 0; j < nbColumn; j++)
		grid->setColumnWidth(j, grid_size/nbColumn);
	for (unsigned int i = 0; i < nbRow; i++) {
		grid->setRowHeight(i, grid_size/nbRow);
		for (uint j = 0; j < nbColumn; j++)
			grid->setItem(i, j, new QTableWidgetItem(""));
	}
}

/**
 * \brief Actualise les cellules de la grille en fonction des états du simulateur
 * \details Change l'état des cellules en modifiant leur couleur en fonction du simulateur.
 *          Vérifie la taille du buffer déjà utilisé pour réaliser l'affichage
 */
void Interface1D::changeGridCells() {
	simulator = SimulatorManager::getManager()->getSimulator();
	const uint currentGeneration = simulator->getGeneration();
	if (currentGeneration > buffer_size)
		for (uint i = 0; i < buffer_size - 1; i++)
			for (uint j = 0; j < grid_dimension; j++)
				grid_view->item(i, j)->setBackgroundColor(grid_view->item(i + 1, j)->backgroundColor());

	if (currentGeneration > 0) {
		uint lastLine;
		if (currentGeneration < buffer_size)
			lastLine = currentGeneration - 1;
		else
			lastLine = buffer_size - 1;
		QColor color = QColor();
		for (uint i = 0; i < grid_dimension; i++){
			color.setNamedColor(QString::fromStdString(simulator->getCell(i)->getColor()));
			grid_view->item(lastLine, i)->setBackgroundColor(color);
		}
	}
	else{
		QColor color = QColor();
		for (uint i = 0; i < grid_dimension; i++){
			color.setNamedColor(QString::fromStdString(simulator->getCell(i)->getColor()));
			initial_view->item(0, i)->setBackgroundColor(color);
		}
	}
}


// === Grid Slots
/**
 * \brief Avance la simulation d'une transition
 * \details \a Slot. Avance la simulation et le simulateur d'une transition
 */
void Interface1D::step_simulation() {
	// Disable dimension changes
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	// Disable initial state changes
	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);
	changeCellEnabled = false;

	// Step simulation
	iterate_simulation();
}
/**
 * \brief Lance la simulation
 * \details \a Slot. Lance la simulation avec la vitesse sélectionnée
 */
void Interface1D::start_simulation() {
	// Disable start/step/reset/speed changes
	sim_start_bt->setEnabled(false);
	sim_step_bt->setEnabled(false);
	sim_reset_bt->setEnabled(false);
	speed_selector->setEnabled(true);
	// Disable dimension changes
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	// Disable initial state changes
	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);

	changeCellEnabled = false;

	// Run simulation until it stage
	sim_is_running = true;
	if (speed_selector->value() > 0)
		sim_timer->start(1000 * speed_selector->value());
	else
		sim_timer->start(10);
	QObject::connect(speed_selector, SIGNAL(valueChanged(double)), this, SLOT(speedSelectorChangedValue(double)));
}

/**
 * \brief Change l'état de la cellule cliquée
 * \details \a Slot. Change l'état de la cellule en modifiant sa couleur en augmentant son état
 * \param it    cellule cliquée
 */
void Interface1D::rotateCellState(QTableWidgetItem* it){
	simulator = SimulatorManager::getManager()->getSimulator();
	it->setSelected(false);
	if (changeCellEnabled) {
        simulator->incrementState(it->column());
		QColor color;
		color.setNamedColor(QString::fromStdString(simulator->getCell(it->column())->getColor()));
		initial_view->item(0, it->column())->setBackgroundColor(color);
	}
}


// === Buffer Slots
/**
 * \brief Modifie la taille du buffer
 * \details \a Slot. Intègre la taille du buffer qui a été modifiée
 */
void Interface1D::grid_set_buf(){
	buffer_size = grid_buffer_length_spin->value();
	if (grid_view != nullptr)
		delete grid_view;
	grid_view = new QTableWidget(buffer_size, grid_dimension);
	view_layout->addWidget(grid_view);

	drawGrid(grid_view, buffer_size, grid_dimension);
}

/**
 * \brief Remet la taille du buffer à la valeur initiale
 * \details \a Slot. Remet la taille du buffer à sa valeur initiale
 */
void Interface1D::grid_reset_buf(){
	grid_buffer_length_spin->setValue(10);
	buffer_size = grid_buffer_length_spin->value();
	if (grid_view != nullptr)
		delete grid_view;
	grid_view = new QTableWidget(buffer_size, grid_dimension);
	view_layout->addWidget(grid_view);

	drawGrid(grid_view, buffer_size, grid_dimension);
}

/**
 * \brief Empêche que la cellule cliquée devienne sélectionnée
 * \details \a Slot. Empêche que la cellule qui a été cliquée devienne bleue lors de la sélection
 * \param it    cellule cliquée
 */
void Interface1D::grid_view_clicked(QTableWidgetItem* it){
	it->setSelected(false);
}

/**
 * \brief Bloque des boutons lorsque les paramètres de l'automate ont été choisie
 * \details \a Slot. Bloque les boutons de la partie gauche lorsque les états et les dimensions de l'automate ont été choisis
 */
void Interface1D::blockAfterAutomateChosen(){
	// Disable left buttons

	grid_buffer_length_spin->setEnabled(false);
	grid_buffer_length_valid->setEnabled(false);
	grid_buffer_length_reset->setEnabled(false);

	initial_view->setEnabled(true);

}

/**
 * \brief Bloque des boutons lorsqu'on change les paramètres de l'automate
 * \details \a Slot. Bloque les boutons de la partie droite quand l'utilisateur veut changer les états et dimensions de l'automate
 */
void Interface1D::blockAfterAutomateChanged(){
	// Disable left buttons

	grid_buffer_length_spin->setEnabled(true);
	grid_buffer_length_valid->setEnabled(true);
	grid_buffer_length_reset->setEnabled(true);

	initial_view->setEnabled(false);


}
