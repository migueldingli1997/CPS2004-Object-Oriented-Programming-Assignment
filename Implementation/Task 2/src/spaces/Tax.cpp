#include "Tax.h"
#include "../core/Player.h"
#include "../core/BankruptcyManagement.h"

namespace spaces {

    using namespace std;
    using namespace core;

    Tax::Tax(uint id, const string &name, uint taxCost) : Space(id, name), taxCost(taxCost) {}

    const string Tax::applyEffect(Player &player, vector<Player *> &allPlayers, const GameBoard &board) {

        // If player does not afford to pay, enter recovery mode; otherwise, pay
        if (player.affords(taxCost) || tryRecover(player, allPlayers, taxCost, "tax")) {
            player.loseMoney(taxCost);
        } else {
            bankrupt_owesBank(player, allPlayers); // player is bankrupt and owes the bank
        }
        return player.getName() + " paid a tax of " + to_string(taxCost) + ".";
    }
}