#ifndef AUTOMATEMANAGER_H
#define AUTOMATEMANAGER_H

#include "etat.h"
#include "automate.h"
#include "simulateur.h"

class AutomateManager
{
	private:
		struct Handler {
			AutomateManager* instance;
			Handler() : instance(nullptr) {}
			~Handler() { delete instance; }
		};
		// static AutomateManager* instance;
		static Handler handler;
		Automate* automates[256];
		AutomateManager();
		~AutomateManager();
	public:
		static AutomateManager& getInstance();
		static void libererInstance();
		const Automate& getAutomate(unsigned int);
};

#endif // AUTOMATEMANAGER_H
