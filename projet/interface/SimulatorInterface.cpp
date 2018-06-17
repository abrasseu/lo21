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

/**
 * \brief Crée et affiche le layout de choix des différents
 * \details Crée un premier état vide pour sélectionner les paramètres de l'état et l'affiche
 * \param parent    layout contenant l'affichage
 */
void SimulatorInterface::addFirstState(QBoxLayout* parent){
//    state_vector = new QVector <QPair<StateInterface*, QPushButton*> >;
    QPair < StateInterface*, QPushButton*>* pair = new QPair < StateInterface*, QPushButton*> ;
    pair->first = new StateInterface();
    pair->second = new QPushButton;
    state_vector->push_back(*pair);
    parent->addLayout(state_vector->last().first);
}

/**
 * \brief Met en place l'affichage pour le choix des dimensions de la grille
 * \details Met en place les layout qui contiennent les choix de dimension et d'état initial de la grille
 * \param parent    layout contenant l'affichage
 */
void SimulatorInterface::setGridControls(QBoxLayout* parent) {
    grid_controls = new QHBoxLayout();			// view or grid ?
    parent->addLayout(grid_controls);
    setDimensionControls(grid_controls);
    setInitialStateControls(grid_controls);
}

/**
 * \brief Met en place l'affichage pour le choix de transitions
 * \details Crée les layout qui contiennent les affichages pour régler les transitions et états
 * \param parent    layout contenant l'affichage
 */
void SimulatorInterface::setAutomateControls(QBoxLayout* parent){
    automate_controls = new QVBoxLayout;
    parent->addLayout(automate_controls);
    setTransitionControls(automate_controls);
    setStateControls(automate_controls);
}

/**
 * \brief Met en place l'affichage pour le choix des transitions et des états
 * \details Affiche le bouton pour choisir les différentes règles de transitions
 * \param parent    layout contenant l'affichage
 */
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

/**
 * \brief Crée un layout pour le choix des états
 * \param parent    layout contenant l'affichage
 */
void SimulatorInterface::setStateControls(QBoxLayout* parent) {
    state_controls = new QHBoxLayout();
    parent->addLayout(state_controls);
}

/**
 * \brief Crée l'affichage pour le choix des transitions
 * \details Affiche le bouton pour choisir les différentes règles de transitions
 * \param parent    layout contenant l'affichage
 */
void SimulatorInterface::setTransitionControls(QBoxLayout* parent) {
    transition_controls = new QHBoxLayout();
    parent->addLayout(transition_controls);
    set_transition_rules = new QPushButton("Choix des transitions");
    transition_controls->addWidget(set_transition_rules);

    QObject::connect(set_transition_rules, SIGNAL(clicked()), this, SLOT(choose_transition_rules()));
}

/**
 * \brief Crée l'affichage pour le choix des dimensions de la grille
 * \details Affiche les boutons, textes et zones éditables pour choisir les dimensions de la grille
 * \param parent    layout contenant l'affichage
 */
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

/**
 * \brief Crée un affichage pour choisir l'état initial de la grille
 * \details Crée le texte, les boutons ainsi qu'une liste déroulante pour choisir l'état initial de la grille
 * \param parent    layout contenant l'affichage
 */
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

/**
 * \brief Crée l'affichage pour sélectionner les options de simulation: départ, pas à pas, stop, état initial
 * \details Affiche les boutons pour choisir les options de simulation et la lancer
 * \param parent    layout contenant l'affichage
 */
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
    manager->setDimension(dim);
    modify_speed_value = false;

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
 * \brief Ferme la fenêtre et affiche la page d'accueil
 */
void SimulatorInterface::home() {
    SimulatorManager::getManager()->deleteSimulator();
    close();
    HomeView* home = new HomeView();
    home->show();
}


// ==================== Simulation Slots ====================

