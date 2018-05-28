#include "interf.h"
#include "qt_designer.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    qt_designer b;
    b.show();
    return app.exec();
}
