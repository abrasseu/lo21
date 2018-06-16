/**
 * Codé par NASTUZZI Samy
 *
 * Permet de tester la gestion des cellules, des états et des règles
 */

#include <iostream>
#include <ctime>
#include <unistd.h>
#include "Simulator1D.h"
#include "Simulator2D.h"
#include "SimulatorManager.h"
#include "State.h"
#include "Rule.h"

using uint = unsigned int;

int main() {
    std::srand(std::time(nullptr));

    SimulatorManager* manager(SimulatorManager::getManager());

    manager->createNewState("0", "#000000");
    manager->createNewState("1", "#FFFFFF");

    manager->createNewRule(std::vector<State*>{manager->getState(0)}, manager->getState(1));
    manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(0), manager->getState(1), manager->getState(1)}, manager->getState(0));

    manager->getState(0)->addANewRule(manager->getRule(0));
    manager->getState(0)->addANewRule(manager->getRule(1));
    manager->getState(1)->addANewRule(manager->getRule(1));

    manager->setGridSize(2);
    manager->createSimulator(2);
    manager->getSimulator()->mutate();

    manager->exportConfig("../saves/test.json");

    return 0;
}
