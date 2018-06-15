#include "StateInterface.h"

#include <QColorDialog>

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
}

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
    color_layout->addWidget(state_color_label);

    color_button = new QPushButton("Choisir couleur");
    color_layout->addWidget(color_button);
    QObject::connect(color_button, SIGNAL(clicked()), this, SLOT(display_palette_color()));
}

// SLOTS

void StateInterface::display_palette_color(){
    QPalette color;
    QColor couleur = QColorDialog::getColor(Qt::black, color_button);
    color.setColor(QPalette::ButtonText, couleur);
    color_button->setPalette(couleur);
}
