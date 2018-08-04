#include <string>
#include "MenuIO.h"
#include "../core/Player.h"
#include "../spaces/Property.h"

namespace io {

    using namespace std;
    using namespace core;

    uint mainMenuChoice(const Player &player, const bool endTurn) {

        // Reduced menu (i.e. without property options) if player does not own properties
        const bool reduced = player.getProps().size() == 0;

        // Print menu
        const uint options = (uint) mainMenu.size() - (reduced ? 1 : 0);
        for (uint i = 0; i < options; i++) {
            if (endTurn && i == continueOption) {
                println(to_string(i) + ") Continue (end turn)...");
            } else {
                println(mainMenu[i]);
            }
        }
        return intIn(0, (uint) (options + 1));
    }

    uint propertyMenuChoice(const Property &prop) {

        // Reduced menu (i.e. without street options) if property is not a street
        const PropGroup &group = prop.getGroup();
        const bool reduced = group == PropGroup::RAILROAD
                             || group == PropGroup::UTILITY;

        // Used so that menu shows 'unmortgage' if property is mortgaged
        const bool mortgaged = prop.isMortgaged();

        // Print menu;
        const uint options = (uint) propMenu.size() - (reduced ? 2 : 0);
        for (uint i = 0; i < options; i++) {
            if (mortgaged && i == mortgageOption) {
                println(to_string(i) + ") Unmortgage property...");
            } else {
                println(propMenu[i]);
            }
        }
        return intIn(0, options + 1);
    }

    uint recoveryMenuChoice() {

        // Print menu
        const uint options = (uint) recoveryMenu.size();
        for (uint i = 0; i < options; i++) {
            println(recoveryMenu[i]);
        }
        return intIn(0, options + 1);
    }

    void unhandledSwitchCase(const string menuName) {
        println("ERROR : The choice made was not recognized by " + menuName + ".");
    }
}