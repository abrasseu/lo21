#include "StateInterface.h"
#include <QColorDialog>

/**
 * \brief Constructeur de l'affichage d'un état
 * \details Crée les layout qui contiennet les différents champs d'affichage d'un état
 * \param n nom de l'état
 * \param c couleur de l'état
 * \param s pointeur de l'état
 */
StateInterface::StateInterface(std::string n, std::string c, State* s): QHBoxLayout(), state(s) {
    // Layout contenant une règle d'état entière
    state_layout = new QHBoxLayout;
    this->addLayout(state_layout);
    state_layout->setAlignment(Qt::AlignTop);

    setNameLayout(state_layout, n);
    setColorLayout(state_layout, c);
}

/**
 * \brief Destructeur de l'affichage d'un état
 */
StateInterface::~StateInterface() {
    delete color_button;
    delete state_color_label;
    delete color_layout;

    delete state_name;
    delete state_name_label;
    delete name_layout;

    delete state_layout;
}

/**
 * \brief Crée et affiche les champs pour entrer le nom de l'état
 * \param parent pointeur sur le layout contenant l'affichage
 * \param name nom de l'état
 */
void StateInterface::setNameLayout(QBoxLayout* parent, std::string name) {
    // Create Layout
    name_layout = new QVBoxLayout;
    parent->addLayout(name_layout);

    // Add Label
    state_name_label = new QLabel("Nom de l'état :");
    state_name_label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    name_layout->addWidget(state_name_label);

    // Add LineEdit
    state_name = new QLineEdit;
    if (!name.empty()) {
        state_name->setText(QString::fromStdString(name));
        state_name->setEnabled(false);
    }
    name_layout->addWidget(state_name);

}

/**
 * \brief Crée et affiche les champs pour entrer la couleur de l'état
 * \param parent pointeur sur le layout contenant l'affichage
 * \param color couleur de l'état
 */
void StateInterface::setColorLayout(QBoxLayout* parent, std::string color){
    // Create Layout
    color_layout = new QVBoxLayout;
    parent->addLayout(color_layout);

    // Add Label
    state_color_label = new QLabel("Couleur de l'état :");
    state_color_label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    color_layout->addWidget(state_color_label);

    // Add Case to select Color
    color_button = new QTableWidget(1,1);
    color_button->setFixedSize(20,20);
    color_button->horizontalHeader()->setVisible(false);
    color_button->verticalHeader()->setVisible(false);
    color_button->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    color_button->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    color_button->setEditTriggers(QAbstractItemView::NoEditTriggers);
    color_button->setItem(0, 0, new QTableWidgetItem());
    color_button->item(0,0)->setBackground(QBrush(Qt::white));

    // Config Color Selection
    color_layout->addWidget(color_button);
    if (color.empty()) {
        QObject::connect(color_button, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(display_palette_color(QTableWidgetItem*)));
    } else {
        QColor color_to_set = QColor();
        color_to_set.setNamedColor(QString::fromStdString(color));
        color_button->item(0, 0)->setBackground(QBrush(color_to_set, Qt::SolidPattern));
    }
}

// ==================== Color Slots ====================
/**
 * \brief Affiche la fenêtre du choix des couleurs pour l'état
 * \details Slot. Ouvre la fenêtre des choix de couleurs lors du clic sur le bouton
 * \param button bouton contenant la couleur choisie pour l'état
 */
void StateInterface::display_palette_color(QTableWidgetItem* button){
    button->setSelected(false);
    // Preset Color
    QPalette color;
    color.setColor(QPalette::Window, Qt::white);

    // Display color
    QColor couleur = QColorDialog::getColor(Qt::white, color_button);
    color_button->setAutoFillBackground(false);

    // Retrieve color & Set it to case
    color.setColor(QPalette::Window, couleur);
    color_button->item(0,0)->setBackground(QBrush(couleur));
}
