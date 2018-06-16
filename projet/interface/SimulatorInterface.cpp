#include "SimulatorInterface.h"
#include "../autocell/SimulatorException.h"
#include "HomeView.h"

#include <QMessageBox>
#include <algorithm>

/*
|--------------------------------------------------------------------------
|	Widget Initialisation
|--------------------------------------------------------------------------
*/

void SimulatorInterface::setGridControls(QBoxLayout* parent) {
	grid_controls = new QHBoxLayout();			// view or grid ?
	parent->addLayout(grid_controls);
	setDimensionControls(grid_controls);
	setInitialStateControls(grid_controls);
}

void SimulatorInterface::setAutomateControls(QBoxLayout* parent){
	automate_controls = new QVBoxLayout;
	parent->addLayout(automate_controls);
	setTransitionControls(automate_controls);
	setStateControls(automate_controls);
}

void SimulatorInterface::setAutomateChoice(QBoxLayout* parent){
	choose_automate = new QPushButton("Choisir cet automate");
	change_automate = new QPushButton("Changer d'automate");
    save_automate = new QPushButton("Sauvegarder l'état de l'automate");
	parent->addWidget(choose_automate);
	parent->addWidget(change_automate);
    parent->addWidget(save_automate);

	QObject::connect(choose_automate, SIGNAL(clicked()), this, SLOT(chosenAutomate()));
	QObject::connect(change_automate, SIGNAL(clicked()), this, SLOT(changedAutomate()));
    QObject::connect(save_automate, SIGNAL(clicked()), this, SLOT(saveAutomate()));
}

void SimulatorInterface::setStateControls(QBoxLayout* parent) {
	state_controls = new QHBoxLayout();
	parent->addLayout(state_controls);
}

void SimulatorInterface::setTransitionControls(QBoxLayout* parent) {
	transition_controls = new QHBoxLayout();
	parent->addLayout(transition_controls);
	set_transition_rules = new QPushButton("Choix des transitions");
	transition_controls->addWidget(set_transition_rules);

	QObject::connect(set_transition_rules, SIGNAL(clicked()), this, SLOT(choose_transition_rules()));
}

void SimulatorInterface::setDimensionControls(QBoxLayout* parent) {
	grid_dim_controls = new QVBoxLayout();
	parent->addLayout(grid_dim_controls);

	// Layout
	grid_dim_select_layout = new QHBoxLayout();
	grid_dim_bts_layout = new QHBoxLayout();
	grid_dim_controls->addLayout(grid_dim_select_layout);
	grid_dim_controls->addLayout(grid_dim_bts_layout);
	// Selectors
	grid_dim_label = new QLabel("Choisissez les dimensions de la grille: ");
	grid_dim_spinbox = new QSpinBox();
	grid_dim_spinbox->setRange(3,100);
	grid_dim_spinbox->setAlignment(Qt::AlignHCenter);
	grid_dim_spinbox->setValue(10);
	// Buttons
	grid_dim_set_bt = new QPushButton("Valider");
	grid_dim_reset_bt = new QPushButton("Reset");
	// Add Items to Layouts
	grid_dim_select_layout->addWidget(grid_dim_label);
	grid_dim_select_layout->addWidget(grid_dim_spinbox);
	grid_dim_bts_layout->addWidget(grid_dim_set_bt);
	grid_dim_bts_layout->addWidget(grid_dim_reset_bt);

	// Slots
	connect(grid_dim_set_bt, SIGNAL(clicked()), this, SLOT(grid_set_dim()));
	connect(grid_dim_reset_bt, SIGNAL(clicked()), this, SLOT(grid_reset_dim()));
}

