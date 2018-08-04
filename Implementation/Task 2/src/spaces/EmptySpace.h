#ifndef TASK2_EMPTYSPACE_H
#define TASK2_EMPTYSPACE_H

#include "Space.h"

namespace spaces {

    using namespace core;

    class EmptySpace final : public Space {

    public:
        /**
         * @param id space ID
         * @param name space name
         */
        EmptySpace(uint id, const std::string &name);

        /**
         * Simply returns a message stating that no change
         * was made to any player.
         * ~Refer to superclass for parameter and return description.
         */
        const std::string
        applyEffect(Player &player, std::vector<Player *> &allPlayers, const GameBoard &board) override;
    };
}

#endif //TASK2_EMPTYSPACE_H
