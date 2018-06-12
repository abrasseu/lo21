#ifndef SIMULATOR_INTERFACE_H
#define SIMULATOR_INTERFACE_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QComboBox>

class SimulatorInterface : public QWidget {
	Q_OBJECT		// Macro permettant d'avoir des slots (qui sont uniquement sur Qt)

	private:
		unsigned int grid_size;			// Taille max de la grille
		unsigned int grid_dimension;

		// === Main Layouts
		QHBoxLayout* main_layout;
		QVBoxLayout* controls_layout;
		QVBoxLayout* view_layout;

		// === Control Layouts
		QHBoxLayout* window_controls;
		QHBoxLayout* grid_controls;			// view or grid ?
		QVBoxLayout* simulation_controls;

		// === Window Controls
		QPushButton* quit_bt;
		QPushButton* home_bt;

		// === Grid Controls
		// Dimension Controls
		QVBoxLayout* grid_dim_controls;
		QHBoxLayout* grid_dim_select_layout;
		QLabel* grid_dim_label;
		QSpinBox* grid_dim_spinbox;
		QHBoxLayout* grid_dim_bts_layout;
		QPushButton* grid_dim_set_bt;				// Bouton valider dimension
		QPushButton* grid_dim_reset_bt;			// Bouton invalider dimension

		// Initial State Controls
		QVBoxLayout* initial_state_controls;
		QLabel* initial_state_label;            // Label pour choix grille de départ
		QComboBox* initial_state_selector;      // Liste déroulante avec grilles de départs
		QPushButton* initial_state_setter;

		// === Simulator Controls
		QLabel* simulation_label;				// Label pour toute la partie simulation
		// Speed Controls
		QHBoxLayout* speed_layout;
		QLabel* speed_label;
		QDoubleSpinBox* speed_selector;			// Spinbox choix des secondes
		// Run Controls
		QHBoxLayout* sim_run_layout;			//Partie gauche de simulation, avec tous les attributs du choix de vitesse + bouton
		QPushButton* sim_start_bt;				// Lancer avec la vitesse
		QPushButton* sim_step_bt;				// Avancer d'un pas
		QPushButton* sim_stop_bt;				// Arrêter la simulation
		QPushButton* sim_reset_bt;				// Reset la simulation

		// Constructor Setters
		void setGridControls(QBoxLayout*);
		void setDimensionControls(QBoxLayout*);
		void setSimulatorControls(QBoxLayout*);
		void setInitialStateControls(QBoxLayout*);

	public:
		SimulatorInterface(QWidget* parent = nullptr);
		void drawGrid();

	private slots:
		// Window Slots
		void home();

		// Simulation Slots
		void start_simulation();
		void step_simulation();
		void stop_simulation();
		void reset_simulation();

		// Grid Slots
		void set_initial_state();
		void grid_set_dim();
		void grid_reset_dim();

//		void synchronizeNumToNumBit(int i);
//		void synchronizeNumBitToNum(const QString& s);
		/*
		void cellActivation(const QModelIndex& index);
		//void faireSimulation();
		void clickcell(int, int);
		*/
};

#endif // SIMULATOR_H