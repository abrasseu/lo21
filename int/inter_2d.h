#ifndef INTER_2D_H
#define INTER_2D_H
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


class inter_2D: public QWidget {
    Q_OBJECT		//macro permettant d'avoir des slots (qui sont uniquement sur Qt)

    QPushButton* quit;          //Bouton quitter
    QPushButton* retur;         //Bouton retour menu principal
    QHBoxLayout* buttons;       //Contient les deux boutons

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

    QVBoxLayout* top;           //Contient verticalement les boutons, contlist

    QVBoxLayout* couche;        //set top



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

    QTableWidget* etats;        //Grille

    static unsigned int taille;     //Taille max de la grille
    static unsigned int dimension;  //dimension de la grille

public:
    explicit inter_2D(QWidget* parent = nullptr);
    void dessinergrille();
    unsigned int getTaille() const { return taille;}

private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/
    //void cellActivation(const QModelIndex& index);
    void clickcell(int, int);
    void backtomain();
    void pushcont();
    void pushfeet();
    void pushstop();
    void pushreset();
    void pushdimvalid();
    void pushdiminval();
    //void faireSimulation();
};


#endif // INTER_2D_H
