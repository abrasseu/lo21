#include "Interface2D.h"
#include <string>


void setRules2(State** states) {
	// Si une cellule vivante est entourée d'au moins 7 cellules mortes, elle meurt à son tour
	std::vector<State*> forRule1({states[0], states[0], states[0], states[0], states[0], states[0], states[0]});
	Rule* rule1 = new Rule(states[0], forRule1);
	states[1]->addANewRule(rule1);

	// Si une cellule morte est entourée de 3 cellules vivantes, elle vit à son tour
	std::vector<State*> forRule2({states[1], states[1], states[1], states[0], states[0], states[0], states[0], states[0]});
	Rule* rule2 = new Rule(states[1], forRule2);
	states[0]->addANewRule(rule2);

	// Si une cellule vivante est entourée d'au moins 4 cellules vivantes, elle meurt par étouffement
	std::vector<State*> forRule3({states[1], states[1], states[1], states[1]});
	Rule* rule3 = new Rule(states[0], forRule3);
	states[1]->addANewRule(rule3);
}


Interface2D::Interface2D() : SimulatorInterface(2) {
	// Set state list
	possible_state_list = new State*[3];
	possible_state_number = 3;
	possible_state_list[0] = new State("Mort", "#fff");
	possible_state_list[1] = new State("Vivant", "#000");
	possible_state_list[2] = new State("Zombi", "#ff0000");

    // Ajout du bouton du choix des paramètres du jeu de la vie
    set_transition_game_life = new QPushButton("Jeu de la vie");
    transition_controls->addWidget(set_transition_game_life);

    initial_state_selector->addItem("Vide", QVariant(0));
    initial_state_selector->addItem("Au hasard", QVariant(1));
    initial_state_selector->addItem("Symétrique vertical", QVariant(2));
    initial_state_selector->addItem("Symétrique horizontal", QVariant(3));
    initial_state_selector->addItem("Etats croissant", QVariant(4));
    initial_state_selector->addItem("Etats décroissant", QVariant(5));

	setRules2(possible_state_list);
	grid_size = 650;

//	simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
	initSimulatorView(view_layout);
}


// ----------------------- Methods to implement -----------------------

void Interface2D::initSimulatorView(QBoxLayout* parent) {
	setInitialStates();
	redrawGrid(parent);
}

void Interface2D::redrawGrid(QBoxLayout* parent) {
	// Config Simulator Cells
	if (simulator)
		delete simulator;
	simulator = new Simulator2D(possible_state_list, possible_state_number, grid_dimension);
	simulator->generateStateCells();

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
	Simulator2D* sim2d = static_cast<Simulator2D*>(this->simulator);
	for (unsigned int i=0; i < grid_dimension; i++) {
		for (unsigned int j=0; j < grid_dimension; j++) {
			// Get and Set Color from each cell's state
			color.setNamedColor(QString::fromStdString(sim2d->getCell(i,j)->getColor()));
			grid_view->item(i,j)->setBackground(QBrush(color, Qt::SolidPattern));
		}
	}
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
		Simulator2D* sim2d = static_cast<Simulator2D*>(this->simulator);
		sim2d->incrementState(i, j, false);
		QColor color;
		color.setNamedColor(QString::fromStdString(sim2d->getCell(i,j)->getColor()));
		grid_view->item(i,j)->setBackground(color);
	}
}


void Interface2D::set_default_grid() {
    unsigned int combo_value = initial_state_selector->currentIndex();
//    QMessageBox::warning(this, "erreur", QString::number(combo_value));

    switch (combo_value){
        case 0 :
            if (simulator)
                delete simulator;
            simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
            simulator->generateStateCells();
            break;
        case 1 :
            if (simulator)
                delete simulator;
            simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
            simulator->generateRandomCells();
            break;
        case 2 :
            if (simulator)
                delete simulator;
            simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
            simulator->generateVerticalSymetricRandomCells();
            break;
        case 3 :
            if (simulator)
                delete simulator;
            simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
            simulator->generateAlternedCells();
            break;
        case 4 :
            if (simulator)
                delete simulator;
            simulator = new Simulator2D(possible_state_list, 3, grid_dimension);
            simulator->generateDescAlternedCells();
            break;

    }
    changeGridCells();
}

void Interface2D::blockAfterAutomateChosen(){
    set_transition_game_life->setEnabled(true);
    grid_view->setEnabled(true);
}
void Interface2D::blockAfterAutomateChanged(){
    set_transition_game_life->setEnabled(false);
    grid_view->setEnabled(false);
}
