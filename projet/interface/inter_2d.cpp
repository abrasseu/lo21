#include "inclu_fich.h"
#include <QMessageBox>

inter_2D::inter_2D(unsigned int t, unsigned int d): taille(t), dimension(d), changeCellEnabled(true) {
    setWindowTitle("Interface 2D");

    //Deux boutons pour aller au menu principal ou quitter tout en haut
    top=new QVBoxLayout;
    buttons=new QHBoxLayout;
    quit=new QPushButton("Quitter");
    retur=new QPushButton("Retour au menu principal");
    buttons->addWidget(quit);
    buttons->addWidget(retur);

    //Choix des dimensions de la grille (carrée)
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
    listder->addItem("Vide", QVariant(0));
    listder->addItem("Symétrique", QVariant(1));
    listder->addItem("Au hasard", QVariant(2));
    listder->addItem("Diagonale principale", QVariant(3));
    listder->addItem("Diagonale opposée", QVariant(4));
    listder->addItem("Deux diagonales", QVariant(5));

    QObject::connect(listder, SIGNAL(currentIndexChanged(int)), this, SLOT(change_grid(int)));

    // Pour centrer dans la liste mais pas l'élément affiché
    /*for (int i = 0 ; i < listder->count() ; ++i) {
        listder->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }*/

    //list contient les widgets pour la liste déroulante, c'est l'élément en partie droite de contlist
    list->addWidget(listtxt);
    list->addWidget(listder);
    list->setAlignment(Qt::AlignVCenter);
    contlist->addLayout(list);

    transi = new QPushButton;
    transi->setText("Choisir les transitions");
    tran = new QVBoxLayout;
    tran->addWidget(transi);
    contlist->addLayout(tran);

    //On accumule tout dans top en vertical
    top->addLayout(buttons);
    top->addLayout(contlist);

    couche=new QVBoxLayout;
    couche->addLayout(top);
    //setLayout(couche);


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

    QObject::connect(transi, SIGNAL(clicked()), this, SLOT(pushtransi()));
    QObject::connect(dimvalid, SIGNAL(clicked()), this, SLOT(pushdimvalid()));
    QObject::connect(diminval, SIGNAL(clicked()), this, SLOT(pushdiminval()));
    QObject::connect(cont, SIGNAL(clicked()), this, SLOT(pushcont()));
    QObject::connect(feet, SIGNAL(clicked()), this, SLOT(pushfeet()));
    QObject::connect(stop, SIGNAL(clicked()), this, SLOT(pushstop()));
    QObject::connect(reset, SIGNAL(clicked()), this, SLOT(pushreset()));
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(retur, SIGNAL(clicked()), this, SLOT(backtomain()));

    setLayout(couche);
}

void inter_2D::dessinergrille(){
    delete etats;
    etats=new QTableWidget(dimension, dimension);
    etats->setFixedSize(taille+dimension/3, taille+dimension/3);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (unsigned int i=0; i<dimension; i++){
        etats->setColumnWidth(i, taille/dimension);
        etats->setRowHeight(i, taille/dimension);
        for (unsigned int j=0; j<dimension; j++){
            etats->setItem(j, i, new QTableWidgetItem(""));
        }
    }

    QObject::connect(etats, SIGNAL(cellClicked(int,int)), this, SLOT(clickcell(int, int)));
    couche->addWidget(etats);
}

void inter_2D::clickcell(int i, int j){
    if (changeCellEnabled){
        if (etats->item(i,j)->backgroundColor()== Qt::black)
            etats->item(i,j)->setBackgroundColor(Qt::white);
        else
            etats->item(i,j)->setBackgroundColor(Qt::black);
    }
}

void inter_2D::pushdimvalid(){
    dimension=this->nb->value();
    dessinergrille();
    this->listder->setCurrentIndex(0);
    //dimvalid->setEnabled(false);
    //nb->setEnabled(false);
}

void inter_2D::pushdiminval(){
    //dimvalid->setEnabled(true);
    //nb->setEnabled(true);
    this->nb->setValue(10);
    this->listder->setCurrentIndex(0);
    dimension=10;
    dessinergrille();
}


void inter_2D::pushtransi(){
    trans* t=new trans;
    t->show();
}


void inter_2D::pushcont(){
    this->cont->setEnabled(false);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(false);
    this->listder->setEnabled(false);
    this->feet->setEnabled(false);

    changeCellEnabled = false;
}

void inter_2D::pushfeet(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(false);
    this->dimvalid->setEnabled(false);
    this->diminval->setEnabled(false);
    this->sec->setEnabled(true);
    this->listder->setEnabled(false);
    this->feet->setEnabled(true);

    changeCellEnabled = true;

    //nextStep();
}

void inter_2D::pushstop(){
    this->cont->setEnabled(true);
    this->sec->setEnabled(true);
    this->feet->setEnabled(true);

    changeCellEnabled = true;
}

void inter_2D::pushreset(){
    this->cont->setEnabled(true);
    this->nb->setEnabled(true);
    this->dimvalid->setEnabled(true);
    this->diminval->setEnabled(true);
    this->sec->setEnabled(true);
    this->listder->setEnabled(true);
    this->feet->setEnabled(true);

    change_grid(listder->currentData().toInt());
    //QMessageBox::warning(this, "val", QString::number(listder->currentData().toInt()));
    changeCellEnabled = true;
}

void inter_2D::backtomain(){
    this->close();
    HomeView* q=new HomeView;
    q->show();
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



/*void inter_2D::cellActivation(const QModelIndex& index){
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
}*/

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

void inter_2D::change_grid(int v){
    switch(v){
        case 0 :
            initGridWhite();
            break;
        case 1 :
            initGrid12();
            break;
        case 2 :
            initGridRandom();
            break;
    }
}

void inter_2D::initGridRandom(){
    SimulatorLifeGame simu(dimension);
    uint* tab = simu.getCells();

    for (unsigned int i = 0; i < dimension; i++){
        for (unsigned int j =0; j < dimension; j++)
                if (tab[i * simu.getCellsSize() + j])
                    etats->item(i,j)->setBackgroundColor(Qt::black); // vivant
                else
                    etats->item(i,j)->setBackgroundColor(Qt::white); // mort
    }
}

void inter_2D::initGrid12(){
    SimulatorLifeGame simu(dimension);

    for (unsigned int i = 0; i < dimension; i++){
        for (unsigned int j =0; j < dimension; j++){
            if (i%2 == 0){
                if (j%2 == 0)
                    etats->item(i,j)->setBackgroundColor(Qt::white);
                else
                    etats->item(i,j)->setBackgroundColor(Qt::black);
            }
            else{
                if (j%2 == 1)
                    etats->item(i,j)->setBackgroundColor(Qt::white);
                else
                    etats->item(i,j)->setBackgroundColor(Qt::black);
            }
        }
    }
}

void inter_2D::initGridWhite(){
    SimulatorLifeGame simu(dimension);

    for (unsigned int i = 0; i < dimension; i++){
        for (unsigned int j =0; j < dimension; j++)
            etats->item(i,j)->setBackgroundColor(Qt::white);
    }
}

