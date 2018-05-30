#include <iostream>
#include <vector>
#include "State.h"
#include "Rule.h"

#define uint unsigned int

bool Rule::isRuleCorrect(State** states, uint size) {
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
                if (statesToHave[j] == _states[i]) {
                    statesToHave.erase(statesToHave.begin() + j);

                    break;
                }
            }
        }

        return (statesToHave.size() == 0);
    }
}
