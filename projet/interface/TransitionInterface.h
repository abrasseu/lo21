#ifndef TRANSITIONINTERFACE_H
#define TRANSITIONINTERFACE_H
#include "SimulatorInterface.h"
#include "autocell/State.h"

#include <QMessageBox>

class Transition : public QHBoxLayout {
    protected:
        Q_OBJECT

        // Attributes
        State* start_state;
        QPair<State*, QSpinBox*>** neighbours = nullptr;
        unsigned int neighbours_nb;
        unsigned int nb_states;
        State* final_state;

        // Layout

        QVBoxLayout* start_layout;
        QVBoxLayout** neighbours_layout = nullptr;
        QVBoxLayout* final_layout;

        // start_layout widget
        QLabel* start_label;
        QTableWidget* start_cell;

        // neighbours_layout widget
        QLabel** neighbours_label = nullptr;

        // final_layout widget
        QLabel* final_label;
        QTableWidget* final_cell;

    public:
        friend class TransitionInterface;

        // Getters
        unsigned int getNeighboursNb() const { return neighbours_nb; }
        unsigned int getNbStates() const { return nb_states; }

        // Initializers
        Transition(State**, unsigned int, unsigned int);
        State* getStartState() { return start_state; }
        State* getFinalState() { return final_state; }

        void setStartState(QVBoxLayout*);
        void setNeighboursNumber(State**, unsigned int, unsigned int, QHBoxLayout*);
        void setFinalState(QVBoxLayout*);


    protected slots:

        // start_state cell slots
        //void rotateCellState(QTableWidgetItem*);
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
};






#endif // TRANSITIONINTERFACE_H
