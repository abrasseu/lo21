#include "Interface1D.h"
#include "SimulatorInterface.h"

//short unsigned int automate_dimension = 1;

// Method to implement

Interface1D::Interface1D(): SimulatorInterface(automate_dimension){
    // Set state list
    possible_state_list = new State*[2];
    possible_state_list[0] = new State("Mort", "#0000000");
    possible_state_list[1] = new State("Vivant", "#fffffff");

    resetSimulatorView(view_layout);
//    simulator = new Simulator1D();
}

void Interface1D::setSimulatorView(QBoxLayout* parent){
//    etats = new QTableWidget;
    resetSimulatorView(parent);
}

void Interface1D::resetSimulatorView(QBoxLayout* parent){
    setInitialStates();

    if (grid_view != nullptr)
        delete grid_view;
    grid_view = new QTableWidget(1, grid_dimension);
    parent->addWidget(grid_view);


    grid_view->setFixedSize(grid_size + grid_dimension/5, grid_size/grid_dimension);
    grid_view->horizontalHeader()->setVisible(false);
    grid_view->verticalHeader()->setVisible(false);
    grid_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grid_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (unsigned int i = 0; i < grid_size; i++){
        grid_view->setColumnWidth(i, grid_size/grid_dimension);
        grid_view->setItem(0, i, new QTableWidgetItem(""));
//        grid_view->item(0, i)->setBackgroundColor(Qt::white);
    }

    QObject::connect(grid_view, SIGNAL(cellClicked(int,int)), this, SLOT(rotateCellState(int, int)));
}

void Interface1D::setInitialStates(){
    initial_states = new State*[grid_dimension];
    for (unsigned int i = 0; i < grid_dimension; i++)
        initial_states[i] = possible_state_list[0];
}



// === Grid Slots

void Interface1D::rotateCellState(int i, int j){
    if (changeCellEnabled){
        if (grid_view->item(i,j)->backgroundColor()== Qt::black)
            grid_view->item(i,j)->setBackgroundColor(Qt::white);
        else
            grid_view->item(i,j)->setBackgroundColor(Qt::black);
    }
}
