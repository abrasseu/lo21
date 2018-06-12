#ifndef INTERF_H
#define INTERF_H
#include <iostream>
#include <string>
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QTableWidget>
#include <vector>

using namespace std;

class trans : public QWidget {
    Q_OBJECT

    QVBoxLayout* titre;


    QVBoxLayout* t1;
    QHBoxLayout* transition;
    QLabel* lab;
    QSpinBox* etatcell;
    QLabel* label;
    QSpinBox* etatcell2;

    QHBoxLayout* nbvois1;

    QPushButton* add;

    QPushButton* valid;
    QHBoxLayout* tabrules;

    QVBoxLayout* rules[2];    //pour transition sur 2 états statiques
    QLabel* rulestitle[2];
    QSpinBox* rulesvalue[20];
    QPushButton* rulesvalid[20];
    unsigned int nbrulesvalue[2];

    /*vector<QHBoxLayout*>* containerRule;
    QTableWidget* grid;
    QPushButton* validGrid;*/

public:
    explicit trans(QWidget* parent = nullptr);
    //void addtransition(int i); //pour transition sur 2 états statique

    //void gridtransition();

private slots:
    void validation();
    /*void clickcell(int, int);
    void validGrid_clicked();*/
    //void slot_addtransition(); //pour transition sur 2 états statique

};


#endif // INTERF_H
