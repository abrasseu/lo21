#include "inclu_fich.h"

qt_designer::qt_designer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qt_designer)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton1D, SIGNAL(clicked()), this, SLOT(on_pushButton1D_clicked()));
    QObject::connect(ui->pushButton2D, SIGNAL(clicked()), this, SLOT(on_pushButton2D_clicked()));
    QObject::connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
}

qt_designer::~qt_designer()
{
    delete ui;
}

void qt_designer::on_pushButton1D_clicked()
{
    this->close();
    inter_1D* q=new inter_1D;
    q->show();
}


void qt_designer::on_pushButton2D_clicked()
{
    this->close();
    inter_2D* q=new inter_2D;
    q->show();
}
