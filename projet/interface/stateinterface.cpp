#include "StateInterface.h"

#include <QColorDialog>

StateInterface::StateInterface(): QHBoxLayout() {
    // Layout contenant une règle d'état entière
    state_layout = new QHBoxLayout;
    this->addLayout(state_layout);
    state_layout->setAlignment(Qt::AlignTop);

    // Layout contenant les widgets
//    name_layout = new QVBoxLayout;
//    state_layout->addLayout(name_layout);
    setNameLayout(state_layout);

//    color_layout = new QVBoxLayout;
//    state_layout->addLayout(color_layout);
    setColorLayout(state_layout);
}

StateInterface::StateInterface(std::string name, std::string color): QHBoxLayout() {
    // Layout contenant une règle d'état entière
    state_layout = new QHBoxLayout;
    this->addLayout(state_layout);
    state_layout->setAlignment(Qt::AlignTop);

    // Layout contenant les widgets
    name_layout = new QVBoxLayout;
    state_layout->addLayout(name_layout);

    state_name_label = new QLabel("Nom de l'état :");
    name_layout->addWidget(state_name_label);

    state_name = new QLineEdit;
    state_name->setText(QString::fromStdString(name));
    state_name->setEnabled(false);
    name_layout->addWidget(state_name);


    color_layout = new QVBoxLayout;
    state_layout->addLayout(color_layout);

    state_color_label = new QLabel("Couleur de l'état :");
    color_layout->addWidget(state_color_label);

    color_button = new QTableWidget(1,1);
    color_button->setFixedSize(20,20);
    color_button->horizontalHeader()->setVisible(false);
    color_button->verticalHeader()->setVisible(false);
    color_button->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    color_button->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    color_button->setEditTriggers(QAbstractItemView::NoEditTriggers);
    color_button->setItem(0, 0, new QTableWidgetItem(""));
//    color_button = new QPushButton("Choisir couleur");
    color_layout->addWidget(color_button);

    QColor color_to_set = QColor();
    color_to_set.setNamedColor(QString::fromStdString(color));
    color_button->item(0, 0)->setBackground(QBrush(color_to_set, Qt::SolidPattern));
}

void StateInterface::setNameLayout(QBoxLayout* parent){
    name_layout = new QVBoxLayout;
    parent->addLayout(name_layout);

    state_name_label = new QLabel("Nom de l'état :");
    name_layout->addWidget(state_name_label);

    state_name = new QLineEdit;
    name_layout->addWidget(state_name);
}

void StateInterface::setColorLayout(QBoxLayout* parent){
    color_layout = new QVBoxLayout;
    parent->addLayout(color_layout);

    state_color_label = new QLabel("Couleur de l'état :");
    color_layout->addWidget(state_color_label);

    color_button = new QTableWidget(1,1);
    color_button->setFixedSize(20,20);
    color_button->horizontalHeader()->setVisible(false);
    color_button->verticalHeader()->setVisible(false);
    color_button->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    color_button->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    color_button->setEditTriggers(QAbstractItemView::NoEditTriggers);
    color_button->setItem(0, 0, new QTableWidgetItem(""));
//    color_button = new QPushButton("Choisir couleur");
    color_layout->addWidget(color_button);
    QObject::connect(color_button, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(display_palette_color(QTableWidgetItem*)));
}

// ==================== Color Slots ====================

void StateInterface::display_palette_color(QTableWidgetItem* button){
    button->setSelected(false);
    QPalette color;
    color.setColor(QPalette::Window, Qt::white);
    QColor couleur = QColorDialog::getColor(Qt::white, color_button);
    color_button->setAutoFillBackground(false);
    color.setColor(QPalette::Window, couleur);
//    color_button->setPalette(color);
//    color_button->setPalette(color);
    color_button->item(0,0)->setBackground(QBrush(couleur));
}
