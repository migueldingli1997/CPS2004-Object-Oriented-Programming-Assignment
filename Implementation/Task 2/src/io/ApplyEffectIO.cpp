#include "ApplyEffectIO.h"
#include "../core/Player.h"
#include "../spaces/Property.h"
#include "GeneralIO.h"
#include "PlayerDecisionIO.h"

namespace io {

    using namespace std;
    using namespace spaces;
    using namespace core;

    const string prop_ownedByPlayer(const Player &player, const Property &prop) {
        return prop.getName() + " is owned by the player; no was rent paid.";
    }

    const string prop_ownedButMortgaged(const Player &player, const Property &prop) {
        return prop.getName() + " is owned by " + prop.getOwnerName() + " but is mortgaged; no rent was paid by " +
               player.getName() + ".";
    }

    const string prop_payRent(const Player &player, const Property &prop, const uint rent) {
        return prop.getName() + " is owned by " + prop.getOwnerName() + " and is unmortgaged; " + player.getName() +
               " had to pay " + to_string(rent) + " rent.";
    }

    bool prop_purchaseRequest(const Player &player, const Property &prop, const uint price) {
        return yesNoDecision(player.getName() + ", do you wish to buy " + prop.getName() + " for " + to_string(price) + "?");
    }

    const string prop_purchased(const Player &player, const Property &prop, const uint price) {
        return player.getName() + " purchased " + prop.getName() + " for " + to_string(price) + ".";
    }

    const string prop_auctionWon(const Player &player, const Property &prop, const uint price) {
        return player.getName() + " won the auction and bought " + prop.getName() + " for " +
               (price > 0 ? to_string(price) : "free") + ".";
    }

    const string prop_auctionSkip(const Property &prop) {
        return "Since no one bid on " + prop.getName() + ", it will remain unowned.";
    }

    const string xorti_birthday(const Player &player, const uint amount) {
        return "It's " + player.getName() + "'s birthday; " + to_string(amount) + " was collected from each other player.";
    }

    const string xorti_mepaFine(const Player &player, const uint amount) {
        return player.getName() + " was fined by MEPA " + to_string(amount) + " for each building owned for a total of " +
               to_string(amount * player.getProps().size()) + ".";
    }

    const string xorti_parkingFine(const Player &player, const uint amount) {
        return player.getName() + " parked the car in a lecturer's spot and was fined " + to_string(amount) + ".";
    }

    const string xorti_advanceSpaces(const Player &player, const uint amount, const Space &space) {
        return player.getName() + " was advanced by " + to_string(amount) + " spaces and landed on " + space.getName();
    }

    void printEffectMessage(const string &msg) {

        if (msg.length() > 0) {
            println(msg);
        }
    }
}