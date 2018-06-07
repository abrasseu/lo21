#include "inclu_fich.h"

unsigned int inter_2D::dimension=10;
unsigned int inter_2D::taille=400;

inter_2D::inter_2D(QWidget* parent): QWidget(parent){

    /*QString nomFichier = QFileDialog::getSaveFileName(this); //voire d'autres paramètres
    QFile fichier(nomFichier);*/

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
    nb->setRange(10,100);
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
    listder->addItem("Symétrique", QVariant(1));
    listder->addItem("Au hasard", QVariant(2));
    listder->addItem("Première diagonale", QVariant(3));
    listder->addItem("Deuxième diagonale", QVariant(4));
    listder->addItem("Deux diagonales", QVariant(5));

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

    /*etats=new QTableWidget(dimension, dimension, this);
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
    }*/
    //etats=new QTableWidget;
    dessinergrille(couche);
    //etats->setFixedSize(dimension*taille, dimension*taille);
    //couche->addWidget(etats);
    //setLayout(couche);

    QObject::connect(this->dimvalid, SIGNAL(clicked()), this, SLOT(pushdimvalid()));
    QObject::connect(this->diminval, SIGNAL(clicked()), this, SLOT(pushdiminval()));
    QObject::connect(this->cont, SIGNAL(clicked()), this, SLOT(pushcont()));
    QObject::connect(this->feet, SIGNAL(clicked()), this, SLOT(pushfeet()));
    QObject::connect(this->stop, SIGNAL(clicked()), this, SLOT(pushstop()));
    QObject::connect(this->reset, SIGNAL(clicked()), this, SLOT(pushreset()));
    QObject::connect(this->quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->retur, SIGNAL(clicked()), this, SLOT(backtomain()));
}

void inter_2D::dessinergrille(QVBoxLayout* couche){
    QTableWidget* etats=new QTableWidget(inter_2D::dimension, inter_2D::dimension);
    etats->setFixedSize(inter_2D::taille, inter_2D::taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (unsigned int i=0; i<dimension; i++){
        etats->setColumnWidth(i, inter_2D::taille/inter_2D::dimension);
        etats->setRowHeight(i, inter_2D::taille/inter_2D::dimension);
        for (unsigned int j=0; j<dimension; j++){
            etats->setItem(j, i, new QTableWidgetItem(""));
        }
    }

    couche->addWidget(etats);
    setLayout(couche);
}

void inter_2D::pushdimvalid(){
    inter_2D::dimension=this->nb->value();
    /*this->etats->clear();
    this->etats->setRowCount(inter_2D::dimension);
    this->etats->setRowCount(inter_2D::dimension);*/
    //dessinergrille(this->couche);
    setLayout(this->couche);
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
