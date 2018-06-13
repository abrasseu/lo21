#include "SimulatorInterface.h"
#include "HomeView.h"
#include <unistd.h>


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

void SimulatorInterface::setStateControls(QBoxLayout* parent) {
	state_controls = new QHBoxLayout();
	parent->addLayout(state_controls);
}

void SimulatorInterface::setTransitionControls(QBoxLayout* parent) {
	transition_controls = new QHBoxLayout();
	parent->addLayout(transition_controls);
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
	grid_dim_spinbox->setAlignment(Qt::AlignRight);
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
	initial_state_selector = new QComboBox();      // Liste déroulante avec grilles de départs
	initial_state_selector->addItem("Un seul au milieu", QVariant(1));
	initial_state_selector->addItem("Au hasard", QVariant(2));
	initial_state_selector->addItem("Un sur deux", QVariant(3));
	initial_state_selector->addItem("Un sur trois", QVariant(4));
	initial_state_setter = new QPushButton("Appliquer l'état");
	// Add Items to Layout
	initial_state_controls->addWidget(initial_state_label);
	initial_state_controls->addWidget(initial_state_selector);
	initial_state_controls->addWidget(initial_state_setter);

	// Slot
	connect(initial_state_setter, SIGNAL(clicked()), this, SLOT(set_initial_state()));
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
	speed_selector->setValue(1.0);
	speed_selector->setRange(0.1, 10.0);
	speed_selector->setSingleStep(0.5);
	//speed_selector->setAlignment(Qt::AlignHCenter);
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



/*
|--------------------------------------------------------------------------
|	Main Functions
|--------------------------------------------------------------------------
*/

/**
 * @brief Constructeur de la classe abstraite SimulatorInterface
 * @details Instancie et configure tous les éléments de l'interface
 * @param parent
 */
SimulatorInterface::SimulatorInterface(short unsigned int automate_dimension): QWidget() {
	setWindowTitle(QString::fromStdString("Interface " + std::to_string(automate_dimension) + "D"));
	grid_dimension = 10;
	grid_size = 400;
	simulator = nullptr;
	changeCellEnabled = true;
	sim_is_running = false;

	// === Main Layout
	// Init Main Layouts
	main_layout = new QHBoxLayout();
	controls_layout = new QVBoxLayout();
	view_layout = new QVBoxLayout();

	// Configure Main Layouts
	setLayout(main_layout);
	main_layout->addLayout(controls_layout);
	main_layout->addLayout(view_layout);


	// === Window Controls
	window_controls = new QHBoxLayout();
	controls_layout->addLayout(window_controls);

	// Add items
	quit_bt = new QPushButton("Quitter");
	home_bt = new QPushButton("Retour au menu principal");
	window_controls->addWidget(quit_bt);
	window_controls->addWidget(home_bt);

	// Configure Slots
	QObject::connect(quit_bt, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(home_bt, SIGNAL(clicked()), this, SLOT(home()));


	// === Init Controls
	setGridControls(controls_layout);
	setAutomateControls(controls_layout);
	setSimulatorControls(controls_layout);

}

/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/

void SimulatorInterface::home() {
	close();
	HomeView* home = new HomeView();
	home->show();
}

// === Grid Dimension Slots
void SimulatorInterface::grid_set_dim(){
	grid_dimension = grid_dim_spinbox->value();
	drawGrid();
}
void SimulatorInterface::grid_reset_dim() {
	grid_dim_spinbox->setValue(10);
	grid_dimension = 10;
	drawGrid();
}

// === Simulation Slots
void SimulatorInterface::start_simulation() {
	sim_start_bt->setEnabled(false);
	sim_step_bt->setEnabled(false);
	speed_selector->setEnabled(false);
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);

	// Run simulation until it stage
	sim_is_running = true;
	while(sim_is_running && simulator->mutate())
		usleep(60 * 1000);
	sim_is_running = false;
}

void SimulatorInterface::step_simulation() {
	sim_start_bt->setEnabled(true);
	sim_step_bt->setEnabled(true);
	speed_selector->setEnabled(true);
	grid_dim_spinbox->setEnabled(false);
	grid_dim_set_bt->setEnabled(false);
	grid_dim_reset_bt->setEnabled(false);
	initial_state_selector->setEnabled(false);
	initial_state_setter->setEnabled(false);

	// Step simulation
	sim_is_running = true;
	simulator->mutate();
	sim_is_running = false;
}
void SimulatorInterface::stop_simulation() {
	sim_start_bt->setEnabled(true);
	sim_step_bt->setEnabled(true);
	speed_selector->setEnabled(true);
	sim_is_running = false;
}
void SimulatorInterface::reset_simulation() {
	sim_start_bt->setEnabled(true);
	sim_step_bt->setEnabled(true);
	grid_dim_spinbox->setEnabled(true);
	grid_dim_set_bt->setEnabled(true);
	grid_dim_reset_bt->setEnabled(true);
	speed_selector->setEnabled(true);
	initial_state_selector->setEnabled(true);
	initial_state_setter->setEnabled(true);
}

// === Grid Slots

void SimulatorInterface::set_initial_state() {

}

