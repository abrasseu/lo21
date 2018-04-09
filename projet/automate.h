#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include "etat.h"

class Automate
{
	private:
		friend class AutomateManager;	// AutomateManager  devient un constructeur possible d'Automate
		short unsigned int numero;		// Défini les transitions
		std::string numeroBit;

		// Constructeurs & Destructeurs
		Automate(short unsigned int n);
		Automate(const std::string& n);
	public:
		~Automate() = default;
		// Accesseurs
		short unsigned int getNumero() const { return numero; }
		std::string getNumeroBit() const { return numeroBit; }

		// Spécifique
		void appliquerTransition(const Etat&, Etat&) const;
		short unsigned int bitToNum(const std::string&);
		std::string numToBit(short unsigned int);
};


class AutomateException
{
	private:
		std::string info;
	public:
		AutomateException(const std::string& message) : info(message) {}
		std::string getInfo() const { return info; }
};

#endif // AUTOMATE_H
