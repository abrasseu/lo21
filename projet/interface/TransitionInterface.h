#ifndef TRANSITIONINTERFACE_H
#define TRANSITIONINTERFACE_H
#include "SimulatorInterface.h"

#include <QDialog>

class TransitionInterface : public QWidget {
    private:
        Q_OBJECT

        // Main Layout
        QVBoxLayout* main_layout;
        QLabel* title;


        // Transition Layout
        QVBoxLayout* transition_layout;

        // Valid PushButton
        QPushButton* transition_valid;

    public:
        TransitionInterface();
};

class Transition : public QHBoxLayout{
    private:
        Q_OBJECT


}



#endif // TRANSITIONINTERFACE_H
