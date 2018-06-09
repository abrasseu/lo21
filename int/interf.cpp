#include "inclu_fich.h"

trans::trans(): QWidget(){
    titre = new QVBoxLayout;
    QLabel* texte = new QLabel;
    titre->addWidget(texte);
    texte->setText("Choix des transitions");
    texte->setAlignment(Qt::AlignCenter);


    t1 = new QVBoxLayout;
    transition = new QHBoxLayout;
    lab = new QLabel;
    lab->setText("Si la cellule est dans l'état ");
    etatcell = new QSpinBox;
    etatcell->setRange(0,1);

    label = new QLabel;
    label->setText(", alors il lui faut le nombre de voisins suivant pour aller dans l'état ");
    etatcell2 = new QSpinBox;
    etatcell2->setRange(0,1);

    transition->addWidget(lab);
    transition->addWidget(etatcell);
    transition->addWidget(label);
    transition->addWidget(etatcell2);
    t1->addLayout(transition);

    nbvois1 = new QHBoxLayout;
    nbvoislab = new QLabel;
    nbvoislab->setText("Nomre de voisins: ");
    QComboBox* nbvoisstate = new QComboBox;
    nbvoisstate->addItem("Mort", QVariant(0));
    nbvoisstate->addItem("Vivant", QVariant(1));


    nbvois1->addWidget(nbvoislab);
    nbvois1->addWidget(nbvoisstate);

    addnewtransi();

    titre->addLayout(t1);
    setLayout(titre);

}

void trans::addnewtransi(){
    QSpinBox* nb11 = new QSpinBox;
    nb11->setRange(0,8);
    nbvois1->addWidget(nb11);

    QPushButton* add = new QPushButton;
    add->setText("+");
    nbvois1->addWidget(add);
    t1->addLayout(nbvois1);

    QObject::connect(add, SIGNAL(clicked()), this, SLOT(addtransi()));
}

void trans::addtransi(){
    addnewtransi();
}
