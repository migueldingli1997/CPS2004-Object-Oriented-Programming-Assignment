#include "Property.h"
#include "../core/Player.h"
#include "../io/GeneralIO.h"
#include "../io/ApplyEffectIO.h"
#include "../io/DetailsIO.h"
#include "../io/PropertyMgtIO.h"
#include "../io/MoneyIO.h"
#include "../core/BankruptcyManagement.h"
#include "../io/EngineIO.h"
#include "../io/MenuIO.h"
#include "../io/AuctionIO.h"
#include <algorithm>

namespace spaces {

    using namespace std;
    using namespace core;

    Property::Property(const uint id, const string &name, const PropGroup group, const vector<Property *> &propGroup,
                       const uint price) : Space(id, name), group(group), propGroup(propGroup), price(price) {}

    void Property::display(const bool table) const {

        using namespace io;

        if (table) {
            printRowElement<string, PropTableColWidths>(name, PropTableColWidths::NAME);
            printRowElement<string, PropTableColWidths>(groupName(group), PropTableColWidths::GROUP);
            printRowElement<int, PropTableColWidths>(price, PropTableColWidths::PRICE);
            printRowElement<string, PropTableColWidths>((mortgaged ? "Yes" : "No"), PropTableColWidths::MORTGAGED);
            printRowElement<int, PropTableColWidths>(getRent(), PropTableColWidths::RENT);
        } else {
            io::println("Name: " + name);
            io::println("Group: " + groupName(group));
            io::println("Price: " + to_string(price));
            io::println(string("Mortgaged: ") + (mortgaged ? "Yes" : "No"));
            io::println("Rent cost: " + to_string(getRent()));
        }
    }

    const string Property::applyEffect(Player &player, vector<Player *> &allPlayers, const GameBoard &board) {

        // If has owner
        if (owner != nullptr) {
            if (mortgaged) {
                // Not owned by the player, but mortgaged, so no rent paid
                return io::prop_ownedButMortgaged(player, *this);
            } else if (isOwnedBy(player)) {
                // Owned by the player, so no rent paid
                return io::prop_ownedByPlayer(player, *this);
            } else {
                // Not owned by the player and unmortgaged, so rent has to be paid
                const uint rentPay = getRent();
                Player &currentOwner = *owner; // for the case that this property is given to 'player'
                if (player.affords(rentPay) || tryRecover(player, allPlayers, rentPay, "rent")) {
                    player.loseMoney(rentPay);
                    owner->gainMoney(rentPay);
                } else {
                    bankrupt_owesPlayer(player, currentOwner);
                }
                return io::prop_payRent(player, *this, rentPay);
            }
        } else {
            // Ask player to purchase
            if (io::prop_purchaseRequest(player, *this, price)) {
                if (player.affords(price)) {
                    transferTo(player, price);
                    return io::prop_purchased(player, *this, price);
                } else {
                    io::notEnoughMoney(player, price);
                    // No return since property will be auctioned instead
                }
            }

            // Auction (if no purchase)
            return auction(allPlayers);
        }
    }

    const string Property::auction(vector<Player *> &allPlayers) {

        // Runs only if player did not want to purchase or did not afford
        io::println("\n~~~Auction~~~");

        uint latestBid, winningBid = 0;
        Player *winningPlayer = nullptr;

        // If there is only two players and one of them is bankrupt, skip auction
        if (allPlayers.size() == 2 && (allPlayers[0]->isBankrupt() || allPlayers[1]->isBankrupt())) {
            winningBid = 0;
            winningPlayer = allPlayers[0]->isBankrupt() ? allPlayers[1] : allPlayers[0];
        } else {
            vector<Player *> participants = vector<Player *>(); // stores participants
            vector<bool> changeBid = vector<bool>(); // indicates whether bid will be changed
            bool endAuction; // indicates whether auction should be ended or not

            // Call for participants
            for (vector<Player *>::const_iterator p = allPlayers.begin(); p < allPlayers.end(); p++) {
                if (!(*p)->isBankrupt() && io::auctionParticipate(**p, *this)) {
                    participants.push_back(*p);
                    changeBid.push_back(true);
                }
            }

            // Proceed with auction if there is at least two participants
            if (participants.size() > 1) {
                io::println();
                // Loop until no participant chooses to change bid
                do {
                    // Ask participants to bid (must have changeBid true)
                    for (uint i = 0; i < participants.size(); i++) {
                        if (changeBid[i]) {
                            latestBid = io::auctionBid(*participants[i], *this);
                            if (winningPlayer == nullptr || latestBid > winningBid) {
                                winningBid = latestBid;
                                winningPlayer = participants[i];
                            }
                        }
                    }

                    // Display current highest bid
                    io::println();
                    io::currentHighestBid(winningBid, *winningPlayer);
                    io::println();

                    // Ask participants (excl. winning player) if they wish to change bid
                    endAuction = true; // assume auction will end
                    for (uint i = 0; i < participants.size(); i++) {
                        if (participants[i] != winningPlayer && io::auctionChangeBidRequest(*participants[i])) {
                            changeBid[i] = true;
                            endAuction = false; // auction does not end since someone wants to change bid
                        } else {
                            changeBid[i] = false;
                        }
                    }
                    io::println();
                } while (!endAuction);
            } else if (participants.size() == 1) { // Only one participant, so automatically wins
                winningBid = 0;
                winningPlayer = participants[0];
                io::println();
            }
        }

        // Transfer property to winner, if there is one
        if (winningPlayer != nullptr) {
            transferTo(*winningPlayer, winningBid);
            return io::prop_auctionWon(*winningPlayer, *this, winningBid);
        } else {
            return io::prop_auctionSkip(*this);
        }
    }

