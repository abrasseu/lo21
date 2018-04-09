#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include "etat.h"
#include "automate.h"

/**
 * === TODO ===
 * - [ ] Iterator
 * - [ ] Singleton
 */

class Simulateur
{
	private:
		// Attributs
		const Automate& automate;
		Etat** etats;
		const Etat* depart = nullptr;
		unsigned int nbMaxEtats;
		unsigned int rang = 0;

		// Iterator
		class Iterator {
			private:
				friend class Simulateur;
				Simulateur* sim;
				int rangCourant;
				Iterator(Simulateur* s) : sim(s) { rangCourant = sim->rang; }
			public:
				void next() { rangCourant--; }
				Etat& current() const {
					return *sim->etats[ rangCourant % sim->getNbMaxEtats() ];
				}
				bool isDone() const {
					return (rangCourant == -1) ||  (rangCourant == sim->rang - sim->getNbMaxEtats());
				}
		};
		friend class Iterator;

		// Constant Iterator
		class ConstIterator {
			private:
				friend class Simulateur;
				const Simulateur* sim;
				int rangCourant;
				ConstIterator(const Simulateur* s) : sim(s) {}
			public:
				void next() { rangCourant--; }
				Etat& current() const {
					return *sim->etats[ rangCourant % sim->getNbMaxEtats() ];
				}
				bool isDone() const {
					return (rangCourant == -1) ||  (rangCourant == sim->rang - sim->getNbMaxEtats());
				}
		};
		friend class ConstIterator;

		// Iterator c++
		class iterator {
			private:
				friend class Simulateur;
				const Simulateur* sim;
				int rangCourant;
				iterator(const Simulateur* s) : sim(s) {}
				iterator(const Simulateur* s, int r) : sim(s), rangCourant(r) {}
			public:
				void operator++() { rangCourant--; }
				Etat& operator *() const {
					return *sim->etats[ rangCourant % sim->getNbMaxEtats() ];
				}
				bool operator !=(const iterator it) const {
					return sim != it.sim || rangCourant != it.rangCourant;
				}
				bool isDone() const {
					return (rangCourant == -1) ||  (rangCourant == sim->rang - sim->getNbMaxEtats());
				}
		};
		friend class iterator;
		iterator begin() {
			return iterator(this);
		}
		iterator end() {
			if (rang < nbMaxEtats)
				return iterator(this, -1);
			else
				return iterator(this); // ?????
		}

	public:
		// Iterators
		Iterator getIterator() { return Iterator(this); }
		ConstIterator getIterator() const { return ConstIterator(this); }

		// Constructeurs & Destructeurs
		Simulateur(const Automate&, unsigned int);
		Simulateur(const Automate&, const Etat&, unsigned int);	// buf =2
		~Simulateur();

		// Accesseurs & Mutateurs
		const Etat& dernier() const;
		unsigned int getDernierRang() const;
		unsigned int getNbMaxEtats() const;
		const Automate& getAutomate() const;
		const Etat& getEtat(unsigned int) const;



		// Spécifiques
		void setEtatDepart(const Etat&);
		void next();
		void run(unsigned int, bool = false);
		void reset();

};

std::ostream& operator <<(std::ostream&, const Simulateur&);


class SimulateurException
{
	private:
		std::string info;
	public:
		SimulateurException(const std::string& message) : info(message) {}
		std::string getInfo() const { return info; }
};

#endif // SIMULATEUR_H
