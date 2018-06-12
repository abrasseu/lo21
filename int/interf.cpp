#include "inclu_fich.h"
#include <iostream>

trans::trans(QWidget* parent): QWidget(parent) {
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

    /*for (unsigned int i = 0; i < 2; i++){
        nbrulesvalue[i] = 0;
        rules[i] = new QVBoxLayout;
        rulestitle[i] = new QLabel;
        if (!i)
            rulestitle[i]->setText("Nombre de voisins morts");
        else if (i == 1)
            rulestitle[i]->setText("Nombre de voisins vivants");
        rules[i]->addWidget(rulestitle[i]);
        addtransition(i);
        tabrules->addLayout(rules[i]);
    }*/



    //rules = new QVector < QPair< QVBoxLayout*, QVector < QSpinBox*> > >;
    for (unsigned int i = 0; i < 2; ++i){
        QPair<QVBoxLayout*, QVector<QPair < QSpinBox*, QPushButton* > > > *pair = new QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >;
        pair->first = new QVBoxLayout;
        pair->second = QVector< QPair <QSpinBox*, QPushButton*> >();
        rules.push_back(pair);
        tabrules->addLayout(pair->first);
    }
    auto it = rules.begin();
    //auto it = rules.begin();
    for (unsigned int i = 0; i < 2; ++i){
        addtransitype(*it);
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

/*void trans::addtransition(int i){
    rulesvalue[nbrulesvalue[i]] = new QSpinBox;
    rulesvalue[nbrulesvalue[i]]->setRange(-1,8);
    rulesvalue[nbrulesvalue[i]]->setValue(-1);
    rules[i]->addWidget(rulesvalue[nbrulesvalue[i]]);
    rulesvalid[nbrulesvalue[i]] = new QPushButton("Valider");
    rulesvalid[nbrulesvalue[i]]->setObjectName(QString::number(i));
    rules[i]->addWidget(rulesvalid[nbrulesvalue[i]]);
    QObject::connect(rulesvalid[nbrulesvalue[i]], SIGNAL(clicked()), this, SLOT(slot_addtransition()));
    nbrulesvalue[i]++;
}

void trans::slot_addtransition(){
    QObject* senderObj = sender();
    QPushButton* qp = qobject_cast<QPushButton*>(senderObj);
    qp->setEnabled(false);
    QString senderObjName = senderObj->objectName();
    if (senderObjName == "0")
        addtransition(0);
    else
        addtransition(1);
}*/


void trans::addtransitype(QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >* it){
    QLabel* nbneightitle = new QLabel;
    nbneightitle->setAlignment(Qt::AlignCenter);
    /*if (!i)
        nbneightitle->setText("Nombre de voisins morts");
    else if (i == 1)*/
        nbneightitle->setText("Nombre de voisins vivants");
    //it->first->addLayout();
    it->first->addWidget(nbneightitle);
    //tabrules->addLayout(it->first); //déjà fait dans le constructeur

    addnewtransi(*it);
}


void trans::addnewtransi(QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > > it){
    QPair < QSpinBox*, QPushButton* >* nbpt = new QPair<QSpinBox*, QPushButton*>;
    nbpt->first = new QSpinBox;
    nbpt->second = new QPushButton;
    nbpt->first->setRange(-1,8);
    nbpt->first->setValue(-1);
    nbpt->second->setText("ajouter nouvelle règle");
    //nb.push_back(nbpt);
    //QMessageBox::warning(this, "Impossible", QString::number(nbi));
    /*auto ite = nb.begin();
    for (unsigned int j = 0; j < i; j++)
        ++ite;*/
    //(*ite).second.push_back(nbpt);
    it.second.push_back(*nbpt);
    it.second.push_back(*nbpt);
    it.first->addWidget(nbpt->first);
    it.first->addWidget(nbpt->second);

    //add->clicked();
        //QMessageBox::warning(this, "Impossible", "Entrez une valeur valide !<br>La règle doit contenir une valeur positive ou nulle!");
    //QPair<QSpinBox*, QPushButton*> qp = it.second.last();
    QObject::connect(it.second.last().second, SIGNAL(clicked()), this, SLOT(addtransi()));
}


void trans::addtransi(){
    QObject* send = sender();
    QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >* sendpair = qobject_cast<QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >*>(send);
    //QPushButton* sendpush = qobject_cast<QPushButton*>(sendpair->second.last().first);
    QSpinBox* sendspin = qobject_cast<QSpinBox*>(sendpair->second.last().second);
    if (sendspin->value() != -1)
        addnewtransi(*sendpair);
    else
        QMessageBox::warning(this, "Impossible", "Entrez une valeur valide !<br>La règle doit contenir une valeur positive ou nulle!");
}


