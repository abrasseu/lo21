#include "../autocell/SimulatorManager.h"
#include "TransitionInterface.h"

/**
 * \brief Constructeur de la fenêtre d'affichage des transitions
 */
TransitionInterface::TransitionInterface() : QWidget() {
    Simulator* simulator = SimulatorManager::getManager()->getSimulator();
    state_list = simulator->getInitStates();
    state_list_number = simulator->getStateNbr();
    neighbour_number = simulator->getNeighbourNbr();

    setWindowTitle("Transitions");
    QVBoxLayout* princ = new QVBoxLayout;
    setLayout(princ);

    // Set Main Layout
    QScrollArea *scroll = new QScrollArea;
    princ->addWidget(scroll);

    scroll->setWidgetResizable(false);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setFixedSize(900,500);
    scroll->verticalScrollBar();
    scroll->adjustSize();
    main_layout = new QVBoxLayout;
    scroll->setLayout(main_layout);
    main_layout->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(main_layout);

    title = new QLabel("Choisissez les règles de transition de l'automate");
    main_layout->addWidget(title);
    title->setAlignment(Qt::AlignHCenter|Qt::AlignTop);


    // Set Transition Layout
    transition_layout = new QVBoxLayout;
    main_layout->addLayout(transition_layout);

    transition_vector = new QVector< QPair< Transition *, QPushButton* > >;
    displayExistingRules();
    addNewTransitionRule();

    transition_add_rule = new QPushButton("Ajouter une nouvelle règle");
    transition_valid = new QPushButton("Valider");
    main_layout->addWidget(transition_add_rule);
    main_layout->addWidget(transition_valid);


    QObject::connect(transition_add_rule, SIGNAL(clicked()), this, SLOT(addNewTransitionRule()));
    QObject::connect(transition_valid, SIGNAL(clicked()), this, SLOT(validateRules()));
}

/**
 * \brief Affiche les règles déjà existantes
 */
void TransitionInterface::displayExistingRules(){
    for (auto ite_state = SimulatorManager::getManager()->getFirstState(); ite_state != SimulatorManager::getManager()->getLastState(); ite_state++){

        for (auto it = (*ite_state)->getFirstRule(); it != (*ite_state)->getLastRule(); ++it){
            uint* tab = new uint[SimulatorManager::getManager()->getStateNumber()];

            std::map<State*, uint> sum;
            for (auto it_vec_state = (*it)->getFirstState(); it_vec_state != (*it)->getLastState(); ++it_vec_state){
                if ( sum.find(*it_vec_state) != sum.end()){
                    sum[*it_vec_state]++;
                }
                else {
                    sum[*it_vec_state] = 1;
                }
            }
            uint j = 0;
            for (auto compare = SimulatorManager::getManager()->getFirstState(); compare != SimulatorManager::getManager()->getLastState(); compare++){
                std::map<State*, uint>::iterator value_return_map = sum.find(*compare);

                if (value_return_map != sum.end()){
                    tab[j] = value_return_map->second;
                }
                else{
                    tab[j] = 0;
                }
                j++;
            }

            Transition* tr = new Transition(state_list, SimulatorManager::getManager()->getStateNumber(), SimulatorManager::getManager()->getSimulator()->getNeighbourNbr(),
                                            tab, *ite_state, (*it)->getState(), false);
            transition_layout->addLayout(tr);

        }
    }
}

/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/
/**
 * \brief Ferme la fenêtre des transitions
 * \details Slot. Ferme la fenêtre des transitions une fois qu'elles sont choisies
 */
void TransitionInterface::validateRules(){
    this->close();
}

/**
 * \brief Slot. Ajoute une règle de transition
 */
