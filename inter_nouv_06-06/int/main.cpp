#include "inclu_fich.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    qt_designer b;
    b.show();
    return app.exec();
}
