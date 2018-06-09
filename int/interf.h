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

class trans : public QWidget {
public:
    trans();
private:
    QVBoxLayout* titre;


    QVBoxLayout* t1;
    QHBoxLayout* transition;
    QLabel* lab;
    QSpinBox* etatcell;
    QLabel* label;
    QSpinBox* etatcell2;

    QHBoxLayout* nbvois1;
    QLabel* nbvoislab;

private slots:
    void addtransi();
    void addnewtransi();

};


#endif // INTERF_H
