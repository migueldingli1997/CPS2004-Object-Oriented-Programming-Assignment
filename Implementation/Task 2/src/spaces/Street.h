#ifndef TASK2_STREET_H
#define TASK2_STREET_H

#include "Property.h"

namespace spaces {

    class Street final : public Property {

    public:
        /**
         * @param id space ID
         * @param name space name
         * @param group group that property belongs to
         * @param propGroup pointers to all properties in group
         * @param price cost to purchase the property
         * @param rentCost street rent cost
         * @param buildCost cost per house
         */
        Street(const uint id, const std::string &name, const PropGroup group, const std::vector<Property *> &propGroup,
               const uint price, const uint rentCost, const uint buildCost);

        /**
         * Calls the superclass display and prints out an additional
         * two elements containing house cost if output will be in
         * table form or the same values on separate lines, if not.
         *
         * @param table true to output in table form
         */
        void display(const bool table) const override;

        /**
         * Calculated based on the number of houses built on the property
         * and whether the whole property's group is owned by the owner.
         *
         * @return rent to be paid
         */
        uint getRent() const override;

        /**
         * Returns the cost to build a house.
         */
        uint getBuildCost() const;

    protected:
        /**
         * Checks whether the street can be mortgaged or unmortgaged,
         * depending on current state. If will be unmortgaged, checks
         * that player affords. If will be mortgaged, checks that no
         * property owned in the same group has a house built.
         *
         * @return true if mortgaged stated can be switched
         */
        bool canSwitchMortgageState() const override;

    private:
        static const uint MAXHOUSECOUNT = 4; // maximum houses
        uint houseCount = 0; // amount of houses built
        const uint rentCost; // base rent cost
        const uint buildCost; // price per house

        /**
         * Indicates whether the street can be traded, based
         * on the houses built on properties in the same group.
         *
         * @return true if street is tradeable
         */
        bool isTradeable() const override;

        /**
         * @return number of houses built
         */
        uint getHouseCount() const override;

        /**
         * An extension to manageProperty in Property allowing
         * houses to be built or sold from the property menu.
         *
         * @param allPlayers pointers to all players in the game
         */
        void manageProperty(vector<Player *> &allPlayers) override;

        /**
         * Builds a house on the property if the limit has not
         * been exceeded. ALSO takes money from the owner.
         *
         * @return true if house successfully built
         */
        bool buildHouse();

        /**
         * Removes a house from the property if there is at least
         * one house built. ALSO gives money to the owner.
         *
         * @return true if house successfully removed
         */
        bool removeHouse();
    };
}

#endif //TASK2_STREET_H
