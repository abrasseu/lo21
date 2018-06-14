#include "TransitionInterface.h"

TransitionInterface::TransitionInterface(State** state_list, unsigned int state_list_number, unsigned int neighbour_number)
    : QWidget(), state_list(state_list), state_list_number(state_list_number), neighbour_number(neighbour_number) {

    setWindowTitle("Transitions");

    // Set Main Layout
    main_layout = new QVBoxLayout;
    setLayout(main_layout);

    title = new QLabel("Choisissez les règles de transition de l'automate");
    main_layout->addWidget(title);
    title->setAlignment(Qt::AlignTop);
    title->setAlignment(Qt::AlignHCenter);


    // Set Transition Layout
    transition_layout = new QVBoxLayout;
    main_layout->addLayout(transition_layout);

    transition_vector = new QVector< Transition *>;
    add_new_transition_rule();

    transition_add_rule = new QPushButton("Ajouter une nouvelle règle");
    transition_valid = new QPushButton("Valider");
    main_layout->addWidget(transition_add_rule);
    main_layout->addWidget(transition_valid);


    QObject::connect(transition_add_rule, SIGNAL(clicked()), this, SLOT(add_new_transition_rule()));
    QObject::connect(transition_valid, SIGNAL(clicked()), this, SLOT(validate_rules()));
}

/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/

void TransitionInterface::validate_rules(){
    this->close();
}

void TransitionInterface::add_new_transition_rule(){
    transition_vector->push_back(new Transition(state_list, state_list_number, neighbour_number));
    transition_layout->addLayout(transition_vector->last());
}


/*void TransitionInterface::add_new_transition_rule(){  // a tester, non fonctionnel !!
    Transition* tr = transition_vector->last();
    if (tr != 0){
        unsigned int sum = 0;
        for (unsigned int i = 0; i < tr->getNbStates(); i++)
            sum += tr->neighbours[i]->second->value();
        if (sum > tr->getNeighboursNb())
            QMessageBox::warning(this, "ERREUR", "Le nombre de voisins est supérieur au nombre de voisins totaux possibles");
        else{
            transition_vector->push_back(new Transition(state_list, state_list_number, neighbour_number));
            transition_layout->addLayout(transition_vector->last());
        }
    }
    else{
        transition_vector->push_back(new Transition(state_list, state_list_number, neighbour_number));
        transition_layout->addLayout(transition_vector->last());
    }
}*/




Transition::Transition(State** state_list, unsigned int state_list_number, unsigned int neighbour_number)
    : QHBoxLayout(), neighbours_nb(state_list_number), nb_states(state_list_number) {
    // Set Start State Layout
    start_layout = new QVBoxLayout;
    this->addLayout(start_layout);
    setStartState(start_layout);

    setNeighboursNumber(state_list, state_list_number, neighbour_number, this);

    final_layout = new QVBoxLayout;
    this->addLayout(final_layout);
    setFinalState(final_layout);
}


void Transition::setStartState(QVBoxLayout* parent){
    start_label = new QLabel("Etat de départ");
    parent->addWidget(start_label);
    start_cell = new QTableWidget(1, 1);
    parent->addWidget(start_cell);
    start_cell->setFixedSize(50, 50);
    start_cell->horizontalHeader()->setVisible(false);
    start_cell->verticalHeader()->setVisible(false);
    start_cell->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start_cell->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    start_cell->setEditTriggers(QAbstractItemView::NoEditTriggers);
    start_cell->setColumnWidth(0, 50);
    start_cell->setRowHeight(0, 50);
    start_cell->setItem(0, 0, new QTableWidgetItem(""));

    QObject::connect(start_cell, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(rotateCellState(QTableWidgetItem*)));
}

void Transition::setNeighboursNumber(State** state_list, unsigned int state_list_number, unsigned int neighbour_number, QHBoxLayout* parent){
    neighbours = new QPair < State*, QSpinBox* >*[state_list_number];
    neighbours_layout = new QVBoxLayout*[state_list_number];
    neighbours_label = new QLabel*[state_list_number];
    for (unsigned int i = 0; i < state_list_number; i++) {
        neighbours_layout[i] = new QVBoxLayout;
        parent->addLayout(neighbours_layout[i]);
        neighbours_label[i] = new QLabel("Nombre de voisins à l'état:<br>"+QString::number(i));
        neighbours_layout[i]->addWidget(neighbours_label[i]);
        neighbours[i] = new QPair < State*, QSpinBox* >;
        neighbours[i]->first = new State(state_list[i]->getName());
        neighbours[i]->second = new QSpinBox;
        neighbours[i]->second->setRange(0, neighbour_number);
        neighbours[i]->second->setValue(0);
        neighbours_layout[i]->addWidget(neighbours[i]->second);
    }
}

void Transition::setFinalState(QVBoxLayout* parent){
    final_label = new QLabel("Etat d'arrivée");
    parent->addWidget(final_label);
    final_cell = new QTableWidget(1, 1);
    parent->addWidget(final_cell);
    final_cell->setFixedSize(50, 50);
    final_cell->horizontalHeader()->setVisible(false);
    final_cell->verticalHeader()->setVisible(false);
    final_cell->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    final_cell->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    final_cell->setEditTriggers(QAbstractItemView::NoEditTriggers);
    final_cell->setColumnWidth(0, 50);
    final_cell->setRowHeight(0, 50);
    final_cell->setItem(0, 0, new QTableWidgetItem(""));

    QObject::connect(final_cell, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(rotateCellState(QTableWidgetItem*)));
}

/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/
