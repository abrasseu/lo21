#ifndef QT_DESIGNER_H
#define QT_DESIGNER_H
#include <QtUiTools>
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class qt_designer;
}

class qt_designer : public QDialog
{
    Q_OBJECT

public:
    explicit qt_designer(QWidget *parent = 0);
    ~qt_designer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::qt_designer *ui;
};

#endif // QT_DESIGNER_H
