#include <QApplication>
#include "interface/HomeView.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	HomeView homeView;
	homeView.show();
	return app.exec();
}
