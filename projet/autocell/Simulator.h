/**
 * Codé par BRASSEUR Alexandre
 * Codé par NASTUZZI Samy
 *
 * Cette classe permet de gérer chaque simulation
 */

#ifndef __SIMULATOR_H_DEFINE__
#define __SIMULATOR_H_DEFINE__

#include <iostream>
#include <cmath>
#include <string>
#include "SimulatorException.h"
#include "State.h"

using uint = unsigned int;

class Simulator {
	protected:
		const uint _dimension;
		// Liste des états et cellules composant la simulation
		State** _states;
		uint _stateNbr;
		// Cellules actives du simulateur
		State** _cells;
		uint _cellsSize;
		uint _generation;

		// Getters
		uint getDimension() const { return _dimension; }
		virtual State** getNeighboursState(State** states, uint position) = 0;
		void generateCells();

	public:
		/**
		 * @brief Simulator
		 * @param states: State** la liste des états possibles
		 * @param stateNbr: le nombre d'états possibles
		 * @param cellsSize: le nombre de cellules en culture
		 * @param dimension: la dimension du Simulator
		 */
		Simulator(State** states, uint stateNbr, uint cellsSize, uint dimension): _dimension(dimension), _states(states),
			_stateNbr(stateNbr), _cellsSize(cellsSize), _generation(0) {
			generateCells();
		}
		virtual ~Simulator() {
			delete[] _states;
			delete[] _cells;
		}

		// Generators
		void generateStateCells(uint s = 0);
		void generateRandomCells();
		void generateHorizontalSymetricRandomCells();
		void generateVerticalSymetricRandomCells();
		void generateAlternedCells();
		void generateDescAlternedCells();

		// Getters
		uint getNeighbourNbr() const { return pow(3, getDimension()) - 1; }
		State** getInitStates() const { return _states; }
		uint getStateNbr() const { return _stateNbr; }
		uint getCellsSize() const { return _cellsSize; }
		uint getCellsNbr() const { return pow(_cellsSize, getDimension()); }
		State** getCellsState() const;
		State* getCell(uint position) const;
		uint getGeneration() const { return _generation; }
		uint* getCells(); // Seulement pour le JDV
		virtual void printCells() = 0;

		// Setters
		bool setCell(State* state, uint position);


		virtual bool mutate();		// Mute et renvoi vrai si les cellules ont changé
		void incrementState(uint position, bool allowNullState = false);

};

#endif
