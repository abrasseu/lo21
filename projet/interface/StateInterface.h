#ifndef STATEINTERFACE_H
#define STATEINTERFACE_H

#include <QLineEdit>
#include <QPalette>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVector>

#include "SimulatorInterface.h"
#include <iostream>
class StateInterface : public QHBoxLayout {
	Q_OBJECT
    protected:
		friend class SimulatorInterface;
        friend class Interface1D;
		State* state;

		// Main layout
		QHBoxLayout* state_layout;

		// === Name Layout
		QVBoxLayout* name_layout;
		// Attributes
		QLabel* state_name_label;
		QLineEdit* state_name;

		// === Color Layout
		QVBoxLayout* color_layout;
		// Attributes
        QTableWidget* color_button;
		QLabel* state_color_label;


//        QPushButton* state_delete;

		// Agencement
		void setNameLayout(QBoxLayout* parent, std::string name = std::string());
		void setColorLayout(QBoxLayout* parent, std::string name = std::string());

	public:
		StateInterface(std::string name = std::string(), std::string c = std::string(), State* s = nullptr);
        ~StateInterface();
		void setState(State* s) { state = s; }
		State* getState() const { return state; }

	protected slots:
		void display_palette_color(QTableWidgetItem*);
//        void delete_state();
};


#endif // STATEINTERFACE_H
