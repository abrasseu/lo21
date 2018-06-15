#include "StateInterface.h"

StateInterface::StateInterface(): QHBoxLayout() {
    // Layout contenant une règle d'état entière
    state_layout = new QHBoxLayout;
    this->addLayout(state_layout);
    state_layout->setAlignment(Qt::AlignTop);

    // Layout contenant les widgets
    name_layout = new QVBoxLayout;
    state_layout->addLayout(name_layout);
    setNameLayout(name_layout);

    color_layout = new QVBoxLayout;
    state_layout->addLayout(color_layout);
    setColorLayout(color_layout);

    state_delete = new QPushButton("Supprimer");
    state_layout->addWidget(state_delete);
}

//StateInterface* StateInterface::StateInterface(const StateInterface& st){
//    return st;
//}

void StateInterface::setNameLayout(QBoxLayout* parent){
    name_layout = new QVBoxLayout;
    parent->addLayout(name_layout);

    state_name_label = new QLabel("Nom de l'état :");
    name_layout->addWidget(state_name_label);

    state_name = new QLineEdit;
    name_layout->addWidget(state_name);
}

void StateInterface::setColorLayout(QBoxLayout* parent){
    color_layout = new QVBoxLayout;
    parent->addLayout(color_layout);

    state_color_label = new QLabel("Couleur de l'état :");
    name_layout->addWidget(state_color_label);

    QWidget* widg = new QWidget;
    name_layout->addWidget(widg);
//    state_color = new QPalette;
    QPalette* pal = widg->palette();
    widg->setPalette(pal);
}
