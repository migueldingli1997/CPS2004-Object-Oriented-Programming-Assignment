#include <string>
#include "PropertyMgtIO.h"
#include "GeneralIO.h"
#include "../spaces/Street.h"
#include "../core/Player.h"
#include "PlayerDecisionIO.h"

namespace io {

    using namespace spaces;
    using namespace std;
    using namespace core;

    void selectPropertyOrReturn(const Player &player) {
        println(player.getName() + ", select a property or enter '0' to return back.");
    }

    void cannotMortgageHasHouses(const Property &prop) {
        println("Cannot mortgage since at least one street in the same group (" + prop.getName() + ") has houses.");
    }

    void mortgageSuccess(const Property &prop, const uint fee) {
        println("Successfully " + string(prop.isMortgaged() ? "" : "un") + "mortgaged " + prop.getName() + " for " +
                to_string(fee) + ".");
    }

    void selectPlayerOrReturn(const Player &player) {
        println(player.getName() + ", select a player to trade with or enter '0' to cancel trading.");
    }

    void cannotTradeHasHouses(const Property &prop) {
        println("Cannot trade since at least one street in the same group (" + prop.getName() + ") has houses.");
    }

    bool tradeRequest(const Player &from, const Player &to) {
        return yesNoDecision(to.getName() + ", accept trade request from " + from.getName() + "?");
    }

    bool tradeReturnRequest(const Player &from, const Player &to) {
        return yesNoDecision(to.getName() + ", accept trade offer from " + from.getName() + "?");
    }

    void tradeOffer(const Player &from, const Player &to, const Property &prop, const uint money) {
        println(to.getName() + ", " + from.getName() + " has offered you " + prop.getName() +
                (money != 0 ? " and " + to_string(money) : ""));
    }

    void tradeReturnOffer(const Player &from, const Player &to, const Property *prop, const uint money) {

        string offer;
        if (prop != nullptr) {
            offer = prop->getName() + (money != 0 ? " and " + to_string(money) : "");
        } else {
            offer = (money != 0 ? to_string(money) : "nothing");
        }
        println(to.getName() + ", " + from.getName() + " has offered you " + offer + " in return.");
    }

    void selectPropertyOrSkip(const Player &player) {
        println(player.getName() + ", select a property to trade or enter '0' to skip.");
    }

    uint howMuchToAdd(const Player &player) {
        return valueDecision(player.getName() + ", how much extra money do you want to add?", 0, player.getBalance());
    }

    void tradeCancelled(const Player &player) {
        println("Trading was cancelled by " + player.getName() + ".");
    }

    void cannotBuildGroupNotOwned(const Property &prop) {
        println("Cannot build since at least one street in the same group (" + prop.getName() + ") is not owned by you.");
    }

    void cannotBuildMortgaged(const Property &prop) {
        println("Cannot build since at least one street in the same group (" + prop.getName() + ") is mortgaged.");
    }

    void cannotBuildUniformly(const Property &prop) {
        println("Cannot build since at least one street in the same group (" + prop.getName() + ") has less houses.");
    }

    void cannotBuildMaxReached(const Street &street) {
        println("Cannot build since the maximum amount of houses on " + street.getName() + " was reached.");
    }

    bool wantToBuild(const Player &player, const Street &street) {
        return yesNoDecision("Build a house at " + street.getName() + " for " + to_string(street.getBuildCost()) + "?");
    }

    void houseBuildSuccess(const Street &street) {
        println("Successfully built a house at " + street.getName() + " for " + to_string(street.getBuildCost()) + ".");
    }

    void cannotSellNotUniform(const Property &prop) {
        println("Cannot sell since at least one street in the same group (" + prop.getName() + ") has more houses.");
    }

    void cannotSellHasNoHouses(const Street &street) {
        println("Cannot sell since " + street.getName() + " has no houses.");
    }

    bool wantToSellHouse(const Player &player, const Street &street) {
        return yesNoDecision("Sell a house at " + street.getName() + " for " + to_string(street.getBuildCost() / 2) + "?");
    }

    void houseSoldSuccessfully(const Street &street) {
        println("Successfully sold the house at " + street.getName() + " for " + to_string(street.getBuildCost()) + ".");
    }
}