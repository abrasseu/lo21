#include "HomeView.h"
#include "SimulatorInterface.h"
#include "Interface2D.h"
#include "Interface1D.h"

#include <string>
#include <QFileDialog>

/**
 * \brief Constructeur du menu principal
 * \details Crée et affiche le menu principal avec les label et boutons pour changer de menu
 */
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
    QString comment = QString::fromStdString("<center>Le Jeu de la Vie est accessible à partir d'un fichier à charger grâce au bouton charger ci-dessous</center><br><br><br><br>");
    subtitle = new QLabel("<center>Par<br>Samy Nastuzzi<br>Simon Bazin<br>Alexandre Brasseur</center><br><br><br>"+comment);
    subtitle->setAlignment(Qt::AlignCenter);
	// Buttons
    load_automate = new QPushButton("Charger Automate");
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
    automate_texts[0] = new QLabel("<center>Réaliser des simulations avec un automate à<br>1 dimension<br> avec les paramètres sélectionnés</center>");
	automate_texts[0]->setWordWrap(true);
    automate_texts[1] = new QLabel("<center>Réaliser des simulations avec un automate à<br>2 dimensions<br> avec les paramètres sélectionnés</center>");
	automate_texts[1]->setWordWrap(true);


	// === Add Widgets
	// Main Layout
	setLayout(main_layout);
	main_layout->addWidget(title);
	main_layout->addWidget(subtitle);
	main_layout->addLayout(automate_layout);
    main_layout->addWidget(load_automate);
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
    connect(load_automate, SIGNAL(clicked()), this, SLOT(loadAutomate()));
	connect(automate_bts[0], SIGNAL(clicked()), this, SLOT(simulate1D()));
	connect(automate_bts[1], SIGNAL(clicked()), this, SLOT(simulate2D()));
}


/**
 * \brief Destructeur du menu principal
 */
HomeView::~HomeView() {
	delete[] automate_bts;
	delete[] automate_texts;
	delete[] automate_titles;
	delete[] automate_layouts;
//	~QWidget();
}


/*
|--------------------------------------------------------------------------
|	Slots
|--------------------------------------------------------------------------
*/

/**
 * \brief Fonction pour afficher l'interface 1D
 * \details Slot activé lors de l'appui sur le bouton pour afficher l'interface 1D
 */
void HomeView::simulate1D() {
	close();
	Interface1D* view = new Interface1D();
	view->show();
}

/**
 * \brief Fonction pour afficher l'interface 2D
 * \details Slot activé lors de l'appui sur le bouton pour afficher l'interface 2D
 */
void HomeView::simulate2D() {
	close();
	Interface2D* view = new Interface2D();
	view->show();
}

/**
 * \brief Fonction pour charger des fichiers
 * \details Permet de charger des fichiers qui correspondent à des automates. Les fichiers sont des fichiers \b .json uniquement
 */
void HomeView::loadAutomate(){
    try {
        QString fileName = QFileDialog::getOpenFileName(this,
               tr("Charger le fichier"), "",
               tr("Adresse du fichier (*.json)"));

        try {
            SimulatorManager::getManager()->importConfig(fileName.toStdString());

            if (SimulatorManager::getManager()->getDimension() == 1){
                close();
                Interface1D* view = new Interface1D(true);
                view->show();
            }
            else if (SimulatorManager::getManager()->getDimension() == 2){
                close();
                Interface2D* view = new Interface2D(true);
                view->show();
            }
        } catch(SimulatorException error) {
            QMessageBox::critical(this, "Erreur", QString::fromStdString(error.what()));
        }
    } catch (...) {}
}




