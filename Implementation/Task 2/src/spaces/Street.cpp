#include "Street.h"
#include "../io/GeneralIO.h"
#include "../core/Player.h"
#include "../io/PropertyMgtIO.h"
#include "../io/DetailsIO.h"
#include "../io/MoneyIO.h"
#include "../io/EngineIO.h"
#include "../io/MenuIO.h"

namespace spaces {

    using namespace std;
    using namespace core;

    Street::Street(const uint id, const string &name, const PropGroup group, const vector<Property *> &propGroup,
                   const uint price, const uint rentCost, const uint buildCost)
            : Property(id, name, group, propGroup, price), rentCost(rentCost), buildCost(buildCost) {}

    void Street::display(const bool table) const {
        Property::display(table);
        if (table) {
            io::printRowElement(houseCount, io::PropTableColWidths::HOUSECOUNT);
            io::printRowElement(buildCost, io::PropTableColWidths::BUILDCOST);
        } else {
            io::println("Houses: " + to_string(houseCount) + " (@ " + to_string(buildCost) + " each)");
        }
    }

    uint Street::getRent() const {
        if (mortgaged) {
            return 0;
        } else if (houseCount > 0) { // implies group is owned
            switch (houseCount) {
                case 1:
                    return rentCost * 5;
                case 2:
                    return rentCost * 15;
                case 3:
                    return rentCost * 45;
                default:
                    return rentCost * 80;
            }
        } else if (amountOwnedFromGroup() == propGroup.size()) {
            return rentCost * 2;
        } else {
            return rentCost;
        }
    }

    uint Street::getBuildCost() const {
        return buildCost;
    }

    bool Street::canSwitchMortgageState() const {

        /*
         * If going to mortgage, check if group allows it. Note that
         * for a property in the group to have a house built, the
         * group would have to be owned by the owner of this street.
         */
        if (!mortgaged) {
            for (vector<Property *>::const_iterator groupP = propGroup.begin(); groupP < propGroup.end(); groupP++) {
                if ((*groupP)->getHouseCount() > 0) {
                    io::cannotMortgageHasHouses(**groupP);
                    return false;
                }
            }
        }
        return Property::canSwitchMortgageState(); // check rest of conditions
    }

    bool Street::isTradeable() const {

        // Cannot trade if has houses
        if (houseCount == 0) {
            // Check if group allows trading
            for (vector<Property *>::const_iterator groupP = propGroup.begin(); groupP < propGroup.end(); groupP++) {
                if ((*groupP)->getHouseCount() > 0) { // owners needn't be checked since must be same to build houses
                    io::cannotTradeHasHouses(**groupP);
                    return false;
                }
            }
            return true;
        } else {
            io::cannotTradeHasHouses(*this);
            return false;
        }
    }

    uint Street::getHouseCount() const {
        return houseCount;
    }

    void Street::manageProperty(vector<Player *> &allPlayers) {

        const Player &currOwner = *owner; // in case the owner changes
        uint choice;
        do {
            io::println("\n~~~Property manager (" + name + ")~~~");
            io::generalWhatToDo(*owner);
            choice = io::propertyMenuChoice(*this);

            if (choice != 0)
                io::println();
            switch (choice) {
                case 0:
                    return;
                case 1:
                    io::println("~~~Property details~~~");
                    display(false);
                    break;
                case 2:
                    Property::mortgageManager();
                    break;
                case 3:
                    Property::tradeManager(allPlayers);
                    break;
                case 4:
                    if (io::wantToBuild(*owner, *this) && buildHouse()) {
                        io::houseBuildSuccess(*this);
                    }
                    break;
                case 5:
                    if (io::wantToSellHouse(*owner, *this) && removeHouse()) {
                        io::houseSoldSuccessfully(*this);
                    }
                    break;
                default:
                    io::unhandledSwitchCase("Street Manager");
            }
            io::enterToContinue();
        } while (choice != 0 && *owner == currOwner);
    }

    bool Street::buildHouse() {

        // If owner affords building and if maximum house count was not exceeded
        if (owner->affords(buildCost)) {
            if (houseCount < MAXHOUSECOUNT) {
                // Check if group allows building a house
                for (vector<Property *>::const_iterator groupP = propGroup.begin();
                     groupP < propGroup.end(); groupP++) {
                    if ((*groupP)->isOwnedBy(*owner)) {
                        if (**groupP != *this) {
                            if ((*groupP)->isMortgaged()) {
                                io::cannotBuildMortgaged(**groupP);
                                return false;
                            } else if ((*groupP)->getHouseCount() < houseCount) {
                                io::cannotBuildUniformly(**groupP);
                                return false;
                            }
                        }
                    } else {
                        io::cannotBuildGroupNotOwned(**groupP);
                        return false;
                    }
                }
                // House build allowed
                owner->loseMoney(buildCost);
                houseCount++;
                return true;
            } else {
                io::cannotBuildMaxReached(*this);
                return false;
            }
        } else {
            io::notEnoughMoney(*owner, buildCost);
            return false;
        }
    }

    bool Street::removeHouse() {

        // If there is a house to remove
        if (houseCount > 0) {
            // Check if group allows selling a house
            for (vector<Property *>::const_iterator p = propGroup.begin(); p < propGroup.end(); p++) {
                if ((*p)->getHouseCount() > houseCount) {
                    io::cannotSellNotUniform(**p);
                    return false;
                }
            }
            // House sell allowed
            owner->gainMoney(buildCost / 2);
            houseCount--;
            return true;
        } else {
            io::cannotSellHasNoHouses(*this);
            return false;
        }
    }
}