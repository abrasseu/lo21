#include "Interface1D.h"
#include "SimulatorInterface.h"

//short unsigned int automate_dimension = 1;

// Method to implement

Interface1D::Interface1D(): SimulatorInterface(automate_dimension){
    // Set state list
    possible_state_list = new State*[2];
    possible_state_list[0] = new State("Vivant", "#fffffff");
    possible_state_list[1] = new State("Mort", "#0000000");

    simulator = new Simulator1D();
}

void Interface1D::setSimulatorView(QBoxLayout* parent){
    etats = new QTableWidget;
    resetSimulator();
}

void Interface1D::resetSimulatorView(){
    setInitialStates();

    etats->item(i,j)->setBackgroundColor(Qt::white);
}

void Interface1D::setInitialStates(){
    initial_states = new State*[grid_dimension];
//    for (unsigned int i = 0; i < grid_dimension; i++)
//        initial_states[i] = "";
}
