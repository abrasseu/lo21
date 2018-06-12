#include "HomeView.h"
#include "SimulatorInterface.h"
#include <string>

HomeView::HomeView() : QWidget() {
	// Set up
	setWindowTitle("AutoCell");

	// === Init Layouts
	main_layout = new QVBoxLayout();
	automate_layout = new QHBoxLayout();
	automate_layouts = new QVBoxLayout*[nb_automates];
	for (suint i = 0; i < nb_automates; i++)
		automate_layouts[i] = new QVBoxLayout();

	// === Init Main Widgets
	// Labels
	title = new QLabel("AutoCell");
	title->setAlignment(Qt::AlignCenter);
	title->setMargin(10);
	subtitle = new QLabel("Par Samy Nastuzzi, Simon Bazin and Alexandre Brasseur");
	subtitle->setAlignment(Qt::AlignCenter);
	// Buttons
	quit_bt = new QPushButton("Quitter");

	// === Init Automate Widgets
	automate_titles = new QLabel*[nb_automates];
	automate_texts = new QLabel*[nb_automates];
	automate_bts = new QPushButton*[nb_automates];
	for (suint i = 0; i < nb_automates; i++) {
		automate_titles[i] = new QLabel(QString::fromStdString("Automate " + std::to_string(i+1) + "D"));
		automate_titles[i]->setAlignment(Qt::AlignCenter);
		automate_bts[i] = new QPushButton("Simuler");
	}
	automate_texts[0] = new QLabel("Automate 1D blabla");
	automate_texts[0]->setWordWrap(true);
	automate_texts[1] = new QLabel("Automate 2D blabla");
	automate_texts[1]->setWordWrap(true);


	// === Add Widgets
	// Main Layout
	setLayout(main_layout);
	main_layout->addWidget(title);
	main_layout->addWidget(subtitle);
	main_layout->addLayout(automate_layout);
	main_layout->addWidget(quit_bt);
	// Automate Layouts
	for (suint i = 0; i < nb_automates; i++) {
		automate_layout->addLayout(automate_layouts[i]);
		automate_layouts[i]->addWidget(automate_titles[i]);
		automate_layouts[i]->addWidget(automate_texts[i]);
		automate_layouts[i]->addWidget(automate_bts[i]);
	}

	// === Connections
	connect(quit_bt, SIGNAL(clicked()), this, SLOT(close()));
	connect(automate_bts[0], SIGNAL(clicked()), this, SLOT(simulate1D()));
	connect(automate_bts[1], SIGNAL(clicked()), this, SLOT(simulate2D()));
}

HomeView::~HomeView() {
	delete[] automate_bts;
	delete[] automate_texts;
	delete[] automate_titles;
	delete[] automate_layouts;
//	~QWidget();
}

void HomeView::simulate1D() {
	close();
	SimulatorInterface* view = new SimulatorInterface();
	view->show();
}

void HomeView::simulate2D() {
	close();
	inter_2D* interface2D = new inter_2D();
	interface2D->show();
}




