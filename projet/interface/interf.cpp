#include "inclu_fich.h"
#include <iostream>
#include <vector>

using namespace std;

trans::trans(QWidget* parent): QWidget(parent) {
    setWindowTitle("Choix des règles");
    titre = new QVBoxLayout;
    QLabel* texte = new QLabel;
    titre->addWidget(texte);
    texte->setText("Choix des transitions");
    texte->setAlignment(Qt::AlignCenter);


    t1 = new QVBoxLayout;     //pour transition sur 2 états statique
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
    }
*/
    t1->addLayout(tabrules);
    titre->addLayout(t1);

    /*containerRule = new vector <QHBoxLayout*>;
    containerRule->push_back(new QHBoxLayout);*/

    valid = new QPushButton("Valider");
    titre->addWidget(valid);

    //gridtransition();

    QObject::connect(valid, SIGNAL(clicked()), this, SLOT(validation()));

    setLayout(titre);
}


void trans::validation(){
    this->close();
}

/*void trans::addtransition(int i){     //pour transition sur 2 états statique
    rulesvalue[nbrulesvalue[i]+10*i] = new QSpinBox;
    rulesvalue[nbrulesvalue[i]+10*i]->setRange(-1,8);
    rulesvalue[nbrulesvalue[i]+10*i]->setValue(-1);
    rules[i]->addWidget(rulesvalue[nbrulesvalue[i]+10*i]);
    rulesvalid[nbrulesvalue[i]+10*i] = new QPushButton("Valider");
    rulesvalid[nbrulesvalue[i]+10*i]->setObjectName(QString::number(i));
    QMessageBox::warning(this, "ok", (rulesvalid[nbrulesvalue[i]+i*10]->objectName()));
    rules[i]->addWidget(rulesvalid[nbrulesvalue[i]+10*i]);
    QObject::connect(rulesvalid[nbrulesvalue[i]+10*i], SIGNAL(clicked()), this, SLOT(slot_addtransition()));
    nbrulesvalue[i]++;
}


void trans::slot_addtransition(){
    QObject* senderObj = sender();
    QPushButton* qp = qobject_cast<QPushButton*>(senderObj);
    //qp->setEnabled(false);
    QString senderObjName = senderObj->objectName();
    QMessageBox::warning(this, "ok", QString::number(rulesvalue[0]->value()));
    if (senderObjName == 0){
//        if (rulesvalue[nbrulesvalue[0] - 1]->value() != -1)
//            addtransition(0);
//        else
//            QMessageBox::warning(this, "Impossible", "Entrez une valeur positive ou nulle pour la règle");
        QMessageBox::warning(this, "ok", rulesvalid[nbrulesvalue[0]]->objectName());
        QMessageBox::warning(this, "ok", QString::number(rulesvalue[nbrulesvalue[0] - 1]->value()));
    }
    else{
//        if (rulesvalue[nbrulesvalue[1] - 1]->value() != -1)
//            addtransition(1);
//        else
//            QMessageBox::warning(this, "Impossible", "Entrez une valeur positive ou nulle pour la règle");
        QMessageBox::warning(this, "ok", rulesvalid[nbrulesvalue[1]+10-1]->objectName());
        QMessageBox::warning(this, "ok", QString::number(rulesvalue[nbrulesvalue[1] - 1]->value()));
    }
}*/


/*void trans::gridtransition(){
    QHBoxLayout* qh = new QHBoxLayout;
    grid = new QTableWidget(9, 9);
    grid->setObjectName("grid");
    grid->setFixedSize(50, 50);
    grid->horizontalHeader()->setVisible(false);
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (unsigned int i = 0; i < 9; i++){
        grid->setColumnWidth(i, 50/3);
        grid->setRowHeight(i, 50/3);
        for (unsigned int j = 0; j < 9; j++){
            grid->setItem(j, i, new QTableWidgetItem(""));
        }
    }

    QObject::connect(grid, SIGNAL(cellClicked(int,int)), this, SLOT(clickcell(int, int)));

    validGrid = new QPushButton("Valider");
    QObject::connect(validGrid, SIGNAL(clicked()), this, SLOT(validGrid_clicked()));

    qh->addWidget(grid);
    qh->addWidget(validGrid);
    containerRule->push_back(qh);
    titre->addLayout(containerRule->back());
}

void trans::clickcell(int i, int j){
    if (grid->item(i,j)->backgroundColor()== Qt::black)
        grid->item(i,j)->setBackgroundColor(Qt::white);
    else
        grid->item(i,j)->setBackgroundColor(Qt::black);
}

void trans::validGrid_clicked(){
    QWidget* gr1 = containerRule->back()->itemAt(0)->widget();
    //QTableWidget* gr = containerRule->last()->findChild<QTableWidget*>(QString("grid"));
    //QTableWidget* gr = qobject_cast<QTableWidget*>(gr1);
    //QTableWidget* gr = qobject_cast<QTableWidget*>(containerRule->last()->findChild<QTableWidget*>());
//    if (gr == 0)
//        QMessageBox::warning(this, "erreur", "attention");
//    containerRule->last()->addWidget(gr);
    //containerRule->last()->addWidget(gr1);
    bool cont = true;
    for (vector<QHBoxLayout*>::iterator it = containerRule->begin(); it != containerRule->end(); ++it ){
        bool empty = (*it)->children().empty();
        if ((*it)->itemAt(0)->widget()){
            cout << "aaaaaaaaaaaaaaaaaaaa" << endl;
        }
//        if ((*it)->itemAt(i)->widget() == gr1){
//            cont = false;
//            break;
//        }
    }
    if (cont)
        gridtransition();
    else
        QMessageBox::warning(this, "Impossible", "La règle existe déjà !");
}*/