void TransitionInterface::addNewTransitionRule(){
    // On test si le nombre de voisins dans la règle n'est pas supérieur au nombre de voisin maximum
    if (!transition_vector->empty()){
        // Si il y a déjà au moins 1 règle
        if (transition_vector->size() != 1){
            Transition* tr = transition_vector->last().first;
            unsigned int sum = 0;
            for (unsigned int i = 0; i < tr->getNbStates(); i++)
                sum += tr->neighbours[i]->second->value();
            // Si la somme des valeurs entrées dépasse le nombre de voisins possible, on affiche un message d'erreur
            if (sum > tr->getNeighboursNb()){
                QMessageBox::warning(this, "ERREUR", "Le nombre de voisins est supérieur au nombre de voisins total possibles");
                return;
            }
            // On insère la valeur
            else{
                Transition* add_transi = new Transition(state_list, state_list_number, neighbour_number);
                if (addNewTransitionRuleValid(tr)){
                    transition_vector->last().first->start_state = SimulatorManager::getManager()->getState(transition_vector->last().first->start_cell->currentIndex());
                    transition_vector->last().first->final_state = SimulatorManager::getManager()->getState(transition_vector->last().first->final_cell->currentIndex());
                    tr->start_cell->setEnabled(false);
                    tr->final_cell->setEnabled(false);
                    transition_vector->last().first->addWidget(transition_vector->last().second);

                    std::vector<State*>* vector_state_manager = new std::vector<State*>;
                    for (unsigned int i = 0; i < tr->getNbStates(); i++){
                        tr->neighbours[i]->second->setEnabled(false);
                        for (unsigned int j = 0; j < tr->neighbours[i]->second->value(); j++)
                            vector_state_manager->push_back(SimulatorManager::getManager()->getState(i));
                    }
                    Rule* rule = SimulatorManager::getManager()->createNewRule(*vector_state_manager, SimulatorManager::getManager()->getState(transition_vector->last().first->final_cell->currentIndex()));
                    transition_vector->last().first->start_state->addANewRule(rule);

                    QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
                    pair->first = add_transi;
                    pair->second = new QPushButton("Supprimer");
                    transition_vector->push_back(*pair);
                    transition_layout->addLayout(transition_vector->last().first);

                    QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(deleteRule()));
                }
                else
                    QMessageBox::warning(this, "ERREUR", "Cette règle existe déjà");
            }
        }
        // Si il y a pas encore de règle, il faut en mettre une première
        else{
            transition_vector->last().first->start_state = SimulatorManager::getManager()->getState(transition_vector->last().first->start_cell->currentIndex());
            transition_vector->last().first->final_state = SimulatorManager::getManager()->getState(transition_vector->last().first->final_cell->currentIndex());
            transition_vector->last().first->start_cell->setEnabled(false);
            transition_vector->last().first->final_cell->setEnabled(false);

            std::vector<State*>* vector_state_manager = new std::vector<State*>;
            transition_vector->last().first->addWidget(transition_vector->last().second);
            for (unsigned int i = 0; i < transition_vector->last().first->getNbStates(); i++){
                // On affiche le bouton Supprimer pour la règle précédent
                transition_vector->last().first->neighbours[i]->second->setEnabled(false);

                // On push le nombre de fois indiqué dans la box de l'état concerné
                for (unsigned int j = 0; j < transition_vector->last().first->neighbours[i]->second->value(); j++)
                    vector_state_manager->push_back(SimulatorManager::getManager()->getState(i));
            }
            Rule* rule = SimulatorManager::getManager()->createNewRule(*vector_state_manager, SimulatorManager::getManager()->getState(transition_vector->last().first->final_cell->currentIndex()));
            transition_vector->last().first->start_state->addANewRule(rule);

            QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
            pair->first = new Transition(state_list, state_list_number, neighbour_number);
            pair->second = new QPushButton("Supprimer");
            transition_vector->push_back(*pair);
            transition_layout->addLayout(transition_vector->last().first);

            QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(deleteRule()));
        }
    }
    // Si vide, on affiche la règle
    else{
        QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
        pair->first = new Transition(state_list, state_list_number, neighbour_number);
        pair->second = new QPushButton("Supprimer");
        transition_vector->push_back(*pair);
        transition_layout->addLayout(transition_vector->last().first);

        std::vector<State*>* vector_state_manager = new std::vector<State*>;
        for (unsigned int i = 0; i < transition_vector->last().first->getNbStates(); i++){
            // On affiche le bouton Supprimer pour la règle précédent
            for (unsigned int j = 0; j < transition_vector->last().first->neighbours[i]->second->value(); j++)
                vector_state_manager->push_back(SimulatorManager::getManager()->getState(i));
        }

        QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(deleteRule()));
    }
}

/**
 * \brief Vérifie que la règle de transition peut être insérée
 * \details Slot. Vérifie que la règle de transition peut être insérée si le nombre de voisins
 *          est valide et vérifie que la règle n'existe pas déjà
 */
