#ifndef STATEINTERFACE_H
#define STATEINTERFACE_H
#include "SimulatorInterface.h"

#include <QLineEdit>
#include <QPalette>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVector>

class StateInterface : public QHBoxLayout {
        Q_OBJECT
    private:
        friend class SimulatorInterface;
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
        QPalette* state_color;
        QLabel* state_color_label;


//        QPushButton* state_delete;

        // Agencement
        void setNameLayout(QBoxLayout*);
        void setColorLayout(QBoxLayout*);

    public:
        StateInterface();
        StateInterface(std::string, std::string);


    protected slots:
        void display_palette_color(QTableWidgetItem*);
//        void delete_state();
};


#endif // STATEINTERFACE_H
