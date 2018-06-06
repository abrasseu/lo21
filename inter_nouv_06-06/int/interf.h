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

class fen : public QWidget {
public:
    fen();
private:
    QHBoxLayout* titre;
    QTextEdit* men;
    QPushButton* bout1D;
    QPushButton* bout2D;
};


#endif // INTERF_H