bool TransitionInterface::addNewTransitionRuleValid(Transition* transi){
    Transition* ittr = nullptr;
    for (auto it = transition_vector->begin(); it != transition_vector->end(); ++it){
        ittr = it->first;
        bool spinboxequals = true;
        if ( ittr != transition_vector->last().first){
            for (unsigned int i = 0; i < transi->nb_states; i++){
                if (ittr->neighbours[i]->second->value() != transi->neighbours[i]->second->value()){
                    spinboxequals = false;
                    break;
                }
            }
        }
        else
            spinboxequals = false;
        if (ittr->start_cell->currentData() == transi->start_cell->currentData()
                && ittr->final_cell->currentData() == transi->final_cell->currentData() && spinboxequals)
            return false;
    }
    return true;
}

/**
 * \brief Supprime une règle
 * \details Slot. Supprime la règle sélectionnée
 */
void TransitionInterface::deleteRule(){
    QObject* sdr = sender();
    QPushButton* button = dynamic_cast<QPushButton*>(sdr);

    for (auto it = transition_vector->begin(); it != transition_vector->end(); it++) {
        if (it->second == button) {
            try {
                SimulatorManager::getManager()->removeRule(SimulatorManager::getManager()->getRule(it - transition_vector->begin()));
            } catch (SimulatorException error) {}

            delete it->first;
            delete it->second;
            transition_vector->erase(it);

            break;
        }
    }
}

// ================== SIGNAL ======================
/**
 * \brief Envoie d'un signal émis lors de la fermeture de la fenêtre du choix de transition
 * \param event     évènement de la fermeture de la fenêtre
 */
void TransitionInterface::closeEvent(QCloseEvent* event){
    emit close_transition_interface();
}

/**
 * \brief Destructeur de la fenêtre d'affichage des transitions
 */
TransitionInterface::~TransitionInterface(){
    delete transition_valid;
    delete transition_add_rule;
    delete transition_layout;
    delete title;
    delete main_layout;
}






Transition::Transition(State** state_list, unsigned int state_list_number, unsigned int neighbour_number,
                            unsigned int* spin_box_tab, State* state_start, State* state_final, bool modify) :
                            QHBoxLayout(), neighbours_nb(neighbour_number), nb_states(state_list_number),
                            state_list(state_list), start_state(state_start), final_state(state_final) {

    // Set Start State Layout
    start_layout = new QVBoxLayout;
    this->addLayout(start_layout);
    setStartState(start_layout, state_start, modify);

    setNeighboursNumber(state_list, state_list_number, neighbour_number, this, spin_box_tab, modify);

    final_layout = new QVBoxLayout;
    this->addLayout(final_layout);
    setFinalState(final_layout, state_final, modify);
}

void Transition::setStartState(QVBoxLayout* parent, State* start_state, bool modify){
    if (start_state == nullptr)
        start_state = state_list[0];

    start_label = new QLabel("Etat de départ");
    start_label->setAlignment(Qt::AlignBottom|Qt::AlignCenter);
    parent->addWidget(start_label);

    start_layout_combo = new QHBoxLayout;
    start_layout_combo->setEnabled(modify);
    parent->addLayout(start_layout_combo);
    start_cell = new QComboBox();
    start_layout_combo->addWidget(start_cell);
    start_cell->addItem(QString::fromStdString(start_state->getName()), QVariant(0));
    for (unsigned int i = 1; i < nb_states; i++){
        if (state_list[i]->getName() != start_state->getName())
            start_cell->addItem(QString::fromStdString(state_list[i]->getName()), QVariant(i));
        else
            i--;
    }

    // Cell with color of state depending on combobox chosen
    start_color = new QTableWidget(1, 1);
    start_layout_combo->addWidget(start_color);
    start_color->setFixedSize(10, 10);
    start_color->horizontalHeader()->setVisible(false);
    start_color->verticalHeader()->setVisible(false);
    start_color->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start_color->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start_color->setEnabled(modify);

    start_color->setEditTriggers(QAbstractItemView::NoEditTriggers);
    start_color->setItem(0, 0, new QTableWidgetItem(""));
    QColor color;
    color.setNamedColor(QString::fromStdString(start_state->getColor()));
    start_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));

    QObject::connect(start_color, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(preventSelection(QTableWidgetItem*)));
    QObject::connect(start_cell, SIGNAL(currentIndexChanged(int)), this, SLOT(changedStartState(int)));
}

