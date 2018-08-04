#ifndef TASK2_TAX_H
#define TASK2_TAX_H

#include "Space.h"

namespace spaces {

    using namespace core;

    class Tax final : public Space {

    public:
        /**
         * @param id space ID
         * @param name space name
         * @param taxCost tax to be paid
         */
        Tax(const uint id, const std::string &name, const uint taxCost);

        /**
         * Makes the player pay tax based on 'taxCost'
         * ~Refer to superclass for parameter and return description.
         */
        const std::string
        applyEffect(Player &player, std::vector<Player *> &allPlayers, const GameBoard &board) override;

    private:
        const uint taxCost; // tax paid by players that land on this space
    };
}

#endif //TASK2_TAX_H