void SimulatorInterface::setInitialStateControls(QBoxLayout* parent) {
	initial_state_controls = new QVBoxLayout();
	parent->addLayout(initial_state_controls);

	initial_state_label = new QLabel("Sélectionner un état de départ");
	initial_state_setter = new QPushButton("Appliquer l'état");
	initial_state_selector = new QComboBox();      // Liste déroulante avec grilles de départs
	initial_state_selector->addItem("Vide", QVariant(0));
	initial_state_selector->addItem("Au hasard", QVariant(1));
	initial_state_selector->addItem("Symétrique vertical", QVariant(2));
	initial_state_selector->addItem("Symétrique horizontal", QVariant(3));
	initial_state_selector->addItem("Etats croissant", QVariant(4));
	initial_state_selector->addItem("Etats décroissant", QVariant(5));
	// Add Items to Layout
	initial_state_controls->addWidget(initial_state_label);
	initial_state_controls->addWidget(initial_state_selector);
	initial_state_controls->addWidget(initial_state_setter);

	// Slot
	connect(initial_state_setter, SIGNAL(clicked()), this, SLOT(set_default_grid()));
}

void SimulatorInterface::setSimulatorControls(QBoxLayout* parent) {
	simulation_controls = new QVBoxLayout();
	parent->addLayout(simulation_controls);

	simulation_label = new QLabel("Mode de simulation");
	simulation_label->setAlignment(Qt::AlignCenter);
	simulation_controls->addWidget(simulation_label);

	// Speed Controls
	speed_label = new QLabel("Vitesse (en secondes)");
	speed_selector = new QDoubleSpinBox();
	speed_selector->setValue(0.1);
	speed_selector->setRange(0.01, 5.0);
	speed_selector->setSingleStep(0.1);
	speed_selector->setAlignment(Qt::AlignHCenter);
	// Speed Layout
	speed_layout = new QHBoxLayout();
	simulation_controls->addLayout(speed_layout);
	speed_layout->addWidget(speed_label);
	speed_layout->addWidget(speed_selector);

	// Run Controls
	sim_start_bt = new QPushButton("Lancer");
	sim_step_bt = new QPushButton("Avancer d'un pas");
	sim_run_layout = new QHBoxLayout();
	sim_run_layout->addWidget(sim_start_bt);
	sim_run_layout->addWidget(sim_step_bt);
	sim_stop_bt = new QPushButton("Arrêter");
	sim_reset_bt = new QPushButton("Remettre à l'état initial");
	// Run Layout
	simulation_controls->addLayout(sim_run_layout);
	simulation_controls->addWidget(sim_stop_bt);
	simulation_controls->addWidget(sim_reset_bt);

	// Slots
	connect(sim_start_bt, SIGNAL(clicked()), this, SLOT(start_simulation()));
	connect(sim_step_bt, SIGNAL(clicked()), this, SLOT(step_simulation()));
	connect(sim_stop_bt, SIGNAL(clicked()), this, SLOT(stop_simulation()));
	connect(sim_reset_bt, SIGNAL(clicked()), this, SLOT(reset_simulation()));
}

void SimulatorInterface::addFirstState(QBoxLayout* parent){
//    state_vector = new QVector <QPair<StateInterface*, QPushButton*> >;
	QPair < StateInterface*, QPushButton*>* pair = new QPair < StateInterface*, QPushButton*> ;
	pair->first = new StateInterface();
	pair->second = new QPushButton;
	state_vector->push_back(*pair);
	parent->addLayout(state_vector->last().first);
}


/*
|--------------------------------------------------------------------------
|	Main Functions
|--------------------------------------------------------------------------
*/

/**
 * @brief Constructeur de la classe abstraite SimulatorInterface
 * @details Instancie et configure tous les éléments de l'interface
 * @param La dimension du Simulateur
 */
