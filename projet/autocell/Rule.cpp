/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions règles
 */

#include <iostream>
#include <vector>
#include "State.h"
#include "Rule.h"

using uint = unsigned int;

/**
 * \brief Applique la règle si les conditions sont respectées
 * \param states     pointeur de tableau d'états
 * \param size       position de la règle
 */
bool Rule::isTrue(State** states, uint size) {
    std::vector<State*> statesToHave(_states);

    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < statesToHave.size(); j++) {
            if (statesToHave[j] == states[i]) {
                statesToHave.erase(statesToHave.begin() + j);

                break;
            }
        }
    }

    // Si on a tout trouvé, la règle est vraie
    return (statesToHave.size() == 0);
}
