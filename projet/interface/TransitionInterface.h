#ifndef TRANSITIONINTERFACE_H
#define TRANSITIONINTERFACE_H

#include "../autocell/SimulatorManager.h"
#include "SimulatorInterface.h"
#include "autocell/State.h"

#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>

class Transition : public QHBoxLayout {
	protected:
		Q_OBJECT

		// Attributes
//        State* state = nullptr;
		State* start_state;
		QPair<State*, QSpinBox*>** neighbours = nullptr;
		unsigned int neighbours_nb;
		unsigned int nb_states;
		State* final_state;
		State** state_list;

		// Layout
		QVBoxLayout* start_layout;
		QVBoxLayout** neighbours_layout = nullptr;
		QVBoxLayout* final_layout;

		// Start_layout widget
		QLabel* start_label;
		QHBoxLayout* start_layout_combo;
		QComboBox* start_cell;
		QTableWidget* start_color;

		// Neighbours_layout widget
		QLabel** neighbours_label = nullptr;

		// final_layout widget
		QLabel* final_label;
		QHBoxLayout* final_layout_combo;
		QComboBox* final_cell;
		QTableWidget* final_color;

	public:
		friend class TransitionInterface;

		// Getters
		QPair<State*, QSpinBox*>** getNeighbour() const { return neighbours; }
		unsigned int getNeighboursNb() const { return neighbours_nb; }
		unsigned int getNbStates() const { return nb_states; }
//        void getState() const { return state; }

        // Setters
//        void setState(State* s) { state = s; }

		// Initializers
        Transition(State**, unsigned int, unsigned int, unsigned int* spin_box_tab = nullptr,
                                    State* state_start = nullptr, State* state_final = nullptr, bool modify = true);
		State* getStartState() { return start_state; }
		State* getFinalState() { return final_state; }

        void setStartState(QVBoxLayout*, State*, bool modify = true);
        void setNeighboursNumber(State**, unsigned int, unsigned int, QHBoxLayout*, unsigned int* spin_value = nullptr, bool modify = true);
        void setFinalState(QVBoxLayout*, State*, bool modify = true);

//        void modifyRule(QObject*);


	protected slots:
		void preventSelection(QTableWidgetItem*);

		// change color on change combobox
		void changedStartState(int);
		void changedFinalState(int);
};


class TransitionInterface : public QWidget {
	private:
		Q_OBJECT
		State** state_list;
		unsigned int state_list_number;
		unsigned int neighbour_number;

		// Main Layout
		QVBoxLayout* main_layout;
		QLabel* title;

		// Transition Layout
		QVBoxLayout* transition_layout;
		QVector<QPair <Transition*, QPushButton* > >* transition_vector;
		// Add transition button
		QPushButton* transition_add_rule;
		// Valid PushButton
		QPushButton* transition_valid;

	public:
		friend class Transition;
		// Slot validate
		TransitionInterface();
        void displayExistingRules();


	signals:
		void close_transition_interface();
	protected slots:
		void validateRules();
		void addNewTransitionRule();
		bool addNewTransitionRuleValid(Transition*);

		void closeEvent(QCloseEvent*);

        void deleteRule();
};






#endif // TRANSITIONINTERFACE_H