SimulatorInterface::SimulatorInterface(const short unsigned int dim): QWidget(), automate_dimension(dim) {
	// Get Manager
	manager = SimulatorManager::getManager();

	// Set Config
	setWindowTitle(QString::fromStdString("Interface " + std::to_string(automate_dimension) + "D"));
	grid_dimension = 10;
	grid_size = 400;
	changeCellEnabled = true;
	sim_is_running = false;


	// =========== Main Layout ===========
	// Init Main Layouts
	main_layout = new QHBoxLayout();
	controls_layout = new QVBoxLayout();
	view_layout = new QVBoxLayout();
	state_main_layout = new QVBoxLayout();
	// Configure Main Layouts
	setLayout(main_layout);
	main_layout->addLayout(state_main_layout);
	main_layout->addLayout(controls_layout);
	main_layout->addLayout(view_layout);

	// Configure State Layout
//	valid_state = new QPushButton("Valider");
//	state_main_layout->addWidget(valid_state);
	state_layout_display = new QVBoxLayout;
	state_main_layout->addLayout(state_layout_display);

	state_vector = new QVector <QPair<StateInterface*, QPushButton*> >;
	displayExistingStates();
	addFirstState(state_layout_display);

	add_state = new QPushButton("Ajouter état");
	state_main_layout->addWidget(add_state);

	QObject::connect(add_state, SIGNAL(clicked()), this, SLOT(add_new_state()));

	// =========== Window Controls ===========
	window_controls = new QHBoxLayout();
	controls_layout->addLayout(window_controls);
	// Add items
	quit_bt = new QPushButton("Quitter");
	home_bt = new QPushButton("Retour au menu principal");
	window_controls->addWidget(quit_bt);
	window_controls->addWidget(home_bt);
	// Connect slots
	QObject::connect(quit_bt, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(home_bt, SIGNAL(clicked()), this, SLOT(home()));

	// =========== Init Controls ===========
	setGridControls(controls_layout);
	setAutomateChoice(controls_layout);
	setAutomateControls(controls_layout);
	setSimulatorControls(controls_layout);

	// Block simulation by default
	changedAutomate();

	// Simulation Timer
	sim_timer = new QTimer(this);
	connect(sim_timer, SIGNAL(timeout()), this, SLOT(iterate_simulation()));
}


/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/

/**
 * @brief Ferme la fenêtre et affiche la page d'accueil
 */
void SimulatorInterface::home() {
	close();
	HomeView* home = new HomeView();
	home->show();
}


// ==================== Simulation Slots ====================

/**
 * @brief Lance la simulation de manière continue
 */
void SimulatorInterface::start_simulation() {
	// Disable dimension changes
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	// Disable start/step/reset/speed changes
	sim_start_bt->setEnabled(false);
	sim_step_bt->setEnabled(false);
	sim_reset_bt->setEnabled(false);
	speed_selector->setEnabled(false);
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

void SimulatorInterface::speedSelectorChangedValue(double val){
	if (val > 0)
		sim_timer->start(1000 * val);
	else
		sim_timer->start(10);
}

/**
 * @brief Avance la simulation d'un itération
 */
void SimulatorInterface::step_simulation() {
	// Disable dimension changes
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	// Disable initial state changes
	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);

	// Step simulation
	iterate_simulation();
//    changeCellEnabled = false;
}

/**
 * @brief Arrête la simulation
 */
void SimulatorInterface::stop_simulation() {
	// Stop simulation
	sim_is_running = false;
	sim_timer->stop();

	// Enable start/step/reset/speed changes
	sim_start_bt->setEnabled(true);
	sim_step_bt->setEnabled(true);
	sim_reset_bt->setEnabled(true);
	speed_selector->setEnabled(true);
	changeCellEnabled = true;
}

/**
 * @brief Remet le simulateur dans son état initial
 */
void SimulatorInterface::reset_simulation() {
	// Enable grid dimension changes
	grid_dim_spinbox->setEnabled(true);
	grid_dim_set_bt->setEnabled(true);
	grid_dim_reset_bt->setEnabled(true);
	// Enable initial state selection
	initial_state_selector->setEnabled(true);
	initial_state_setter->setEnabled(true);
	changeCellEnabled = true;
}

/**
 * @brief Fait muter les cellules du simulateur et affiche les changements
 */
void SimulatorInterface::iterate_simulation() {
	if (!SimulatorManager::getManager()->getSimulator()->mutate())
		sim_timer->stop();
	changeGridCells();
}


// ==================== Grid Slots ====================

void SimulatorInterface::grid_set_dim(){
	grid_dimension = grid_dim_spinbox->value();
//	redrawGrid(view_layout);
}
void SimulatorInterface::grid_reset_dim() {
	grid_dim_spinbox->setValue(10);
	grid_dimension = 10;
//	redrawGrid(view_layout);
}

void SimulatorInterface::set_default_grid() {
	unsigned int combo_value = initial_state_selector->currentIndex();
	simulator = SimulatorManager::getManager()->getSimulator();

	switch (combo_value){
		case 0 :
			simulator->generateStateCells();
			break;
		case 1 :
			simulator->generateRandomCells();
            break;
        case 2 :
            simulator->generateVerticalSymetricRandomCells();
            break;
        case 3 :
            simulator->generateHorizontalSymetricRandomCells();
            break;
        case 4 :
			simulator->generateAlternedCells();
			break;
        case 5 :
			simulator->generateDescAlternedCells();
			break;
	}
	changeGridCells();
}


// ==================== Transition Slots ====================

void SimulatorInterface::choose_transition_rules(){
	this->setEnabled(false); // A voir pour bloquer la fenetre mere et débloquer à la fermeture
	TransitionInterface* windowtransition = new TransitionInterface();
	windowtransition->show();

	// A la fermeture de la fenêtre du choix des transitions
	QObject::connect(windowtransition, SIGNAL(close_transition_interface()), this, SLOT(choose_transition_rules_finished()));
}


void SimulatorInterface::choose_transition_rules_finished(){
	this->setEnabled(true);
}

// ==================== Automate choice Slots ====================
void SimulatorInterface::chosenAutomate(){
	if (SimulatorManager::getManager()->getStateNumber() < 1) {
		QMessageBox::critical(this, "Attention", "Il faut définir au moins 1 état");
		return;
	} else {
		try {
			// Create Simulator
			manager = SimulatorManager::getManager();
            try {
                simulator = manager->getSimulator();
                grid_dimension = manager->getGridSize();
            } catch(SimulatorException error) {
                manager->setGridSize(grid_dimension);
                simulator = manager->createSimulator(automate_dimension);
            }

			// Disable every left buttons
			add_state->setEnabled(false);
			state_vector->last().second->setEnabled(false);
			state_vector->last().first->state_name->setEnabled(false);
			state_vector->last().first->color_button->setEnabled(false);

			grid_dim_spinbox->setEnabled(false);
			grid_dim_controls->setEnabled(false);
			grid_dim_set_bt->setEnabled(false);
			grid_dim_reset_bt->setEnabled(false);

			choose_automate->setEnabled(false);

			// Enable right buttons
			change_automate->setEnabled(true);
			set_transition_rules->setEnabled(true);
			speed_selector->setEnabled(true);
			sim_start_bt->setEnabled(true);
			sim_step_bt->setEnabled(true);
			sim_stop_bt->setEnabled(true);
			sim_reset_bt->setEnabled(true);

			initial_state_selector->setEnabled(true);
			initial_state_setter->setEnabled(true);

			blockAfterAutomateChosen();
			redrawGrid(view_layout);
			changeCellEnabled = true;
		} catch (SimulatorException error) {
			QMessageBox::critical(this, "Erreur", QString::fromStdString(error.what()));
		}
	}
}

void SimulatorInterface::changedAutomate(){
	changeCellEnabled = false;

	// Enable every left buttons
	add_state->setEnabled(true);
	state_vector->last().second->setEnabled(true);
	state_vector->last().first->state_name->setEnabled(true);
	state_vector->last().first->color_button->setEnabled(true);

	grid_dim_spinbox->setEnabled(true);
	grid_dim_controls->setEnabled(true);
	grid_dim_set_bt->setEnabled(true);
	grid_dim_reset_bt->setEnabled(true);

	choose_automate->setEnabled(true);

	// Disnable right buttons
    save_automate->setEnabled(false);
	change_automate->setEnabled(false);
	set_transition_rules->setEnabled(false);
	speed_selector->setEnabled(false);
	sim_start_bt->setEnabled(false);
	sim_step_bt->setEnabled(false);
	sim_stop_bt->setEnabled(false);
	sim_reset_bt->setEnabled(false);

	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);

	blockAfterAutomateChanged();
}

