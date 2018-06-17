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

    try {
        SimulatorManager* manager(SimulatorManager::getManager());

        manager->createNewState("Blink", "#0033FF");
        manager->createNewState("Unblink", "#FFFFFF");

        manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(0)}, manager->getState(1)));
        manager->getState(1)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1)}, manager->getState(0)));

        manager->setGridSize(10);
        manager->createSimulator(1);
        manager->getSimulator()->printCells();

        manager->exportConfig("../saves/blinker.json");
        manager->getSimulator()->mutate();
        manager->getSimulator()->printCells();
        std::cout << std::endl;

        // Jeu de la vie
        manager->removeState(manager->getState(0));
        manager->removeState(manager->getState(0));

        manager->createNewState("Vivant", "#000000");
        manager->createNewState("Mort", "#FFFFFF");

        manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1)}, manager->getState(1)));
        manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(0)}, manager->getState(1)));
        manager->getState(1)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(0), manager->getState(0), manager->getState(0), manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1), manager->getState(1)}, manager->getState(0)));

        manager->setGridSize(10);
        manager->createSimulator(2);
        manager->getSimulator()->generateRandomCells();
        manager->getSimulator()->printCells();
        manager->getSimulator()->mutate();
        manager->getSimulator()->printCells();
        manager->exportConfig("../saves/life_game.json");
        std::cout << std::endl;

        manager->importConfig("../saves/life_game.json");
        manager->getSimulator()->printCells();
        std::cout << std::endl;

        manager->getSimulator()->resetToInitialCells();
        manager->getSimulator()->printCells();
        manager->getSimulator()->mutate();
        manager->getSimulator()->printCells();

        // Jeu WalkingDead
        manager->removeState(manager->getState(0));
        manager->removeState(manager->getState(0));

        manager->createNewState("Humain", "#000000");
        manager->createNewState("Militaire", "#663300");
        manager->createNewState("Zombie", "#FF0000");
        manager->createNewState("Mort", "#FFFFFF");

        manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(1), manager->getState(1)}, manager->getState(1)));
        manager->getState(0)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(2)}, manager->getState(2)));
        manager->getState(1)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(2), manager->getState(2)}, manager->getState(2)));
        manager->getState(2)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(1), manager->getState(1)}, manager->getState(3)));
        manager->getState(2)->addANewRule(manager->createNewRule(std::vector<State*>{manager->getState(2), manager->getState(2), manager->getState(2), manager->getState(2)}, manager->getState(3)));

        manager->setGridSize(25);
        manager->createSimulator(2);
        manager->exportConfig("../saves/walking_dead.json");
        std::cout << std::endl;
    } catch (SimulatorException e) {
        std::cout << e.what();
    }

    return 0;
}
