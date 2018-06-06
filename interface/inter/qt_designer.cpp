#include "qt_designer.h"
#include "ui_qt_designer.h"
#include "interf.h"

qt_designer::qt_designer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qt_designer)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton1D, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    QObject::connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
}

qt_designer::~qt_designer()
{
    delete ui;
}

void qt_designer::on_pushButton_clicked()
{
    this->close();
    fen* q=new fen;
    q->show();
}