// ==================== State Slots ====================

void SimulatorInterface::add_new_state(){
	QPair<StateInterface*,QPushButton*>& lastState = state_vector->last();
	if (lastState.first->state_name->text().isEmpty()) {
		QMessageBox::critical(this, "ERREUR", "Vous devez entrer des valeurs pour les champs");
	} else {
		std::string name = lastState.first->state_name->text().toStdString();
		std::string color = lastState.first->color_button->item(0,0)->backgroundColor().name().toStdString();
		try {
			// Try to create State and add it to StateInterface
			State* newState = manager->createNewState(name, color);
			lastState.first->setState(newState);

			// Config View
			lastState.first->state_name->setEnabled(false);
			lastState.first->color_button->setEnabled(false);
			lastState.second = new QPushButton("Supprimer");
			lastState.first->addWidget(state_vector->last().second);
			QObject::connect(state_vector->last().second, SIGNAL(clicked()), this, SLOT(delete_state()));

			// Add new slot
			QPair <StateInterface*, QPushButton*>* pair = new QPair <StateInterface*, QPushButton*> ;
			pair->first = new StateInterface();
			pair->second = new QPushButton;
			state_vector->push_back(*pair);
			state_layout_display->addLayout(state_vector->last().first);
		} catch(SimulatorException error) {
			QMessageBox::critical(this, "Erreur", QString::fromStdString(error.what()));
		}
	}
}

