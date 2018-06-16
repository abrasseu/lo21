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

    manager->createNewState("Mort", "#FFFFFF");
    manager->createNewState("Vivant", "#000000");

    manager->getState(1)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0)}, manager->getState(0)));
    manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0)}, manager->getState(1)));
    manager->getState(1)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1)}, manager->getState(0)));

    manager->setGridSize(50);
    manager->createSimulator(2);

    manager->exportConfig("../saves/life_game.json");

    return 0;
}
