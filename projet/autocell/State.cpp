/**
 * Codé par NASTUZZI Samy
 *
 * Définition des fonctions états
 */

#include "State.h"
#include "Rule.h"

using uint = unsigned int;

/**
 * \brief Change les états de génération
 * \param states tableau de pointeurs des états
 * \param size nombre d'états
 * \return Renvoie un \em pointeur \em d' \em état
 */
State* State::getNextGeneration(State** states, uint size) {
    for (Rule* rule : _rules) {
        if (rule->isTrue(states, size))
            return rule->getState();
    }

    return this;
}

/**
 * \brief Ajoute une règle à l'état
 * \param rule pointeur sur la règle à ajouter
 */
void State::addANewRule(Rule* rule) {
    _rules.push_back(rule);
}
