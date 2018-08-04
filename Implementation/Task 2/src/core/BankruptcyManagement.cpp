#include "../io/GeneralIO.h"
#include "../io/EngineIO.h"
#include "../io/MoneyIO.h"
#include "BankruptcyManagement.h"
#include "Player.h"
#include "PropertyManagement.h"
#include "../spaces/Property.h"
#include "../io/MenuIO.h"

namespace core {

    using namespace std;

    bool tryRecover(Player &player, vector<Player *> &allPlayers, const uint amount, const string toPayFor) {

        io::println("\n~~~Recovery Mode~~~");
        io::recoveryMode(player, toPayFor);

        // Starting balance before recovery
        const uint baseBalance = player.getBalance();

        uint choice;
        while (player.getBalance() < (baseBalance + amount)) {
            io::println("\n~~~Recovery Menu~~~");
            io::stillNotFullyRecovered(amount - player.getBalance());
            io::generalWhatToDo(player);
            choice = io::recoveryMenuChoice();

            switch (choice) {
                case 0:
                    return false;
                case 1:
                    manageProperties(player, allPlayers);
                    break;
                default:
                    io::unhandledSwitchCase("Recovery Menu");
            }
        };

        io::fullyRecovered(player.getBalance());
        return true; // recovered
    }

    void bankrupt_owesBank(Player &player, vector<Player *> &allPlayers) {

        player.setToBankrupt();
        player.loseMoney(player.getBalance());

        // Auction skipped if only two players (one of which is bankrupt)
        if (allPlayers.size() > 2) {
            io::propertiesWillBeAuctioned(player);
            vector<Property *> playerProps = player.getProps();
            for (vector<Property *>::iterator p = playerProps.begin(); p < playerProps.end(); p++) {
                (*p)->resetOwner(); // Just in case no one bids in auction
                io::println((*p)->auction(allPlayers));
            }
        }
    }

    void bankrupt_owesPlayer(Player &player, Player &owes) {

        player.setToBankrupt();
        io::assetsWillBeGiven(player, owes);

        // Transfer money
        const uint playerBalance = player.getBalance();
        owes.gainMoney(playerBalance);
        player.loseMoney(playerBalance);

        // Transfer properties
        vector<Property *> playerProps = player.getProps();
        for (vector<Property *>::iterator p = playerProps.begin(); p < playerProps.end(); p++) {
            (*p)->transferTo(owes, 0);
        }
    }
}
