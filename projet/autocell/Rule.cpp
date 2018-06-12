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
    // Si on veut exactement le même ordre, il faut déjà qu'on ait la même longueur
    if (_orderedStates) {
        if (_states.size() != size)
            return false;

        for (uint i = 0; i < size; i++) {
            // On compare chacun pour vérifier l'ordre
            if (_orderedStates) {
                if (_states[i] != states[i]) // On ne possède pas les états dans le même ordre
                    return false;
            }
        }

        return true;
    }
    else {
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
}
