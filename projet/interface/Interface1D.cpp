#include "Interface1D.h"
#include "SimulatorInterface.h"
#include "autocell/Rule.h"
#include <QMessageBox>

// short unsigned int automate_dimension = 1;

Interface1D::Interface1D(): SimulatorInterface(automate_dimension), buffer_size(10) {
    // Set state list
    setGridBufferLength(grid_dim_controls);
    possible_state_list = new State*[2];
    possible_state_list[0] = new State("Mort", "#000000");
    possible_state_list[1] = new State("Vivant", "#ffffff");

    simulator = new Simulator1D(possible_state_list, 2, grid_dimension);
    initSimulatorView(view_layout);
}

void Interface1D::setGridBufferLength(QBoxLayout* parent){
    grid_buffer_length_controls = new QVBoxLayout;
    parent->addLayout(grid_buffer_length_controls);
    grid_buffer_length_select = new QHBoxLayout;
    grid_buffer_length_bts_layout = new QHBoxLayout;
    grid_buffer_length_controls->addLayout(grid_buffer_length_select);
    grid_buffer_length_controls->addLayout(grid_buffer_length_bts_layout);

    grid_buffer_length_label = new QLabel("Choisissez le nombre de buffers: ");
    grid_buffer_length_select->addWidget(grid_buffer_length_label);
    grid_buffer_length_spin = new QSpinBox;
    grid_buffer_length_spin->setRange(0,100);
    grid_buffer_length_spin->setValue(10);
    grid_buffer_length_select->addWidget(grid_buffer_length_spin);

    grid_buffer_length_valid = new QPushButton("Valider");
    grid_buffer_length_reset = new QPushButton("Reset");
    grid_buffer_length_bts_layout->addWidget(grid_buffer_length_valid);
    grid_buffer_length_bts_layout->addWidget(grid_buffer_length_reset);

    QObject::connect(grid_buffer_length_valid, SIGNAL(clicked()), this, SLOT(grid_set_buf()));
    QObject::connect(grid_buffer_length_reset, SIGNAL(clicked()), this, SLOT(grid_reset_buf()));
}

void Interface1D::initSimulatorView(QBoxLayout* parent){
    setInitialStates();

    // Initialisation de la ligne de départ
    if (initial_view != nullptr)
        delete initial_view;
    initial_view = new QTableWidget(1, grid_dimension);
    parent->addWidget(initial_view);

    drawGrid(initial_view, 1, grid_dimension);

    // Initialisation du simulateur à state[0]
    simulator->generateStateCells(0);

    QObject::connect(initial_view, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(rotateCellState(QTableWidgetItem*)));

    // Initialisation de la grille d'affichage
    if (grid_view != nullptr)
        delete grid_view;
    grid_view = new QTableWidget(buffer_size, grid_dimension);
    parent->addWidget(grid_view);

    drawGrid(grid_view, buffer_size, grid_dimension);

    QObject::connect(grid_view, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(grid_view_clicked(QTableWidgetItem*)));
}

void Interface1D::drawGrid() {

}

void Interface1D::drawGrid(QTableWidget* grid, uint nbRow, uint nbColumn){
    // nbRow if one line table
    if (nbRow == 1)
        grid->setFixedSize(grid_size, grid_size/nbColumn);
    else
        grid->setFixedSize(grid_size, grid_size);
    grid->horizontalHeader()->setVisible(false);
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set size of cells
    for (unsigned int i = 0; i < nbColumn; i++){
        grid->setColumnWidth(i, grid_size/nbColumn);
        grid->setRowHeight(i, grid_size/nbRow);
        if (nbRow != 1){
            for (uint j = 0; j < nbRow; j++)
                grid->setItem(j, i, new QTableWidgetItem(""));
        }
        else
            grid->setItem(0, i, new QTableWidgetItem(""));
//        grid->item(0, i)->setBackgroundColor(Qt::white);
    }
}

void Interface1D::changeGridCells(){
    if (simulator->getGeneration() > buffer_size){
        for (uint i = 0; i < buffer_size - 1; i++){
            for (uint j = 0; j < grid_dimension; j++){
                grid_view->item(i, j)->setBackgroundColor(grid_view->item(i + 1, j)->backgroundColor());
            }
        }
    }

    QColor color = QColor();
    for (uint i = 0; i < grid_dimension; i++){
        color.setNamedColor(QString::fromStdString(simulator->getCell(i)->getColor()));
        grid_view->item(simulator->getGeneration(), i)->setBackgroundColor(color);
    }
}

void Interface1D::setInitialStates(){
    initial_states = new State*[grid_dimension];
    for (unsigned int i = 0; i < grid_dimension; i++)
        initial_states[i] = possible_state_list[0];
}



// === Grid Slots

void Interface1D::rotateCellState(QTableWidgetItem* it){
    it->setSelected(false);
    if (changeCellEnabled) {
        simulator->incrementState(it->column(), false);
        QColor color;
        color.setNamedColor(QString::fromStdString(simulator->getCell(it->column())->getColor()));
        initial_view->item(0, it->column())->setBackgroundColor(color);
    }
}


// === Buffer Slots

void Interface1D::grid_set_buf(){
    buffer_size = grid_buffer_length_spin->value();
}

void Interface1D::grid_reset_buf(){
    grid_buffer_length_spin->setValue(10);
    buffer_size = grid_buffer_length_spin->value();
}

void Interface1D::grid_view_clicked(QTableWidgetItem* it){
    it->setSelected(false);
}

