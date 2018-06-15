#include "TransitionInterface.h"

TransitionInterface::TransitionInterface(State** state_list, unsigned int state_list_number, unsigned int neighbour_number)
    : QWidget(), state_list(state_list), state_list_number(state_list_number), neighbour_number(neighbour_number) {

    setWindowTitle("Transitions");
    QVBoxLayout* princ = new QVBoxLayout;
    setLayout(princ);

    // Set Main Layout
    QScrollArea *scroll = new QScrollArea;
    princ->addWidget(scroll);
    scroll->setWidgetResizable(false);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setFixedSize(700,500);
    scroll->verticalScrollBar();
    scroll->adjustSize();
    main_layout = new QVBoxLayout;
    scroll->setLayout(main_layout);
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
    // On test si le nombre de voisins dans la règle n'est pas supérieur au nombre de voisin maximum
    if (!transition_vector->empty()){
        // Si il y a déjà au moins 1 règle
        if (transition_vector->size() != 1){
            Transition* tr = transition_vector->last();
            unsigned int sum = 0;
            for (unsigned int i = 0; i < tr->getNbStates(); i++)
                sum += tr->neighbours[i]->second->value();
            if (sum > tr->getNeighboursNb()){
                QMessageBox::warning(this, "ERREUR", "Le nombre de voisins est supérieur au nombre de voisins total possibles");
                return;
            }
            else{
                Transition* add_transi = new Transition(state_list, state_list_number, neighbour_number);
                if (add_new_transition_rule_valid(tr)){
                    tr->start_cell->setEnabled(false);
                    tr->final_cell->setEnabled(false);
                    for (unsigned int i = 0; i < tr->getNbStates(); i++)
                        tr->neighbours[i]->second->setEnabled(false);
                    transition_vector->push_back(add_transi);
                    transition_layout->addLayout(transition_vector->last());
                }
                else
                    QMessageBox::warning(this, "ERREUR", "Cette règle existe déjà");
            }
        }
        // Si il y a pas encore de règle, il faut en mettre une première
        else{
            transition_vector->last()->start_cell->setEnabled(false);
            transition_vector->last()->final_cell->setEnabled(false);
            for (unsigned int i = 0; i < transition_vector->last()->getNbStates(); i++)
                transition_vector->last()->neighbours[i]->second->setEnabled(false);
            transition_vector->push_back(new Transition(state_list, state_list_number, neighbour_number));
            transition_layout->addLayout(transition_vector->last());
        }
    }
    else{
        transition_vector->push_back(new Transition(state_list, state_list_number, neighbour_number));
        transition_layout->addLayout(transition_vector->last());
    }
}

bool TransitionInterface::add_new_transition_rule_valid(Transition* transi){
    for (Transition** it = transition_vector->begin(); it != transition_vector->end(); ++it){
        bool spinboxequals = true;
        if ((*it) != transition_vector->last()){
            for (unsigned int i = 0; i < transi->nb_states; i++){
                if ((*it)->neighbours[i]->second->value() != transi->neighbours[i]->second->value()){
                    spinboxequals = false;
                    break;
                }
            }
        }
        else
            spinboxequals = false;
        if ((*it)->start_cell->currentData() == transi->start_cell->currentData()
                && (*it)->final_cell->currentData() == transi->final_cell->currentData() && spinboxequals)
            return false;
    }
    return true;
}









Transition::Transition(State** state_list, unsigned int state_list_number, unsigned int neighbour_number)
    : QHBoxLayout(), neighbours_nb(neighbour_number), nb_states(state_list_number), state_list(state_list) {
    // "Simulateur" à 2 cases pour pouvoir utiliser la fonction incrementState

    // Set Start State Layout
    start_layout = new QVBoxLayout;
    this->addLayout(start_layout);
    setStartState(start_layout);

    setNeighboursNumber(state_list, state_list_number, neighbour_number, this);

    final_layout = new QVBoxLayout;
    this->addLayout(final_layout);
    setFinalState(final_layout);

    valid_layout = new QVBoxLayout;
    this->addLayout(valid_layout);
    setValidLayout(valid_layout);
}


