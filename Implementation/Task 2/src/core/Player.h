#ifndef TASK2_PLAYER_H
#define TASK2_PLAYER_H

#include <vector>
#include <string>

namespace spaces {

    class Space;

    class Property;
}

namespace core {

    using namespace spaces;

    class DicePair;

    class Player final {

    public:
        /**
         * @param id unique player ID
         * @param name unique player name
         * @param startBalance starting balance
         * @param startSpace starting space (only ID is taken)
         */
        Player(const uint id, const std::string &name, uint startBalance, const Space *startSpace);

        /**
         * Increases the player's balance by the specified integer amount.
         */
        void gainMoney(const uint amount);

        /**
         * Decreases the player's balance by the specified integer amount.
         */
        void loseMoney(const uint amount) throw();

        /**
         * Checks if the player affords losing the specified integer amount.
         *
         * @return true if the player affords
         */
        bool affords(const uint amount) const;

        /**
         * Adds the specified property to the
         * vector of properties owned by the player.
         */
        void addProperty(Property &prop);

        /**
         * Removes the specified property from the
         * vector of properties owned by the player.
         */
        void removeProperty(const Property &prop);

        /**
         * Player is expected to roll the specified
         * DicePair by calling the dice's roll method.
         */
        void rollDice(DicePair &toRoll) const;

        /**
         * Returns value of variable 'balance'
         */
        uint getBalance() const;

        /**
         * Returns the ID of the player's current space
         */
        const uint getCurrSpaceId() const;

        /**
         * Returns the vector 'properties' of pointers to owned properties
         */
        const std::vector<Property *> &getProps() const;

        /**
         * Returns the value of variable 'bankrupt'
         */
        bool isBankrupt() const;

        /**
         * Sets the current space ID to the specified space's ID
         *
         * @param newSpace pointer to the space to advance to
         */
        void advanceTo(const Space *newSpace);

        /**
         * Player is set to bankrupt (i.e. bankrupt set to true)
         */
        void setToBankrupt();

        /**
         * Returns the player's name
         */
        const std::string getName() const;

        /**
         * Checks if the player IDs are equal
         *
         * @param player player to compare to
         * @return true if player IDs are equal
         */
        bool operator==(const Player &player) const;

        /**
         * Checks if the player IDs are not equal
         *
         * @param player player to compare to
         * @return true if player IDs are not equal
         */
        bool operator!=(const Player &player) const;

        /**
         * Adds the player's name to the output stream
         *
         * @param os output stream
         * @param p player to output
         * @return stream with player's name
         */
        friend std::ostream &operator<<(std::ostream &os, const Player &p);

    private:
        const uint id; // player ID
        const std::string name; // player name
        uint balance; // player's balance
        uint currentSpaceId; // ID of the space the player is at
        std::vector<Property *> properties; // owned properties
        bool bankrupt; // indicates if player is bankrupt
    };
}

#endif //TASK2_PLAYER_H
