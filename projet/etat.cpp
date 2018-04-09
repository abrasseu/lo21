#include "etat.h"
#include <iostream>

using namespace std;

/**
 *	===== TODO ====
 *
 * - gérer les exceptions
 */


// =============================================
//		Constructeurs & Destructeurs
// =============================================

Etat::Etat(unsigned int n = 0) : dimension(n), valeur(nullptr) {
	// Allocation du tableau d'états tous à 0
	valeur = new bool[n];
	for (unsigned int i = 0; i < dimension; i++)
		valeur[i] = false;
}

// Constructeur de recopie
Etat::Etat(const Etat& e) : dimension(e.dimension), valeur(nullptr) {
	if (dimension <= 0)
		throw EtatException("La dimension doit être strictement positive");

	valeur = new bool[dimension];
	for (unsigned int i = 0; i < dimension; i++)
		valeur[i] = e.valeur[i];
}


Etat::~Etat() {
	delete[] valeur;
}


// =============================================
//		Accesseurs & Mutateurs
// =============================================

bool Etat::getCellule(unsigned i) const {
	if (i >= dimension)
		throw EtatException("Cellule inexistante");
	return valeur[i];
}

bool Etat::setCellule(unsigned int i, bool val) {
	if (i >= dimension)
		throw EtatException("Cellule inexistante");
	return valeur[i] = val;
}



// =============================================
//		Opérateurs
// =============================================

Etat& Etat::operator =(const Etat& e) {
	// Évite l'Auto-affectation
	if (this != &e) {
		// Dimension différente => réaffectation de valeurs
		if (dimension != e.dimension) {
			delete[] valeur;
			dimension = e.dimension;
			valeur = new bool[dimension];
		}
		// Affectation
		for (unsigned int i = 0; i < dimension; i++)
			valeur[i] = e.valeur[i];
	}
}

ostream& operator <<(ostream& f, const Etat& e) {
	f << "[";
	for (unsigned int i = 0; i < e.getDimension(); i++)
		f << e.getCellule(i);
	f << "]";
	return f;
}