/**
 * \brief Lance la simulation de manière continue
 * \details Arrête la simulation et remet à jour l'état des boutons pour pouvoir cliquer sur les bons boutons
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
    sim_stop_bt->setEnabled(true);


    speed_selector->setEnabled(true);
    modify_speed_value = true;


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
 * \brief Met à jour la vitesse de simulation
 * \details Met à jour la vitesse de simulation lors du changement de vitesse en cours de simulation
 * \param val   valeur de la vitesse de simulation
 */
void SimulatorInterface::speedSelectorChangedValue(double val){
    if (modify_speed_value){
        if (val > 0)
            sim_timer->start(1000 * val);
        else
            sim_timer->start(10);
    }
}

/**
 * \brief Avance la simulation d'une itération
 * \details Arrête la simulation et remet à jour l'état des boutons pour pouvoir cliquer sur les bons boutons
 */
void SimulatorInterface::step_simulation() {
    // Disable dimension changes
    grid_dim_spinbox->setEnabled(false);
    grid_dim_set_bt->setEnabled(false);
    grid_dim_reset_bt->setEnabled(false);
    // Disable initial state changes
    initial_state_selector->setEnabled(false);
    initial_state_setter->setEnabled(false);

    modify_speed_value = false;

    // Step simulation
    iterate_simulation();
//    changeCellEnabled = false;
}

/**
 * \brief Arrête la simulation
 * \details Arrête la simulation et remet à jour l'état des boutons pour pouvoir cliquer sur les bons boutons
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
    sim_stop_bt->setEnabled(false);
    modify_speed_value = false;
    changeCellEnabled = true;
}

/**
 * @brief Remet le simulateur dans son état initial
 */
void SimulatorInterface::reset_simulation() {
    SimulatorManager::getManager()->getSimulator()->resetToInitialCells();

    // Enable grid dimension changes
    grid_dim_spinbox->setEnabled(false);
    grid_dim_set_bt->setEnabled(false);
    grid_dim_reset_bt->setEnabled(false);
    // Enable initial state selection
    initial_state_selector->setEnabled(true);
    initial_state_setter->setEnabled(true);
    changeCellEnabled = true;

    changeGridCells();
}

/**
 * @brief Fait muter les cellules du simulateur et affiche les changements
 */
void SimulatorInterface::iterate_simulation() {
    if (!SimulatorManager::getManager()->getSimulator()->mutate()){
        sim_timer->stop();
        sim_start_bt->setEnabled(true);
        sim_step_bt->setEnabled(true);
        sim_reset_bt->setEnabled(true);
        sim_stop_bt->setEnabled(false);
    }
    changeGridCells();
}


// ==================== Grid Slots ====================

/**
 * \brief Change la dimension de la grille
 * \details Slot. Change la dimension de la grille avec la valeur entrée
 */
void SimulatorInterface::grid_set_dim(){
    grid_dimension = grid_dim_spinbox->value();
//    redrawGrid(view_layout);
}
/**
 * \brief Réinitialise la dimension de la grille
 * \details Slot. Remet la dimension de la grille à la valeur initiale (10)
 */
void SimulatorInterface::grid_reset_dim() {
    grid_dim_spinbox->setValue(10);
    grid_dimension = 10;
//    redrawGrid(view_layout);
}

/**
 * \brief Affiche la grille avec un état choisi parmi les états par défaut de la liste déroulante
 */
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
            simulator->generateAlternedCells();
            break;
        case 4 :
            simulator->generateDescAlternedCells();
            break;
    }
    changeGridCells();
}


// ==================== Transition Slots ====================
/**
 * \brief Ouvre la fenêtre du choix des transitions
 * \details Slot. Ouvre la fenêtre du choix des transitions et bloque la fenêtre d'interface tant que la fenêtre
 *          transition n'est pas fermée
 */
void SimulatorInterface::choose_transition_rules(){
    this->setEnabled(false); // A voir pour bloquer la fenetre mere et débloquer à la fermeture
    TransitionInterface* windowtransition = new TransitionInterface();
    windowtransition->show();

    // A la fermeture de la fenêtre du choix des transitions
    QObject::connect(windowtransition, SIGNAL(close_transition_interface()), this, SLOT(choose_transition_rules_finished()));
}