void Transition::setNeighboursNumber(State** state_list, unsigned int state_list_number, unsigned int neighbour_number, QHBoxLayout* parent, unsigned int* spin_value, bool modify){
    if (spin_value == nullptr){
        spin_value = new unsigned int[nb_states];
        for (unsigned int i = 0; i < nb_states; i++)
            spin_value[i] = 0;
    }
    neighbours_layout = new QVBoxLayout*[state_list_number];
    neighbours = new QPair < State*, QSpinBox* >*[state_list_number];
    neighbours_label = new QLabel*[state_list_number];
    for (unsigned int i = 0; i < state_list_number; i++) {
        neighbours_layout[i] = new QVBoxLayout;
        parent->addLayout(neighbours_layout[i]);
        neighbours[i] = new QPair < State*, QSpinBox* >;
        neighbours[i]->first = new State(state_list[i]->getName());
        neighbours[i]->second = new QSpinBox;
        neighbours[i]->second->setEnabled(modify);
        neighbours_label[i] = new QLabel("Nombre de voisins à l'état:<br><center>"+QString::fromStdString(neighbours[i]->first->getName())+"</center>");
        neighbours_label[i]->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        neighbours_layout[i]->addWidget(neighbours_label[i]);
        neighbours[i]->second->setRange(0, neighbour_number);
        neighbours[i]->second->setValue(spin_value[i]);
        neighbours_layout[i]->addWidget(neighbours[i]->second);
    }
}

void Transition::setFinalState(QVBoxLayout* parent, State* final_state, bool modify){
    if (final_state == nullptr)
        final_state = state_list[0];
    final_label = new QLabel("Etat d'arrivée");
    final_label->setAlignment(Qt::AlignBottom|Qt::AlignCenter);
    parent->addWidget(final_label);

    final_layout_combo = new QHBoxLayout;
    final_layout_combo->setEnabled(modify);
    parent->addLayout(final_layout_combo);
    // ComboBox
    final_cell = new QComboBox();
    final_layout_combo->addWidget(final_cell);
    final_cell->addItem(QString::fromStdString(final_state->getName()), QVariant(0));
    for (unsigned int i = 1; i < nb_states; i++){
        if (state_list[i]->getName() != final_state->getName())
            final_cell->addItem(QString::fromStdString(state_list[i]->getName()), QVariant(i));
        else
            i--;
    }

    // Cell with color of state depending on combobox chosen
    final_color = new QTableWidget(1, 1);
    final_layout_combo->addWidget(final_color);
    final_color->setFixedSize(10, 10);
    final_color->horizontalHeader()->setVisible(false);
    final_color->verticalHeader()->setVisible(false);
    final_color->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    final_color->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    final_color->setEnabled(modify);

    final_color->setEditTriggers(QAbstractItemView::NoEditTriggers);
    final_color->setItem(0, 0, new QTableWidgetItem(""));
    QColor color;
    color.setNamedColor(QString::fromStdString(final_state->getColor()));
    final_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));

    QObject::connect(final_color, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(preventSelection(QTableWidgetItem*)));
    QObject::connect(final_cell, SIGNAL(currentIndexChanged(int)), this, SLOT(changedFinalState(int)));
}
/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/
void Transition::preventSelection(QTableWidgetItem* cell){
    cell->setSelected(false);
}

void Transition::changedStartState(int nb){
    QColor color;
    color.setNamedColor(QString::fromStdString(state_list[nb]->getColor()));
    start_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));
}

void Transition::changedFinalState(int nb){
    QColor color;
    color.setNamedColor(QString::fromStdString(state_list[nb]->getColor()));
    final_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));
}

Transition::~Transition(){
    delete final_color;
    delete final_label;
    delete final_cell;
    delete final_layout_combo;

    for (unsigned int i = 0; i < nb_states; i++) {
        delete neighbours_label[i];
        delete neighbours[i]->second;
    }
    delete[] neighbours_label;
    delete[] neighbours_layout;

    delete start_color;
    delete start_label;
    delete start_cell;
    delete start_layout_combo;

    delete final_layout;
    delete start_layout;
}
