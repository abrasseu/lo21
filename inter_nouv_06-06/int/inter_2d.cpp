#include "inclu_fich.h"

unsigned int inter_2D::dimension=25;

inter_2D::inter_2D(QWidget* parent): QWidget(parent){

    //Deux boutons pour aller au menu principal ou quitter tout en haut
    top=new QVBoxLayout;
    buttons=new QHBoxLayout;
    quit=new QPushButton("Quitter");
    retur=new QPushButton("Retour au menu principal");
    buttons->addWidget(quit);
    buttons->addWidget(retur);

    //Choix des dimensions de la grille (carrée)
    nb=new QSpinBox(this);
    nb->setRange(10,100);
    nb->setAlignment(Qt::AlignHCenter);
    nb->setValue(10);
    nbtitle=new QLabel("Choisissez les dimensions de la grille: ");
    nbtitle->setAlignment(Qt::AlignHCenter);
    dimvalid=new QPushButton;
    dimvalid->setText("Valider");
    diminval=new QPushButton;
    diminval->setText("Effacer");
    dimbut=new QHBoxLayout;
    dimbut->addWidget(dimvalid);
    dimbut->addWidget(diminval);

    nbcase=new QVBoxLayout;
    nbcase->addWidget(nbtitle);
    nbcase->addWidget(nb);
    nbcase->addLayout(dimbut);

    contlist=new QHBoxLayout;
    contlist->addLayout(nbcase);
    list=new QVBoxLayout;
    listtxt=new QLabel;
    listtxt->setText("Sélectionner un état de départ");
    listtxt->setAlignment(Qt::AlignHCenter);

    listder=new QComboBox;
    listder->addItem("Symétrique", QVariant(1));
    listder->addItem("Au hasard", QVariant(2));
    listder->addItem("Première diagonale", QVariant(3));
    listder->addItem("Deuxième diagonale", QVariant(4));
    listder->addItem("Deux diagonales", QVariant(5));
    // Pour centrer dans la liste
    /*for (int i = 0 ; i < listder->count() ; ++i) {
        listder->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }*/
    list->addWidget(listtxt);
    list->addWidget(listder);
    list->setAlignment(Qt::AlignVCenter);
    contlist->addLayout(list);

    top->addLayout(buttons);
    top->addLayout(contlist);

    numeroc=new QHBoxLayout;
    numeroc->addLayout(top);


    /*num=new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    numl=new QLabel("Numéro");


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
    numeroBitl[7]->setText("000");*/	/*setLayout(numeroc);*/

    couche=new QVBoxLayout;
    couche->addLayout(numeroc);
    //depart=new QTableWidget(1, dimension, this);
    //couche->addWidget(depart);
    setLayout(couche);

    unsigned int taille=25;
    /*depart->setFixedSize(dimension*taille, taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (unsigned int i=0; i<dimension; i++){
        depart->setColumnWidth(i,taille);
        depart->setItem(0, i, new QTableWidgetItem("0"));
    }*/

    //connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int))); // dès qu'une valeur est
                                                                // modifiée, on fait appel à la fonction

    /*for (unsigned int i=0; i<8; i++){
        connect(numeroBit[i], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(QString)));
    }*/

    //Affichage des modes de simulation
    simupart=new QVBoxLayout;
    simutext=new QHBoxLayout;
    simulation=new QLabel("Mode de simulation");
    simulation->setAlignment(Qt::AlignHCenter);

    //Une colonne gauche en choisissant la vitesse d'avance
    simuleft=new QVBoxLayout;
    conttext=new QLabel;
    conttext->setText("Changement d'état toutes les ");
    cont=new QPushButton;
    cont->setText("Lancer avec la vitesse");
    contsec=new QHBoxLayout;
    sec=new QDoubleSpinBox;
    sec->setValue(1.0);
    sec->setAlignment(Qt::AlignHCenter);
    sec->setRange(0.1, 10.0);
    sec->setSingleStep(0.5);
    sectxt=new QLabel;
    sectxt->setText("secondes");
    contsec->addWidget(conttext);
    contsec->addWidget(sec);
    contsec->addWidget(sectxt);
    simuleft->addLayout(contsec);
    simuleft->addWidget(cont);

    //Une colonne droite au pas à pas
    simuright=new QVBoxLayout;
    feet=new QPushButton;
    feet->setText("Avancer d'un pas");
    simuright->addWidget(feet);

    simupart->addLayout(simutext);
    simuboth=new QHBoxLayout;
    simuboth->addLayout(simuleft);
    simuboth->addLayout(simuright);
    simupart->addLayout(simuboth);
    simutext->addWidget(simulation);
    couche->addLayout(simupart);

    //Layout stop reset

    pause=new QVBoxLayout;
    stop=new QPushButton;
    stop->setText("Stop");
    reset=new QPushButton;
    reset->setText("Reset");
    pause->addWidget(stop);
    pause->addWidget(reset);
    couche->addLayout(pause);

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

    setLayout(couche);

    QObject::connect(this->dimvalid, SIGNAL(clicked()), this, SLOT(pushdimvalid()));
    QObject::connect(this->diminval, SIGNAL(clicked()), this, SLOT(pushdiminval()));
    QObject::connect(this->cont, SIGNAL(clicked()), this, SLOT(pushcont()));
    QObject::connect(this->feet, SIGNAL(clicked()), this, SLOT(pushfeet()));
    QObject::connect(this->stop, SIGNAL(clicked()), this, SLOT(pushstop()));
    QObject::connect(this->reset, SIGNAL(clicked()), this, SLOT(pushreset()));
    QObject::connect(this->quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->retur, SIGNAL(clicked()), this, SLOT(backtomain()));
}

void inter_2D::pushdimvalid(){
    this->dimvalid->setEnabled(false);
    this->nb->setEnabled(false);
}

void inter_2D::pushdiminval(){
    this->dimvalid->setEnabled(true);
    this->nb->setEnabled(true);
    this->nb->setValue(10);
}

void inter_2D::pushcont(){
    this->cont->setEnabled(false);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(false);
    this->listder->setEnabled(false);
    this->feet->setEnabled(false);
}

void inter_2D::pushfeet(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(true);
    this->listder->setEnabled(false);
    this->feet->setEnabled(true);
}

void inter_2D::pushstop(){
    this->cont->setEnabled(true);
    this->sec->setEnabled(true);
    this->feet->setEnabled(true);
}

void inter_2D::pushreset(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(true);
    this->dimvalid->setEnabled(true);
    this->diminval->setEnabled(true);
    this->sec->setEnabled(true);
    this->listder->setEnabled(true);
    this->feet->setEnabled(true);
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


void inter_2D::backtomain()
{
    this->close();
    qt_designer* q=new qt_designer;
    q->show();
}


void inter_2D::cellActivation(const QModelIndex& index){
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
