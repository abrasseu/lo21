#include "Interface1D.h"


void setRules(State** states) {
	// Si une cellule vivante est entourée d'au moins 2 cellules mortes, elle meurt à son tour
	std::vector<State*> forRule1({states[0], states[0]});
	Rule* rule1 = new Rule(states[0], forRule1);
	states[1]->addANewRule(rule1);

	// Si une cellule morte est entourée de 2 cellules vivantes, elle vit à son tour
	std::vector<State*> forRule2({states[1], states[1]});
	Rule* rule2 = new Rule(states[1], forRule2);
	states[0]->addANewRule(rule2);
}
Interface1D::Interface1D(): SimulatorInterface(1), buffer_size(10) {
	// Set state list
	setGridBufferLength(grid_dim_controls);
	possible_state_list = new State*[2];
	possible_state_number = 2;
	possible_state_list[0] = new State("Mort", "#fff");
	possible_state_list[1] = new State("Vivant", "#000");

    initial_state_selector->clear();
    initial_state_selector->addItem("Vide", QVariant(0));
    initial_state_selector->addItem("Au hasard", QVariant(1));
    initial_state_selector->addItem("Symétrique", QVariant(2));
    initial_state_selector->addItem("Etats croissant", QVariant(3));
    initial_state_selector->addItem("Etats décroissant", QVariant(4));

	setRules(possible_state_list);

//	simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
	initSimulatorView(view_layout);
}

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

void Interface1D::initSimulatorView(QBoxLayout* parent) {
	setInitialStates();
	redrawGrid(parent);
}

void Interface1D::redrawGrid(QBoxLayout* parent) {
    // Initialisation du simulateur avec la bonne taille
    if (simulator)
        delete simulator;
    simulator = new Simulator1D(possible_state_list, 2, grid_dimension);

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

void Interface1D::changeGridCells() {
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

void Interface1D::setInitialStates(){
	initial_states = new State*[grid_dimension];
	for (unsigned int i = 0; i < grid_dimension; i++)
        initial_states[i] = possible_state_list[0];
}



// === Grid Slots
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

void Interface1D::rotateCellState(QTableWidgetItem* it){
    it->setSelected(false);
    if (changeCellEnabled) {
        simulator->incrementState(it->column(), false);
        QColor color;
        color.setNamedColor(QString::fromStdString(simulator->getCell(it->column())->getColor()));
        initial_view->item(0, it->column())->setBackgroundColor(color);
    }
}


// === Buffer Slots
void Interface1D::grid_set_buf(){
	buffer_size = grid_buffer_length_spin->value();
    if (grid_view != nullptr)
        delete grid_view;
    grid_view = new QTableWidget(buffer_size, grid_dimension);
    view_layout->addWidget(grid_view);

    drawGrid(grid_view, buffer_size, grid_dimension);
}

void Interface1D::grid_reset_buf(){
	grid_buffer_length_spin->setValue(10);
	buffer_size = grid_buffer_length_spin->value();
    if (grid_view != nullptr)
        delete grid_view;
    grid_view = new QTableWidget(buffer_size, grid_dimension);
    view_layout->addWidget(grid_view);

    drawGrid(grid_view, buffer_size, grid_dimension);
}

void Interface1D::grid_view_clicked(QTableWidgetItem* it){
	it->setSelected(false);
}

void Interface1D::set_default_grid() {
    unsigned int combo_value = initial_state_selector->currentIndex();
//    QMessageBox::warning(this, "erreur", QString::number(combo_value));

    switch (combo_value){
        case 0 :
            if (simulator)
                delete simulator;
            simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
            simulator->generateStateCells();
            break;
        case 1 :
            if (simulator)
                delete simulator;
            simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
            simulator->generateRandomCells();
            break;
        case 2 :
            if (simulator)
                delete simulator;
            simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
            simulator->generateVerticalSymetricRandomCells();
            break;
        case 3 :
            if (simulator)
                delete simulator;
            simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
            simulator->generateAlternedCells();
            break;
        case 4 :
            if (simulator)
                delete simulator;
            simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
            simulator->generateDescAlternedCells();
            break;

    }
    changeGridCells();
}

void Interface1D::blockAfterChoosedAutomate(){
    // Disable left buttons

    grid_buffer_length_spin->setEnabled(false);
    grid_buffer_length_valid->setEnabled(false);
    grid_buffer_length_reset->setEnabled(false);

    initial_view->setEnabled(true);

}

void Interface1D::blockAfterChangedAutomate(){
    // Disable left buttons

    grid_buffer_length_spin->setEnabled(true);
    grid_buffer_length_valid->setEnabled(true);
    grid_buffer_length_reset->setEnabled(true);

    initial_view->setEnabled(false);


}
