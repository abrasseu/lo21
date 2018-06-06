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
    QSpinBox* nb;  // numéro
    //QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QVBoxLayout* nbcase;
    QHBoxLayout* dimbut;
    QPushButton* dimvalid;
    QPushButton* diminval;
    QHBoxLayout* contlist;
    QVBoxLayout* list;
    QLabel* listtxt;
    QComboBox* listder;
    QPushButton* quit;
    QPushButton* retur;
    QLabel* nbtitle;
    QVBoxLayout* top;
    QHBoxLayout* buttons;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QVBoxLayout* couche;
    QTableWidget* depart;
    QTableWidget* etats;
    QVBoxLayout* simupart;
    QHBoxLayout* simutext;
    QVBoxLayout* simuright;
    QVBoxLayout* simuleft;
    QHBoxLayout* simuboth;
    QPushButton* feet;
    QPushButton* cont;
    QDoubleSpinBox* sec;
    QLabel* conttext;
    QHBoxLayout* contsec;
    QLabel* sectxt;
    QLabel* simulation;
    QVBoxLayout* pause;
    QPushButton* stop;
    QPushButton* reset;
    static unsigned int dimension;

    public:
    explicit inter_2D(QWidget* parent = nullptr);
    private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/
    void cellActivation(const QModelIndex& index);
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