void SimulatorInterface::displayExistingStates(){
	SimulatorManager* manager = SimulatorManager::getManager();
	std::vector<State*>::const_iterator it;
	for (it = manager->getFirstState(); it != manager->getLastState(); it++) {
		// Create view elements
		StateInterface* state_interface = new StateInterface((*it)->getName(), (*it)->getColor(), (*it));
		QPushButton* button = new QPushButton("Supprimer");
		QObject::connect(button, SIGNAL(clicked()), this, SLOT(delete_state()));

		// Configure view
		QPair < StateInterface*, QPushButton*>* pair = new QPair < StateInterface*, QPushButton*> ;
		pair->first = state_interface;
		pair->second = button;
		state_vector->push_back(*pair);
		state_vector->last().first->addWidget(button);
		state_layout_display->addLayout(state_vector->last().first);
	}
}


void SimulatorInterface::delete_state() {
	QObject* sdr = sender();
	QPushButton* button = dynamic_cast<QPushButton*>(sdr);
	QVector< QPair<StateInterface*, QPushButton*> >::iterator it;
	it = std::remove_if(state_vector->begin(), state_vector->end(),
		[&sdr, &button](QPair<StateInterface*, QPushButton*> pair) { return pair.second == button; });
	// TODO FIX getState = 0 ???
	try {
		SimulatorManager::getManager()->removeState(it->first->getState());
	} catch (SimulatorException error) {
		QMessageBox::critical(this, "Erreur", QString::fromStdString(error.what()));
	}
}


void SimulatorInterface::saveAutomate(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarder l'automate"), "",
            tr("Adresse du fichier (*.json)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                    file.errorString());
                return;
            }
    }

    SimulatorManager::getManager()->importConfig(fileName.toStdString());
}

