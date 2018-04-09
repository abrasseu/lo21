#include "automate.h"
#include "simulateur.h"

#include "iostream"
#include "string"

using namespace std;

/* =======================================================
 *		Constructeurs & Destructeurs
 * =======================================================
 */

Simulateur::Simulateur(const Automate& a, unsigned int buffer = 2): automate(a), depart(nullptr), nbMaxEtats(buffer), rang(0){
	etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++)
		etats[i] = nullptr;
}

Simulateur::Simulateur(const Automate& a, const Etat& e, unsigned int buffer = 2): automate(a), depart(&e), nbMaxEtats(buffer), rang(0) {
	etats = new Etat*[nbMaxEtats];
	etats[0] = new Etat(*depart);		// Recopie
	for (unsigned int i = 1; i < nbMaxEtats; i++)
		etats[i] = nullptr;
}


Simulateur::~Simulateur() {
	for (unsigned int i = 0; i < nbMaxEtats; i++)
		delete etats[i];
	delete[] etats;
}


/* =======================================================
 *		Accesseurs & Mutateurs
 * ==========================s=============================
 */
const Etat& Simulateur::dernier() const {
	if (depart == nullptr)
		throw SimulateurException("Etat de départ non défini");
	return *etats[rang % nbMaxEtats];
}
unsigned int Simulateur::getDernierRang() const {
	return rang;
}
unsigned int Simulateur::getNbMaxEtats() const {
	return nbMaxEtats;
}
const Automate& Simulateur::getAutomate() const {
	return automate;
}
const Etat& Simulateur::getEtat(unsigned int i) const {
	if (i < rang)
		return *etats[i % nbMaxEtats];
	else
		throw SimulateurException("Etat " + to_string(i) + " non défini");
}



/* =======================================================
 *		Fonctions Spécifiques
 * =======================================================
 */

void Simulateur::next() {
	if (depart == nullptr)
		throw SimulateurException("Etat de depart non defini");
	rang++;
	if (etats[rang % nbMaxEtats] == nullptr)
		etats[rang % nbMaxEtats] = new Etat(0);
	automate.appliquerTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang % nbMaxEtats]);
}

void Simulateur::run(unsigned int nbSteps, bool verbose) {
	for (; nbSteps > 0; nbSteps--) {
		next();
		if (verbose)
			cout << rang << " : " << *etats[rang % nbMaxEtats] << endl;
	}
}

void Simulateur::setEtatDepart(const Etat& e) {
	depart = &e;
	if (etats[0] == nullptr)
		etats[0] = new Etat(e);		// Copie
	else
		*etats[0] = e;				// Affectation
}

void Simulateur::reset() {
	if (depart == nullptr)
		throw SimulateurException("Etat de départ non défini");
	rang = 0;
	etats[0] = nullptr;
}



/* =======================================================
 *		Opérateurs
 * =======================================================
 */

std::ostream& operator <<(std::ostream& f, const Simulateur& s) {
	unsigned int dernier = s.getDernierRang();
	f << "Simulateur de " << dernier << " états sur un buffer de " << s.getNbMaxEtats() << endl;
	f << "Automate correspondant " << s.getAutomate().getNumero() << endl;
	if (dernier > 0) {
		f << "Liste des états successifs" << endl;
		for (unsigned int i = 0; i < dernier; i++)
			f << i << ": " << s.getEtat(i) << endl;
		f << "Fin de la liste" << endl;
	} else
		cout << "Aucun état défini" << endl;
	return f;
}
