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
        // Attributes
        QLabel* state_name_label;
        QLineEdit* state_name;
        QPalette* state_color;
        QLabel* state_color_label;
        QPushButton* state_delete;

        // Layout
        QHBoxLayout* state_layout;

        QVBoxLayout* name_layout;
        QVBoxLayout* color_layout;

        // Agencement
        void setNameLayout(QBoxLayout*);
        void setColorLayout(QBoxLayout*);

    public:
        StateInterface();
//        StateInterface* StateInterface(const StateInterface&);


    protected slots:

};


#endif // STATEINTERFACE_H
