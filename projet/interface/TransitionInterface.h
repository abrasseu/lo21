#ifndef TRANSITIONINTERFACE_H
#define TRANSITIONINTERFACE_H
#include "SimulatorInterface.h"
#include "autocell/State.h"

#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>

class Transition : public QHBoxLayout {
    protected:
        Q_OBJECT

        // Attributes
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
        QVBoxLayout* valid_layout;

        // start_layout widget
        QLabel* start_label;
        QHBoxLayout* start_layout_combo;
        QComboBox* start_cell;
        QTableWidget* start_color;

        // neighbours_layout widget
        QLabel** neighbours_label = nullptr;

        // final_layout widget
        QLabel* final_label;
        QHBoxLayout* final_layout_combo;
        QComboBox* final_cell;
        QTableWidget* final_color;

        // valid_layout widget
        QPushButton* valid_rule;
        QPushButton* modify_rule;

    public:
        friend class TransitionInterface;

        // Getters
        QPair<State*, QSpinBox*>** getNeighbour() const { return neighbours; }
        unsigned int getNeighboursNb() const { return neighbours_nb; }
        unsigned int getNbStates() const { return nb_states; }

        // Initializers
        Transition(State**, unsigned int, unsigned int);
        State* getStartState() { return start_state; }
        State* getFinalState() { return final_state; }

        void setStartState(QBoxLayout*);
        void setNeighboursNumber(State**, unsigned int, unsigned int, QBoxLayout*);
        void setFinalState(QBoxLayout*);
        void setValidLayout(QBoxLayout*);


    protected slots:

        void preventSelection(QTableWidgetItem*);

        // change color on change combobox
        void changedStartState(int);
        void changedFinalState(int);

        // Validate and modify previous rules
//        void validRuleClick();
//        void modifyRuleClick();
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
        QVector < Transition* >* transition_vector;
        // Add transition button
        QPushButton* transition_add_rule;
        // Valid PushButton
        QPushButton* transition_valid;

    public:
        friend class Transition;
        // Slot validate
        TransitionInterface(State**, unsigned int, unsigned int);

    protected slots:
        void validate_rules();
        void add_new_transition_rule();
        bool add_new_transition_rule_valid(Transition*);
};






#endif // TRANSITIONINTERFACE_H
