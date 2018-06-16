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

    transition_vector = new QVector< QPair< Transition *, QPushButton* > >;
//    displayExistingRules();
    addNewTransitionRule();

    transition_add_rule = new QPushButton("Ajouter une nouvelle règle");
    transition_valid = new QPushButton("Valider");
    main_layout->addWidget(transition_add_rule);
    main_layout->addWidget(transition_valid);


    QObject::connect(transition_add_rule, SIGNAL(clicked()), this, SLOT(addNewTransitionRule()));
    QObject::connect(transition_valid, SIGNAL(clicked()), this, SLOT(validateRules()));
}

/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/
void TransitionInterface::validateRules(){
    this->close();
}

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
                    tr->start_cell->setEnabled(false);
                    tr->final_cell->setEnabled(false);
                    // On affiche le bouton modifier pour la règle précédente
                    transition_vector->last().first->addWidget(transition_vector->last().second);
                    for (unsigned int i = 0; i < tr->getNbStates(); i++)
                        tr->neighbours[i]->second->setEnabled(false);
                    QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
                    pair->first = add_transi;
                    pair->second = new QPushButton("Modifier");
                    transition_vector->push_back(*pair);
                    transition_layout->addLayout(transition_vector->last().first);

                    QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(modifyPreviousRule()));
                }
                else
                    QMessageBox::warning(this, "ERREUR", "Cette règle existe déjà");
            }
        }
        // Si il y a pas encore de règle, il faut en mettre une première
        else{
            transition_vector->last().first->start_cell->setEnabled(false);
            transition_vector->last().first->final_cell->setEnabled(false);
            // On affiche le bouton modifier pour la règle précédente
            transition_vector->last().first->addWidget(transition_vector->last().second);
            for (unsigned int i = 0; i < transition_vector->last().first->getNbStates(); i++)
                transition_vector->last().first->neighbours[i]->second->setEnabled(false);
            QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
            pair->first = new Transition(state_list, state_list_number, neighbour_number);
            pair->second = new QPushButton("Modifier");
            transition_vector->push_back(*pair);
            transition_layout->addLayout(transition_vector->last().first);

            QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(modifyPreviousRule()));
        }
    }
    // Si vide, on affiche la règle
    else{
        QPair<Transition*, QPushButton*>* pair = new QPair < Transition*, QPushButton* >;
        pair->first = new Transition(state_list, state_list_number, neighbour_number);
        pair->second = new QPushButton("Modifier");
        transition_vector->push_back(*pair);
        transition_layout->addLayout(transition_vector->last().first);

        QObject::connect(pair->second, SIGNAL(clicked()), this, SLOT(modifyPreviousRule()));
    }
}

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

void TransitionInterface::modifyPreviousRule(){
    QObject* sdr = sender();
    QPushButton* qp = dynamic_cast<QPushButton*>(sdr);
    for (auto it = transition_vector->begin(); it != transition_vector->end(); ++it){
        if (it->second == qp){
            if (qp->text() == QString::fromStdString("Modifier")){
                qp->setText(QString::fromStdString("Valider"));
                it->first->start_cell->setEnabled(true);
                it->first->final_cell->setEnabled(true);
                for (unsigned int i = 0; i < it->first->nb_states; i++)
                    it->first->neighbours[i]->second->setEnabled(true);
            }
            // Validation de la modification
            else{
                qp->setText(QString::fromStdString("Modifier"));
                it->first->start_cell->setEnabled(false);
                it->first->final_cell->setEnabled(false);
                for (unsigned int i = 0; i < it->first->nb_states; i++)
                    it->first->neighbours[i]->second->setEnabled(false);
                // Insérer le code pour modifier la règle du simulateur
            }
        }
    }
}

//void TransitionInterface::displayExistingRules(){
//    State** list_states;
//    for (unsigned int i = 0; i < nb_state; i++){
//        std::vector<Rule*>::const_iterator it = list_states[i]->getRules();
//        it.
//        for (auto it = list_states[i]->getRules().begin(); it != list_states[i]->getRules().begin(); ++it)
//    }
//}

void TransitionInterface::closeEvent(QCloseEvent* event){
    emit close_transition_interface();
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

