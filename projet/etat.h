#ifndef ETAT_H
#define ETAT_H

#include <string>
#include <iostream>

class Etat
{
	private:
		unsigned int dimension = 0;
		bool* valeur = nullptr;

	public:
		// Constructeurs & Destructeurs
		Etat(unsigned int);
		Etat(const Etat&);
		~Etat();

		// Accesseurs & Mutateurs
		unsigned int getDimension() const { return dimension; }
		bool getCellule(unsigned int) const;
		bool setCellule(unsigned int, bool);

		// Opérateurs
		Etat& operator =(const Etat&);
};


class EtatException {
	private:
		std::string info;
	public:
		EtatException(const std::string& message) : info(message) {}
		std::string getInfo() const { return info; }

};


std::ostream& operator <<(std::ostream&, const Etat&);



#endif // ETAT_H
