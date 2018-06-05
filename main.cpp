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
#include "SimulatorLifeGame.h"
#include "Cell.h"
#include "State.h"
#include "Rule.h"

#define uint unsigned int

int main() {
    std::srand(std::time(nullptr));
    std::cout << "Coucou" << std::endl;

    State** states;
    states = new State*[5];

    // On crée 5 états avec les idées {0, 1, 2, 3, 4}
    for (uint i = 0; i < 5; i++)
        states[i] = new State(std::to_string(i));

    // On crée une règle qui prend en compte un ordre de 5 états
    Rule rule1(states[1], states, 5, true);
    states[0]->addANewRule(&rule1);

    // On crée une règle qui demande à ce que les voisins possèdent au moins les 3 états.
    Rule rule2(states[2], states, 3);
    states[0]->addANewRule(&rule2);

    // On crée une règle qui demande à ce qu'au moins 2 voisins aient l'état 2
    std::vector<State*> forRule3({states[2], states[2]});
    Rule rule3(states[3], forRule3);
    states[0]->addANewRule(&rule3);

    // On crée une règle qui demande à ce que les voisins dans l'ordre soient de l'état 2 puis 3 puis 0 puis 3
    std::vector<State*> forRule4({states[2], states[3], states[0], states[3]});
    Rule rule4(states[4], forRule4, true);
    states[0]->addANewRule(&rule4);

    std::vector<State*> forRule5({states[1], states[1], states[1]});
    Rule rule5(states[1], forRule5);
    states[0]->addANewRule(&rule5);

    std::vector<State*> forRule6({states[0], states[1]});
    Rule rule6(states[0], forRule6, true);
    states[1]->addANewRule(&rule6);

    Simulator1D simulation1D(states, 2, 10);
    simulation1D.printCells();
    simulation1D.mutate();
    std::cout << std::endl;
    simulation1D.printCells();

    Simulator2D simulation2D(states, 2, 5);
    simulation2D.printCells();
    simulation2D.mutate();
    std::cout << std::endl;
    simulation2D.printCells();

    Cell cell(states[0]);

    // On donne 4 voisins pour avoir la génération suivante, on respecte donc que la règle 2
    std::cout << "Passage de la cellule à la génération " << cell.getGeneration() << " dans l'état " << cell.getState()->getName();
    cell.mutate(states, 4);
    std::cout << " à la génération " << cell.getGeneration() << " avec l'état " << cell.getState()->getName() << " via la règle 2" << std::endl;

    SimulatorLifeGame simulatorLifeGame(68);
    simulatorLifeGame.printCells();

    while (simulatorLifeGame.mutate()) {
        std::cout << "Génération suivante:" << std::endl;
        simulatorLifeGame.printCells();
        usleep(10000);
    }

    return 0;
}
