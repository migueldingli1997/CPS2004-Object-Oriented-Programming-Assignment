#include "MoneyIO.h"
#include "GeneralIO.h"
#include "../core/Player.h"

namespace io {

    using namespace std;

    void notEnoughMoney(const Player &player, const uint amount) {
        println(player.getName() + ", you do not have enough money to pay " + to_string(amount) + ". Your balance is " +
                to_string(player.getBalance()) + ".");
    }

    void recoveryMode(const Player &player, const string &toPayFor) {
        println(player.getName() + ", you are now in recovery mode since you could not pay for " + toPayFor +
                ". You need to collect money by selling properties or houses, or by mortgaging.");
    }

    void stillNotFullyRecovered(const uint amountLeft) {
        println("You still need to collect " + to_string(amountLeft) + ". ");
    }

    void fullyRecovered(const uint newBalance) {
        println("\nYou successfully recovered. Your new balance is " + to_string(newBalance) + ".");
    }

    void propertiesWillBeAuctioned(const Player &player) {
        println("All properties belonging to " + player.getName() + " will now be auctioned off.");
    }

    void assetsWillBeGiven(const Player &player, const Player &owes) {
        println("All assets belonging to " + player.getName() + " will now be given to " + owes.getName() + ".");
    }
}