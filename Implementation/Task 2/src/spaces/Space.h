#ifndef TASK2_SPACE_H
#define TASK2_SPACE_H

#include <string>
#include <vector>
#include "Space.h"

namespace core {

    class Player;

    class GameBoard;
}

namespace spaces {

    using namespace std;
    using namespace core;

    class Space {

    public:
        virtual ~Space();

        /**
         * Function called when a player lands on the space.
         * It has the ability to manipulate all players.
         *
         * @param player player that landed on the space
         * @param allPlayers pointers to all players
         * @param board game board with all spaces
         * @return message stating what happened.
         */
        virtual const std::string
        applyEffect(Player &player, std::vector<Player *> &allPlayers, const core::GameBoard &board) = 0;

        /**
         * Returns id of space
         */
        const uint getId() const;

        /**
         * Returns name of space
         */
        const std::string getName() const;

        /**
         * Checks if the space IDs are equal.
         *
         * @param space space to compare to
         * @return true if space IDs are equal
         */
        bool operator==(const Space &space) const;

        /**
         * Checks if the space IDs are NOT equal.
         *
         * @param space space to compare to
         * @return true if space IDs are not equal
         */
        bool operator!=(const Space &space) const;

        /**
         * Adds the space's name to the output stream.
         *
         * @param os output stream
         * @param s space to output
         * @return stream with space's name
         */
        friend ostream &operator<<(ostream &os, const Space &s);

    protected:
        const uint id; // Space ID
        const std::string name; // Space name

        /**
         * @param id space ID
         * @param name space name
         */
        Space(const uint id, const std::string &name);
    };
}

#endif //TASK2_SPACE_H