/**
 * \brief Fenêtre interface est de nouveau disponible car la fenêtre transition est fermée
 */
void SimulatorInterface::choose_transition_rules_finished(){
    this->setEnabled(true);
}

// ==================== Automate choice Slots ====================
/**
 * \brief Définit les paramètres choisis de l'automate
 * \details Slot. Bloque et débloque les boutons une fois que les états et dimensions ont été choisis
 */
void SimulatorInterface::chosenAutomate(){
    if (SimulatorManager::getManager()->getStateNumber() < 1) {
        QMessageBox::critical(this, "Attention", "Il faut définir au moins 1 état");
        return;
    } else {
        try {
            // Récupération de la simulation
            manager = SimulatorManager::getManager();
            if (manager->simulatorExists()) {
                simulator = manager->getSimulator();
                grid_dimension = manager->getGridSize();
            }
            else {
                manager->setGridSize(grid_dimension);
                simulator = manager->createSimulator(automate_dimension);
            }

            // Disable every left buttons
            add_state->setEnabled(false);
            state_vector->last().second->setEnabled(false);
            state_vector->last().first->state_name->setEnabled(false);
            state_vector->last().first->color_button->setEnabled(false);

            for (auto it = state_vector->begin(); it != state_vector->end(); ++it){
                it->second->setEnabled(false);
            }

            grid_dim_spinbox->setEnabled(false);
            grid_dim_controls->setEnabled(false);
            grid_dim_set_bt->setEnabled(false);
            grid_dim_reset_bt->setEnabled(false);

            choose_automate->setEnabled(false);

            // Enable right buttons
            save_automate->setEnabled(true);
            change_automate->setEnabled(true);
            set_transition_rules->setEnabled(true);
            speed_selector->setEnabled(true);
            sim_start_bt->setEnabled(true);
            sim_step_bt->setEnabled(true);
            sim_stop_bt->setEnabled(false);
            sim_reset_bt->setEnabled(true);

            initial_state_selector->setEnabled(true);
            initial_state_setter->setEnabled(true);

            redrawGrid(view_layout);
            changeGridCells();
            blockAfterAutomateChosen();
            changeCellEnabled = true;
        } catch (SimulatorException error) {
            QMessageBox::critical(this, "Erreur", QString::fromStdString(error.what()));
        }
    }
}

/**
 * \brief Définit les paramètres choisis de l'automate
 * \details Slot. Bloque et débloque les boutons pour pouvoir changer les états et dimensions
 */
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

    for (auto it = state_vector->begin(); it != state_vector->end(); ++it){
        it->second->setEnabled(true);
    }

    choose_automate->setEnabled(true);

    // Disable right buttons
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
/**
 * \brief Ajoute un nouvel état
 * \details Slot. Ajoute un nouvel état à la liste des états et vérifie qu'on peut l'ajouter
 */
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

    if (SimulatorManager::getManager()->simulatorExists())
        changeGridCells();
}

/**
 * \brief Affiche les états déjà existant
 */
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

/**
 * \brief Supprime un état et le retire de l'affichage
 */
void SimulatorInterface::delete_state() {
	QObject* sdr = sender();
	QPushButton* button = dynamic_cast<QPushButton*>(sdr);

    if (state_vector->size() < 3)
        QMessageBox::critical(this, "Erreur", "Il est nécessaire d'avoir au moins un état");
    else {
        for (auto it = state_vector->begin(); it != state_vector->end(); it++) {
            if (it->second == button) {
                try {
                    SimulatorManager::getManager()->removeState(it->first->getState());
                } catch (SimulatorException error) {}

                delete it->first;
                delete it->second;
                state_vector->erase(it);

                break;
            }
        }

        changeGridCells();
    }
}

/**
 * \brief Enregistre un automate
 * \details Slot. Enregistre les paramètres d'un automate: états, dimensions, règles de transitions
 */
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

    SimulatorManager::getManager()->exportConfig(fileName.toStdString());
}

