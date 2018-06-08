#include "inclu_fich.h"

unsigned int inter_1D::dimension=10;
unsigned int inter_1D::taille=400;

inter_1D::inter_1D(QWidget* parent): QWidget(parent){
    top=new QVBoxLayout;
    buttons=new QHBoxLayout;
    quit=new QPushButton("Quitter");
    retur=new QPushButton("Retour au menu principal");
    buttons->addWidget(quit);
    buttons->addWidget(retur);
    top->addLayout(buttons);

    nbtitle=new QLabel("Choisissez les dimensions de la grille: ");
    nbtitle->setAlignment(Qt::AlignCenter);
    nb=new QSpinBox(this);
    nb->setRange(3,100);
    nb->setAlignment(Qt::AlignHCenter);
    nb->setValue(10);
    dimvalid=new QPushButton;
    dimvalid->setText("Valider");
    diminval=new QPushButton;
    diminval->setText("Effacer");
    dimbut=new QHBoxLayout;
    dimbut->addWidget(dimvalid);
    dimbut->addWidget(diminval);

    //nbcase contient tous les widgets pour dimension
    nbcase=new QVBoxLayout;
    nbcase->addWidget(nbtitle);
    nbcase->addWidget(nb);
    nbcase->addLayout(dimbut);

    //contlist contient à gauche la dimension et à droite la liste déroulante
    contlist=new QHBoxLayout;
    contlist->addLayout(nbcase);
    list=new QVBoxLayout;
    listtxt=new QLabel;
    listtxt->setText("Sélectionner un état de départ");
    listtxt->setAlignment(Qt::AlignHCenter);

    //listdet est la liste déroulante
    listder=new QComboBox;
    listder->addItem("Un seul au milieu", QVariant(1));
    listder->addItem("Au hasard", QVariant(2));
    listder->addItem("Un sur deux", QVariant(3));
    listder->addItem("Un sur trois", QVariant(4));

    // Pour centrer dans la liste mais pas l'élément affiché
    /*for (int i = 0 ; i < listder->count() ; ++i) {
        listder->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }*/

    //list contient les widgets pour la liste déroulante, c'est l'élément en partie droite de contlist
    list->addWidget(listtxt);
    list->addWidget(listder);
    list->setAlignment(Qt::AlignVCenter);
    contlist->addLayout(list);

    //On accumule tout dans top en vertical
    top->addLayout(buttons);
    top->addLayout(contlist);

    num=new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    numl=new QLabel("Numéro");
    numc=new QHBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);
    numc->setAlignment(Qt::AlignBottom);

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
    depart=new QTableWidget(1, inter_1D::dimension, this);
    couche->addWidget(depart);
    setLayout(couche);

    depart->setFixedSize(inter_1D::taille+inter_1D::dimension/3, inter_1D::taille/inter_1D::dimension);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (unsigned int i=0; i<inter_1D::dimension; i++){
        depart->setColumnWidth(i,inter_1D::taille/inter_1D::dimension);
        depart->setItem(0, i, new QTableWidgetItem("0"));
    }

    //connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int))); // dès qu'une valeur est
                                                                // modifiée, on fait appel à la fonction

    /*for (unsigned int i=0; i<8; i++){
        connect(numeroBit[i], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(QString)));
    }*/

    //Affichage des modes de simulation
    simulation=new QLabel("Mode de simulation");
    simulation->setAlignment(Qt::AlignCenter);

    //Une colonne gauche en choisissant la vitesse d'avance
    conttext=new QLabel;
    conttext->setText("Changement d'état toutes les ");
    sec=new QDoubleSpinBox;
    sec->setValue(1.0);
    sec->setAlignment(Qt::AlignHCenter);
    sec->setRange(0.1, 10.0);
    sec->setSingleStep(0.5);
    sectxt=new QLabel;
    sectxt->setText("secondes");
    cont=new QPushButton;
    cont->setText("Lancer avec la vitesse");

    contsec=new QHBoxLayout;
    contsec->addWidget(conttext);
    contsec->addWidget(sec);
    contsec->addWidget(sectxt);
    simuleft=new QVBoxLayout;
    simuleft->addLayout(contsec);
    simuleft->addWidget(cont);
    simuleft->setAlignment(Qt::AlignVCenter);

    //Une colonne droite au pas à pas
    feet=new QPushButton;
    feet->setText("Avancer d'un pas");
    simuright=new QVBoxLayout;
    simuright->addWidget(feet);
    simuright->setAlignment(Qt::AlignVCenter);

    simutext=new QHBoxLayout;
    simutext->addWidget(simulation);
    simuboth=new QHBoxLayout;
    simuboth->addLayout(simuleft);
    simuboth->addLayout(simuright);

    simupart=new QVBoxLayout;
    simupart->addLayout(simutext);
    simupart->addLayout(simuboth);
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

    etats=new QTableWidget;
    dessinergrille();
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

void inter_1D::dessinergrille(){
    delete etats;
    etats=new QTableWidget(inter_1D::dimension, inter_1D::dimension);
    etats->setFixedSize(inter_1D::taille+inter_1D::dimension/3, inter_1D::taille+inter_1D::dimension/3);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (unsigned int i=0; i<dimension; i++){
        etats->setColumnWidth(i, inter_1D::taille/inter_1D::dimension);
        etats->setRowHeight(i, inter_1D::taille/inter_1D::dimension);
        for (unsigned int j=0; j<dimension; j++){
            etats->setItem(j, i, new QTableWidgetItem(""));
        }
    }

    QObject::connect(etats, SIGNAL(cellClicked(int,int)), this, SLOT(clickcell(int, int)));
    couche->addWidget(etats);
}

void inter_1D::clickcell(int i, int j){
    if (etats->item(i,j)->backgroundColor()== Qt::black)
        etats->item(i,j)->setBackgroundColor(Qt::white);
    else
        etats->item(i,j)->setBackgroundColor(Qt::black);
}

void inter_1D::pushdimvalid(){
    inter_1D::dimension=this->nb->value();
    dessinergrille();
    //dimvalid->setEnabled(false);
    //nb->setEnabled(false);
}

void inter_1D::pushdiminval(){
    //dimvalid->setEnabled(true);
    //nb->setEnabled(true);
    this->nb->setValue(10);
    inter_1D::dimension=10;
    dessinergrille();
}

void inter_1D::pushcont(){
    this->cont->setEnabled(false);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(false);
    this->listder->setEnabled(false);
    this->feet->setEnabled(false);
}

void inter_1D::pushfeet(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(true);
    this->listder->setEnabled(false);
    this->feet->setEnabled(true);
}

void inter_1D::pushstop(){
    this->cont->setEnabled(true);
    this->sec->setEnabled(true);
    this->feet->setEnabled(true);
}

void inter_1D::pushreset(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(true);
    this->dimvalid->setEnabled(true);
    this->diminval->setEnabled(true);
    this->sec->setEnabled(true);
    this->listder->setEnabled(true);
    this->feet->setEnabled(true);
}


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
