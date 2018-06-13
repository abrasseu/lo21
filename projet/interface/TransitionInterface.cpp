#include "TransitionInterface.h"

TransitionInterface::TransitionInterface() : QWidget() {
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

    transition_valid = new QPushButton("Valider");
    main_layout->addWidget(transition_valid);
}
