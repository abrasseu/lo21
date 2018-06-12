#include <iostream>
#include <ctime>
#include <unistd.h>

#include "autocell/SimulatorManager.h"
#include "autocell/Simulator1D.h"
#include "autocell/Simulator2D.h"
#include "autocell/SimulatorLifeGame.h"
#include "autocell/Cell.h"
#include "autocell/State.h"
#include "autocell/Rule.h"

#include "interface/inclu_fich.h"

using uint = unsigned int;
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(nullptr));
	cout << "Coucou" << endl;


	/*
	// Managers
	SimulatorManager* simulatorManager = SimulatorManager::getManager();

	State** states;
	states = new State*[5];

	// On crée 5 états avec les idées {0, 1, 2, 3, 4}
	for (uint i = 0; i < 5; i++)
		states[i] = new State(to_string(i));

	// On crée une règle qui prend en compte un ordre de 5 états
	Rule rule1(states[1], states, 5, true);
	states[0]->addANewRule(&rule1);

	// On crée une règle qui demande à ce que les voisins possèdent au moins les 3 états.
	Rule rule2(states[2], states, 3);
	states[0]->addANewRule(&rule2);

	// On crée une règle qui demande à ce qu'au moins 2 voisins aient l'état 2
	vector<State*> forRule3({states[2], states[2]});
	Rule rule3(states[3], forRule3);
	states[0]->addANewRule(&rule3);

	// On crée une règle qui demande à ce que les voisins dans l'ordre soient de l'état 2 puis 3 puis 0 puis 3
	vector<State*> forRule4({states[2], states[3], states[0], states[3]});
	Rule rule4(states[4], forRule4, true);
	states[0]->addANewRule(&rule4);

	vector<State*> forRule5({states[1], states[1], states[1]});
	Rule rule5(states[1], forRule5);
	states[0]->addANewRule(&rule5);

	vector<State*> forRule6({states[0], states[1]});
	Rule rule6(states[0], forRule6, true);
	states[1]->addANewRule(&rule6);

	Simulator1D simulation1D(states, 2, 10);
	simulation1D.printCells();
	simulation1D.mutate();
	cout << endl;
	simulation1D.printCells();

	Simulator2D simulation2D(states, 2, 5);
	simulation2D.printCells();
	simulation2D.mutate();
	cout << endl;
	simulation2D.printCells();

	Cell cell(states[0]);

	// On donne 4 voisins pour avoir la génération suivante, on respecte donc que la règle 2
	cout << "Passage de la cellule à la génération " << cell.getGeneration() << " dans l'état " << cell.getState()->getName();
	cell.mutate(states, 4);
	cout << " à la génération " << cell.getGeneration() << " avec l'état " << cell.getState()->getName() << " via la règle 2" << endl;

	SimulatorLifeGame simulatorLifeGame(68);
	simulatorLifeGame.printCells();

	while (simulatorLifeGame.mutate()) {
		cout << "Génération suivante:" << endl;
		simulatorLifeGame.printCells();
		usleep(10000);
	}
	*/
	return 0;
}
