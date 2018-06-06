#include "inclu_fich.h"

unsigned int inter_1D::dimension=25;

inter_1D::inter_1D(QWidget* parent): QWidget(parent){
    top=new QVBoxLayout;
    buttons=new QHBoxLayout;
    quit=new QPushButton("Quitter");
    retur=new QPushButton("Retour au menu principal");
    buttons->addWidget(quit);
    buttons->addWidget(retur);
    top->addLayout(buttons);

    num=new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    numl=new QLabel("Numéro");
    numc=new QHBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc=new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator=new QIntValidator(this);
    zeroOneValidator->setRange(0,1); // valeurs autorisées : 0 ou 1

    for (unsigned int i=0; i<8; i++){
        numeroBit[i]=new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);	// Pour rentrer seulement 0 ou 1
        numeroBitl[i]=new QLabel;
        bitc[i]=new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);
    }

    numeroBitl[0]->setText("111");
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[7]->setText("000");	/*setLayout(numeroc);*/

    couche=new QVBoxLayout;
    couche->addLayout(top);
    couche->addLayout(numeroc);
    depart=new QTableWidget(1, dimension, this);
    couche->addWidget(depart);
    setLayout(couche);

    unsigned int taille=25;
    depart->setFixedSize(dimension*taille, taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (unsigned int i=0; i<dimension; i++){
        depart->setColumnWidth(i,taille);
        depart->setItem(0, i, new QTableWidgetItem("0"));
    }

    //connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int))); // dès qu'une valeur est
                                                                // modifiée, on fait appel à la fonction

    /*for (unsigned int i=0; i<8; i++){
        connect(numeroBit[i], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(QString)));
    }*/

    simulation=new QPushButton("Simulation", this);
    couche->addWidget(simulation);
    //connect(simulation, SIGNAL(clicked()), this, SLOT(faireSimulation()));

    etats=new QTableWidget(dimension, dimension, this);
    etats->setFixedSize(dimension*taille, dimension*taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (unsigned int i=0; i<dimension; i++){
        etats->setColumnWidth(i, taille);
        etats->setRowHeight(i, taille);
        for (unsigned int j=0; j<dimension; j++){
            etats->setItem(j, i, new QTableWidgetItem(""));
        }
    }
    couche->addWidget(etats);

    QObject::connect(this->quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->retur, SIGNAL(clicked()), this, SLOT(backtomain()));

}

/*void AutoCell::faireSimulation(){
    Etat e(dimension);
    for (unsigned int i=0; i<dimension; i++)
        if (depart->item(0, i)->text()!="0")
            e.setCellule(i, true);
    const Automate& A=AutomateManager::getInstance().getAutomate(num->value());//getAutomateManager //(au lieu de getInstance)
    Simulateur S(A,e);
    for (unsigned int i=0; i<dimension; i++){
        S.Next();
        const Etat& d=S.dernier();
        for (unsigned int j=0; j<dimension; j++){
            if (d.getCellule(j)){
                etats->item(i,j)->setBackgroundColor("black");
            }else{
                etats->item(i,j)->setBackgroundColor("white");
            }
        }
    }
}*/

void inter_1D::backtomain()
{
    this->close();
    qt_designer* q=new qt_designer;
    q->show();
}

void inter_1D::cellActivation(const QModelIndex& index){
    if (depart->item(0, index.column())->text()==""){ // cellule désactivée
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    }
    else{ // activée
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}

/*void AutoCell::synchronizeNumToNumBit(int n){
    for (unsigned int i=0; i<8; i++)
        if (numeroBit[i]->text()=="")
            return;
    std::string numbit=NumToNumBit(n);
    for (unsigned int i=0; i<8; i++){
        numeroBit[i]->setText(QString(numbit[i]));
    }
}


void AutoCell::synchronizeNumBitToNum(const QString& s){
    if (s=="")
        return;
    std::string str;
    for (unsigned int i=0; i<8; i++)
        str+=numeroBit[i]->text().toStdString();
    int n=NumBitToNum(str);
    num->setValue(n);
}*/
