#ifndef TASK2_PROPERTY_H
#define TASK2_PROPERTY_H

#include "Space.h"
#include "GroupEnum.h"

namespace spaces {

    using namespace core;

    class Property : public Space {

    public:
        /**
         * Outputs the property details either in table form or in the form of a list.
         *
         * @param table true to output in table form
         */
        virtual void display(const bool table) const;

        /**
         * If the property is not owned, the player is offered the
         * property at the defined property price. Otherwise, if the
         * player is not the owner, rent has to be paid by the player.
         * ~Refer to superclass for parameter and return description.
         */
        virtual const std::string
        applyEffect(Player &player, std::vector<Player *> &allPlayers, const GameBoard &board) override;

        /**
         * Calculates the rent that a player that landed on this property has to pay.
         *
         * @return rent to be paid by the player
         */
        virtual uint getRent() const = 0;

        /**
         * Puts the current property on aution. Players that
         * are bankrupt are not allowed to participate.
         *
         * @param allPlayers pointers to all players in the game
         * @return message indicating the auction result
         */
        const std::string auction(vector<Player *> &allPlayers);

        /**
         * Gives the owner the option to mortgage/unmortgage the
         * property and to trade the property.
         *
         * @param allPlayers pointers to all players in the game
         */
        virtual void manageProperty(vector<Player *> &allPlayers);

        /**
         * Handles transfer of both property AND MONEY between the current
         * owner and the new owner. Also adds/removes the property from the
         * players' owned properties lists. If no owner, property is just bought.
         *
         * @param newOwner new property owner
         * @param customPrice price at which property is sold
         */
        void transferTo(Player &newOwner, const uint customPrice);

        /**
         * @param player player to check
         * @return true if property is owned by player
         */
        bool isOwnedBy(const Player &player) const;

        /**
         * Returns owner's name ("No Owner" if nullptr).
         */
        const std::string getOwnerName() const;

        /**
         * Sets owner to a nullptr
         */
        void resetOwner();

        /**
         * Returns true if property is mortgaged.
         */
        bool isMortgaged() const;

        /**
         * Returns the number of houses built on the property.
         */
        virtual uint getHouseCount() const;

        /**
         * Returns the property's group.
         */
        PropGroup getGroup() const;

    protected:
        static constexpr float MORTGAGERATE = 0.5; // used to calculate mortgage cost
        static constexpr float UNMORTGAGERATE = 0.55; // used to calculate unmortgage cost

        const PropGroup group; // group that the property belongs to
        const std::vector<Property *> &propGroup; // pointers to properties in the same group
        const uint price; // cost to purchase the property
        Player *owner = nullptr; // pointer to the property owner
        bool mortgaged = false; // indicates whether property is mortgaged

        /**
         * @param id space ID
         * @param name space name
         * @param group group that property belongs to
         * @param propGroup pointers to all properties in group
         * @param price cost to purchase the property
         */
        Property(const uint id, const std::string &name, PropGroup group, const std::vector<Property *> &propGroup,
                 const uint price);

        /**
         * @return number of properties owned from
         * the group that this property belongs to
         */
        uint amountOwnedFromGroup() const;

        /**
         * @return true if property is tradeable
         */
        virtual bool isTradeable() const;

        /**
         * Allows owner to trade the property with a player
         * from the list of players.
         *
         * @param allPlayers pointers to all players in the game
         */
        void tradeManager(vector<Player *> &allPlayers);

        /**
         * Switches the mortgage state if this is possible and
         * takes/gives money from/to the player accordingly.
         */
        void mortgageManager();

        /**
         * Checks whether the property can be mortgaged or
         * unmortgaged, depending on current state. If
         * will be unmortgaged, checks that player affords.
         *
         * @return true if can switch mortgage state
         */
        virtual bool canSwitchMortgageState() const;

    private:

        /**
         * Mortgages/Unmortgages property based on current state and also charges
         * the player (if unmortgage) or gives the player money (if unmortgage).
         *
         * @return amount taken/given from/to the player
         */
        uint switchMortgageState();
    };
}

#endif //TASK2_PROPERTY_H
