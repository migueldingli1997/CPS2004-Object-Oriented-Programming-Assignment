#ifndef TASK2_XORTI_H
#define TASK2_XORTI_H

#include "Space.h"

namespace spaces {

    using namespace core;

    class Xorti final : public Space {

    public:
        /**
         * @param id space ID
         * @param name space name
         */
        Xorti(const uint id, const std::string &name);

        /**
         * Applies one out of the four possible outcomes on the player
         * (birthday, parking fine, MEPA fine, and a change in space).
         * ~Refer to superclass for parameter and return description.
         */
        const std::string
        applyEffect(Player &player, std::vector<Player *> &allPlayers, const GameBoard &board) override;

    private:
        /**
         * OUTCOME 1; A random amount in the range [10, 100]
         * is collected from each other player.
         *
         * @param player main player in consideration
         * @param allPlayers pointers to all players
         * @return the value of the fine applied
         */
        uint birthday(Player &player, std::vector<Player *> &allPlayers);

        /**
         * OUTCOME 2; Player is fined a random amount in the range [40, 180]
         *
         * @param player main player in consideration
         * @param allPlayers pointers to all players
         * @return the value of the fine applied
         */
        uint parkingFine(Player &player, std::vector<Player *> &allPlayers);

        /**
         * OUTCOME 3; Player is fined a random amount in
         * the range [50, 150] for each building owned.
         *
         * @param player main player in consideration
         * @param allPlayers pointers to all players
         * @return the value of the fine applied
         */
        uint mepaFine(Player &player, std::vector<Player *> &allPlayers);

        /**
         * OUTCOME 4; Advances player to a random position on the board.
         *
         * @param player main player in consideration
         * @param allPlayers pointers to all players
         * @param board the game board
         */
        void advanceToNewSpace(Player &player, std::vector<Player *> &allPlayers, const GameBoard &board);
    };
}

#endif //TASK2_XORTI_H
