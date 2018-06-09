#ifndef INTER_1D_H
#define INTER_1D_H
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QComboBox>


class inter_1D: public QWidget {
    Q_OBJECT		//macro permettant d'avoir des slots (qui sont uniquement sur Qt)
    QPushButton* quit;
    QPushButton* retur;
    QVBoxLayout* top;
    QHBoxLayout* buttons;
    QHBoxLayout* hor;

    QSpinBox* nb;               //Choix de dimensions
    QLabel* nbtitle;            //Label associé au spinbox
    QPushButton* dimvalid;      //Bouton valider dimension
    QPushButton* diminval;      //Bouton invalider dimension
    QHBoxLayout* dimbut;        //Contient les deux boutons
    QVBoxLayout* nbcase;        //contient tous les attributs pour choix dimensions

    QVBoxLayout* list;          //Contient tous les attributs pour choix grille de départ
    QLabel* listtxt;            //Label pour choix grille de départ
    QComboBox* listder;         //Liste déroulante avec grilles de départs

    QHBoxLayout* contlist;      //Contient à gauche choix dimension, à droite la liste

    QSpinBox* num;  // numéro
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QHBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QVBoxLayout* couche;
    QTableWidget* depart;
    QTableWidget* etats;


    QLabel* simulation;         //Label pour toute la partie simulation

    QLabel* conttext;           //Label changement d'état par x secondes
    QDoubleSpinBox* sec;        //Spinbox choix des secondes
    QLabel* sectxt;             //Affichage secondes après spinbox
    QPushButton* cont;          //Lancer avec la vitesse
    QHBoxLayout* contsec;       //Contient toute la partie pour choix du temps

    QVBoxLayout* simuleft;      //Partie gauche de simulation, avec tous les attributs du choix de vitesse + bouton

    QPushButton* feet;          //Bouton pas à pas
    QVBoxLayout* simuright;     //Contient partie droite avec le pas à pas

    QHBoxLayout* simutext;      //Contient le label de titre "Mode de simulation"
    QHBoxLayout* simuboth;      //Contient partie droite et gauche
    QVBoxLayout* simupart;      //Contient titre + 2 parties verticales
    QVBoxLayout* pause;         //Contient les boutons stop et reset
    QPushButton* stop;          //Bouton stop
    QPushButton* reset;         //Bouton reset

    static unsigned int taille;     //Taille max de la grille
    static unsigned int dimension;

    public:
    explicit inter_1D(QWidget* parent = nullptr);
    void dessinergrille();
    private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/
    void cellActivation(const QModelIndex& index);
    //void faireSimulation();
    void clickcell(int, int);
    void backtomain();
    void pushcont();
    void pushfeet();
    void pushstop();
    void pushreset();
    void pushdimvalid();
    void pushdiminval();
};

#endif // INTER_1D_H
