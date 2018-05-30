#include "automate.h"

#include <string>

using namespace std;


/* =======================================================
 *		Constructeurs & Destructeurs
 * =======================================================
 */
Automate::Automate(short unsigned int n) {
	if (n > 256)
		throw AutomateException("Numéro trop grand");
	numero = n;
	numeroBit = numToBit(n);
}
Automate::Automate(const string& bit) {
	if (bit.size() != 8)
		throw "Numéro d'automate indéfini";
	numeroBit = bit;
	numero = bitToNum(bit);
}


/* =======================================================
 *		Fonctions Spécifiques
 * =======================================================
 */

void Automate::appliquerTransition(const Etat& dep, Etat& dest) const {
	if (dep.getDimension() != dest.getDimension() )
		dest = dep;			// Deux états de la même taille // opérateur = réalloue un tableau de la même taille
	for (unsigned int i = 0; i < dest.getDimension()-1; i++) {
		// quelle configuration?
		unsigned short int conf = 0;
		if (i > 0) // cas où on n'est pas à l'extrémité gauche (on considère qu'à la case -1 et à la case dim sont présents des 0
			conf += dep.getCellule(i - 1) * 4;
		conf += dep.getCellule(i) * 2;
		if (i < dep.getDimension() - 1) // cas où on n'est pas a l'extrémité droite
			conf += dep.getCellule(i + 1);
		dest.setCellule(i, numeroBit[7 - conf] - '0'); // tableau à l'envers pour les bits (commence pour config 111)
															// et on soustrait la valeur de '0' pour otbenir la valeur 0 ou 1
	}
}



short unsigned int Automate::bitToNum(const string& num) {
	if (num.size() != 8)
		throw AutomateException("Numero d'automate indefini");
	int puissance = 1;
	short unsigned int numero = 0;
	for (int i = 7; i >= 0; i--) {
		if (num[i] == '1')
			numero += puissance;
		else if (num[i] != '0')
			throw AutomateException("Numero d'automate indefini");
		puissance *= 2;
	}
	return numero;
}

string Automate::numToBit(short unsigned int num) {
	string numeroBit;
	if (num > 256)
		throw AutomateException("Numero d'automate indefini");
	unsigned short int p = 128;
	int i = 7;
	while (i >= 0) {
		if (num >= p) {
			numeroBit.push_back('1');
			num -= p;
		} else {
			numeroBit.push_back('0');
		}
		i--;
		p = p / 2;
	}
	return numeroBit;
}


