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
    QVector < QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >* > rules;
    /*QVBoxLayout* rules[2];
    QLabel* rulestitle[2];
    QSpinBox* rulesvalue[20];
    QPushButton* rulesvalid[20];
    unsigned int nbrulesvalue[2];*/

public:
    explicit trans(QWidget* parent = nullptr);
    void addnewtransi(QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >);
    void addtransitype(QPair< QVBoxLayout*, QVector < QPair< QSpinBox*, QPushButton* > > >*);

    /*void addtransition(int i);*/

private slots:
    void addtransi();
    void validation();

    /*void slot_addtransition();*/

};


#endif // INTERF_H
