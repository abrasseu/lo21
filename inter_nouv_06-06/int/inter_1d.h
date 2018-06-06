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


class inter_1D: public QWidget {
    Q_OBJECT		//macro permettant d'avoir des slots (qui sont uniquement sur Qt)
    QPushButton* quit;
    QPushButton* retur;
    QVBoxLayout* top;
    QHBoxLayout* buttons;
    QHBoxLayout* hor;

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
    QPushButton* simulation;
    static unsigned int dimension;

    public:
    explicit inter_1D(QWidget* parent = nullptr);
    private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/
    void cellActivation(const QModelIndex& index);
    //void faireSimulation();
    void backtomain();
};

#endif // INTER_1D_H
