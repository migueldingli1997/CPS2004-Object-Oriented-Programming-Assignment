#ifndef TASK2_MENUIO_H
#define TASK2_MENUIO_H

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include "GeneralIO.h"
#include "PlayerDecisionIO.h"

namespace spaces {

    class Property;
}

namespace core {

    class Player;
}

namespace io {

    using namespace spaces;
    using namespace core;

    // Main menu
    const uint continueOption = 0; // number corresponding to "Continue" choice
    const std::array<const std::string, 4> mainMenu = {
            "0) Continue (roll dice)...", // Changed to "end turn" if already played
            "1) List player details...",
            "2) List property and group details...",
            "3) Manage owned properties..."
    };

    // Property menu
    const uint mortgageOption = 2; // number corresponding to "Mortgage" choice
    const std::array<const std::string, 6> propMenu = {
            "0) Return to properties management menu...",
            "1) List property details...",
            "2) Mortgage property...", // Changed to "Unmortgage" if mortgaged
            "3) Trade property...",
            "4) Build a house...",
            "5) Sell a house..."
    };

    // Recovery menu
    const std::array<const std::string, 2> recoveryMenu = {"0) Forfeit the game...", "1) Go to Property Manager..."};

    /**
     * Print main menu and ask for a choice.
     *
     * @param player player viewing the menu
     * @param endTurn true if menu should replace "roll dice"
     * with "end turn" when the player has finished the turn.
     * @return player's menu choice
     */
    uint mainMenuChoice(const Player &player, const bool endTurn);

    /**
     * Print property menu and ask for a choice.
     *
     * @param prop Property on which menu is based
     * @return Player's menu choice
     */
    uint propertyMenuChoice(const Property &prop);

    /**
     * Print recovery menu and ask for a choice.
     *
     * @return Player's menu choice
     */
    uint recoveryMenuChoice();

    /**
     * Print a general menu based on the specified vector of pointers and
     * and asks for a choice, starting from a particular choice index
     * [e.g. from 1)]. The specified index is used as an offset since the
     * menu is assumed to startfrom index 0, so the previous indices would
     * have to be printed out before calling this function.
     *
     * @tparam T Type of
     * @param elements The elements to print out
     * @param indexOffset The index to start the menu from
     * @return Value in the range [0, (elementCount-1+offset)]
     */
    template<typename T>
    uint generalMenuChoice(const std::vector<T *> &elements, const uint indexOffset) {

        uint index = indexOffset;
        for (typename std::vector<T *>::const_iterator e = elements.begin(); e < elements.end(); e++) {
            std::cout << index++ << ") " << (**e) << std::endl;
        }
        return intIn(0, (uint) elements.size() - 1 + indexOffset);
    }
}

#endif //TASK2_MENUIO_H
