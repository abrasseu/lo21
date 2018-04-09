#include "etat.h"
#include "automate.h"
#include "simulateur.h"
#include "automate-manager.h"

#include "string"

using namespace std;


/* =======================================================
 *		Constructeur & Destructeur
 * =======================================================
 */

AutomateManager::AutomateManager() {
	for (unsigned int i = 0;  i < 256; i++)
		automates[i] = nullptr;
}

AutomateManager::~AutomateManager() {
	for (unsigned int i = 0;  i < 256; i++)
		delete automates[i];
	delete[] automates;
}



/* =======================================================
 *		Fonctions Spécifiques
 * =======================================================
 */

// AutomateManager* AutomateManager::instance = nullptr;
AutomateManager::Handler AutomateManager::handler = AutomateManager::Handler();

AutomateManager& AutomateManager::getInstance() {
	// static AutomateManager instance;
	if (handler.instance == nullptr)
		handler.instance = new AutomateManager;
	return *handler.instance;
}

void AutomateManager::libererInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}

const Automate& AutomateManager::getAutomate(unsigned int i) {
	if (i > 255)
		throw AutomateException("L'automate n° " + to_string(i) + " n'existe pas.");
	if (automates[i] == nullptr)
		automates[i] = new Automate(i);
	return *automates[i];
}





