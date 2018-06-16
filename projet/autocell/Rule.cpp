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

bool Rule::isTrue(State** states, uint size) {
    // On crée un vector tampon
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
