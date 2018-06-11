#include "inclu_fich.h"
#include <iostream>

trans::trans(QWidget* parent): QWidget(parent), nbi(0) {
    setWindowTitle("Choix des règles");
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

    tabrules = new QHBoxLayout;

    //rules = new QVector < QPair< QVBoxLayout*, QVector < QSpinBox*> > >;
    for (unsigned int i = 0; i < 2; ++i){
        QPair<QVBoxLayout*, QVector<QSpinBox*> > *pair = new QPair<QVBoxLayout*, QVector<QSpinBox*> >;
        pair->first = new QVBoxLayout;
        pair->second = QVector<QSpinBox*>();
        rules.push_back(pair);
        tabrules->addLayout(pair->first);
    }
    auto it = rules.begin();
    //auto it = rules.begin();
    for (unsigned int i = 0; i < 2; ++i){
        addtransitype(*it, i);
        ++it;
    }

    t1->addLayout(tabrules);
    titre->addLayout(t1);

    valid = new QPushButton("Valider");
    titre->addWidget(valid);

    QObject::connect(valid, SIGNAL(clicked()), this, SLOT(validation()));
    setLayout(titre);
}


void trans::validation(){
    this->close();
}


void trans::addtransitype(QPair< QVBoxLayout*, QVector < QSpinBox*> >* it, int i){
    QLabel* nbneightitle = new QLabel;
    nbneightitle->setAlignment(Qt::AlignCenter);
    if (!i)
        nbneightitle->setText("Nombre de voisins morts");
    else if (i == 1)
        nbneightitle->setText("Nombre de voisins vivants");
    //it->first->addLayout();
    it->first->addWidget(nbneightitle);
    //tabrules->addLayout(it->first); //déjà fait dans le constructeur

    addnewtransi(*it, i);
}


void trans::addnewtransi(QPair< QVBoxLayout*, QVector < QSpinBox*> > it, int i){
    QSpinBox* nbpt = new QSpinBox;
    nbpt->setRange(-1,8);
    nbpt->setValue(-1);
    //nb.push_back(nbpt);
    //QMessageBox::warning(this, "Impossible", QString::number(nbi));
    /*auto ite = nb.begin();
    for (unsigned int j = 0; j < i; j++)
        ++ite;*/
    //(*ite).second.push_back(nbpt);
    it.second.push_back(nbpt);
    it.first->addWidget(nbpt);
    add = new QPushButton("ajouter nouvelle règle");
    it.first->addWidget(add);

    //add->clicked();
        //QMessageBox::warning(this, "Impossible", "Entrez une valeur valide !<br>La règle doit contenir une valeur positive ou nulle!");

    QObject::connect(add, SIGNAL(clicked()), it, SLOT(addtransi()));
}


void trans::addtransi(){
    if (this != -1)
        addnewtransi(pair, i);
    else
        QMessageBox::warning(this, "Impossible", "Entrez une valeur valide !<br>La règle doit contenir une valeur positive ou nulle!");
}


