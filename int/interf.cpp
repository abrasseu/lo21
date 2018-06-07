#include "inclu_fich.h"

fen::fen(): QWidget(){
    setFixedSize(800,500);
    titre = new QHBoxLayout;
    QLabel* texte = new QLabel;
    titre->addWidget(texte);
    texte->setText("Menu principal");
    //titre->setAlignment(Qt.AlignCenter);

    setLayout(titre);
    bout1D = new QPushButton("1D", this);
    bout1D->setFixedSize(100,100);
    bout1D->move(100,300);
    bout2D = new QPushButton("2D", this);
    bout2D->setFixedSize(100,100);
    bout2D->move(600,300);

}
