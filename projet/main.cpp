//#include <QApplication>
#include <iostream>
#include "etat.h"
#include "automate.h"
#include "simulateur.h"
#include "automate-manager.h"

using namespace std;

int main()
{
	cout << "=== Jeu de la vie ===" << endl;
	Etat e = Etat(5);
	cout << e << endl;

	Automate a = AutomateManager::getInstance().getAutomate(30);

	Simulateur s = Simulateur(a, e, 2);
	//cout << s;
	s.run(15, true);
	//cout << s;

	return 0;
}