void Transition::setStartState(QVBoxLayout* parent){
    start_label = new QLabel("Etat de départ");
    parent->addWidget(start_label);

    start_layout_combo = new QHBoxLayout;
    parent->addLayout(start_layout_combo);
    start_cell = new QComboBox();
    start_layout_combo->addWidget(start_cell);
    for (unsigned int i =0; i < nb_states; i++){
        start_cell->addItem(QString::fromStdString(state_list[i]->getName()), QVariant(i));
    }

    // Cell with color of state depending on combobox chosen
    start_color = new QTableWidget(1, 1);
    start_layout_combo->addWidget(start_color);
    start_color->setFixedSize(10, 10);
    start_color->horizontalHeader()->setVisible(false);
    start_color->verticalHeader()->setVisible(false);
    start_color->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start_color->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    start_color->setEditTriggers(QAbstractItemView::NoEditTriggers);
    start_color->setItem(0, 0, new QTableWidgetItem(""));
    QColor color;
    color.setNamedColor(QString::fromStdString(state_list[0]->getColor()));
    start_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));

    QObject::connect(start_color, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(preventSelection(QTableWidgetItem*)));
    QObject::connect(start_cell, SIGNAL(currentIndexChanged(int)), this, SLOT(changedStartState(int)));
}

void Transition::setNeighboursNumber(State** state_list, unsigned int state_list_number, unsigned int neighbour_number, QHBoxLayout* parent){
    neighbours_layout = new QVBoxLayout*[state_list_number];
    neighbours = new QPair < State*, QSpinBox* >*[state_list_number];
    neighbours_label = new QLabel*[state_list_number];
    for (unsigned int i = 0; i < state_list_number; i++) {
        neighbours_layout[i] = new QVBoxLayout;
        parent->addLayout(neighbours_layout[i]);
        neighbours_label[i] = new QLabel("Nombre de voisins à l'état:<br><center>"+QString::number(i)+"</center>");
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

    final_layout_combo = new QHBoxLayout;
    parent->addLayout(final_layout_combo);
    // ComboBox
    final_cell = new QComboBox();
    final_layout_combo->addWidget(final_cell);
    for (unsigned int i =0; i < nb_states; i++){
        final_cell->addItem(QString::fromStdString(state_list[i]->getName()), QVariant(i));
    }

    // Cell with color of state depending on combobox chosen
    final_color = new QTableWidget(1, 1);
    final_layout_combo->addWidget(final_color);
    final_color->setFixedSize(10, 10);
    final_color->horizontalHeader()->setVisible(false);
    final_color->verticalHeader()->setVisible(false);
    final_color->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    final_color->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    final_color->setEditTriggers(QAbstractItemView::NoEditTriggers);
    final_color->setItem(0, 0, new QTableWidgetItem(""));
    QColor color;
    color.setNamedColor(QString::fromStdString(state_list[0]->getColor()));
    final_color->item(0,0)->setBackground(QBrush(color, Qt::SolidPattern));

    QObject::connect(final_color, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(preventSelection(QTableWidgetItem*)));
    QObject::connect(final_cell, SIGNAL(currentIndexChanged(int)), this, SLOT(changedFinalState(int)));
}

void Transition::setValidLayout(QBoxLayout* parent){
    valid_rule = new QPushButton("Valider");
    modify_rule = new QPushButton("Modifier");
    parent->addWidget(valid_rule);
    parent->addWidget(modify_rule);

    QObject::connect(valid_rule, SIGNAL(clicked()), this, SLOT(validRuleClick()));
    QObject::connect(modify_rule, SIGNAL(clicked()), this, SLOT(modifyRuleClick()));
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

void Transition::validRuleClick(){
    valid_rule->setEnabled(false);
    modify_rule->setEnabled(true);
}

void Transition::modifyRuleClick(){
    valid_rule->setEnabled(true);
    modify_rule->setEnabled(false);
    modifyRule(sender());
}