    void Property::manageProperty(vector<Player *> &allPlayers) {

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
                    display(false); // (false => not in table form)
                    break;
                case 2:
                    mortgageManager();
                    break;
                case 3:
                    tradeManager(allPlayers);
                    break;
                default:
                    io::unhandledSwitchCase("Property Manager");
            }
            io::enterToContinue();
        } while (choice != 0 && *owner == currOwner);
    }

    void Property::transferTo(Player &newOwner, const uint customPrice) {

        // If player does not afford, cancel transfer
        if (newOwner.affords(customPrice)) {
            // If property owned, property removed and owner given money
            if (owner != nullptr) {
                owner->gainMoney(customPrice);
                owner->removeProperty(*this);
            }
            newOwner.loseMoney(customPrice);
            newOwner.addProperty(*this);
            owner = &newOwner;
        } else {
            io::println("ERROR :: Player did not afford property. Transfer cancelled.");
        }
    }

    bool Property::isOwnedBy(const Player &player) const {
        return owner != nullptr && *owner == player;
    }

    const string Property::getOwnerName() const {

        if (owner != nullptr) {
            return owner->getName();
        } else {
            return "No Owner";
        }
    }

    void Property::resetOwner() {
        owner = nullptr;
    }

    bool Property::isMortgaged() const {
        return mortgaged;
    }

    uint Property::getHouseCount() const {
        return 0;
    }

    PropGroup Property::getGroup() const {
        return group;
    }

    uint Property::amountOwnedFromGroup() const {

        uint count = 0;
        for (vector<Property *>::const_iterator p = propGroup.begin(); p < propGroup.end(); p++) {
            count += ((*p)->isOwnedBy(*owner) ? 1 : 0);
        }
        return count;
    }

    bool Property::isTradeable() const {
        return true;
    }

    void Property::tradeManager(vector<Player *> &allPlayers) {

        uint money1, money2;   // money towards toTradeWith and towards owner
        uint playerChoice;     // chosen player to trade with
        uint tradePropChoice;  // index of property chosen by toTradeWith
        Property *tradeProp;  // property chosen by toTradeWith
        Player &player = *owner; // in case the owner changes

        if (isTradeable()) {
            // Extra money from player's side
            money1 = io::howMuchToAdd(player);

            // Make a copy of allPlayers, excluding current player
            vector<Player *> plCopy(allPlayers.size() - 1);
            plCopy = allPlayers;
            plCopy.erase(remove(plCopy.begin(), plCopy.end(), &player), plCopy.end());

            // Select player to trade with
            io::println();
            io::selectPlayerOrReturn(player);
            io::println("0) Cancel trade...");
            playerChoice = io::generalMenuChoice<Player>(plCopy, 1);

            if (playerChoice == 0) {
                io::tradeCancelled(player);
                return;
            }

            Player &toTradeWith = *plCopy[playerChoice - 1];

            // player can enter 0 in each case to "cancel" trade (bad deal)
            io::println();

            if (!io::tradeRequest(player, toTradeWith)) {
                io::tradeCancelled(toTradeWith);
                return;
            }

            io::tradeOffer(player, toTradeWith, *this, money1);
            const vector<Property *> &tradeProps = toTradeWith.getProps();

            // Select property
            do {
                io::println();
                io::selectPropertyOrSkip(toTradeWith);
                io::println("0) Skip (no property)...");
                tradePropChoice = io::generalMenuChoice<Property>(tradeProps, 1);

                if (tradePropChoice == 0) {
                    tradeProp = nullptr;
                    break;
                } else {
                    tradeProp = tradeProps[tradePropChoice - 1]; // -1 to start from 0
                    if (tradeProp->isTradeable()) {
                        break;
                    }
                }
            } while (true); // loops if non-tradeable property

            // Extra money from tradePlayer's side
            money2 = io::howMuchToAdd(toTradeWith);

            // Confirm trade
            io::println();
            io::tradeReturnOffer(toTradeWith, player, tradeProp, money2);

            if (!io::tradeReturnRequest(toTradeWith, player)) {
                io::tradeCancelled(player);
                return;
            }

            // Transfer first property (from player to toTradeWith (money2 was offered by toTradeWith))
            transferTo(toTradeWith, money2);

            // Transfer second property (from toTradeWith to player (money1 was offered by player))
            if (tradeProp != nullptr) {
                tradeProp->transferTo(player, money1);
            } else {
                player.loseMoney(money1);
                toTradeWith.gainMoney(money1);
            }
        }
    }

    void Property::mortgageManager() {

        if (canSwitchMortgageState()) {
            const uint pay = switchMortgageState();
            io::mortgageSuccess(*this, pay);
        }
    }

    bool Property::canSwitchMortgageState() const {

        // If going to unmortgage, check that player affords
        if (mortgaged) {
            const uint unmortgageCost = (uint) (price * UNMORTGAGERATE);
            if (!owner->affords(unmortgageCost)) {
                io::notEnoughMoney(*owner, unmortgageCost);
                return false;
            }
        }
        return true; // player affords
    }

    uint Property::switchMortgageState() {

        uint payment;
        if (!mortgaged) {
            // Mortgage
            payment = (uint) (price * MORTGAGERATE);
            owner->gainMoney(payment);
        } else {
            // Unmortgage
            payment = (uint) (price * UNMORTGAGERATE);
            owner->loseMoney(payment);
        }
        mortgaged = !mortgaged;
        return payment;
    }
}
