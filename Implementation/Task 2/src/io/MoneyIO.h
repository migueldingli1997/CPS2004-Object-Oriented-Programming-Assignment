#ifndef TASK2_MONEYIO_H
#define TASK2_MONEYIO_H

#include <string>

namespace core {

    class Player;
}

namespace io {

    using namespace core;

    // Player does not have enough money to pay a particular amount
    void notEnoughMoney(const Player &player, const uint amount);

    // Player has entered recovery mode to avoid bankruptcy
    void recoveryMode(const Player &player, const std::string &toPayFor);

    // Player has not yet fully recovered and has to collect more money
    void stillNotFullyRecovered(const uint amountLeft);

    // Player has fully recovered
    void fullyRecovered(const uint newBalance);

    /**
     * Player's properties will be auctioned off due to bankruptcy.
     * This is the case where the bankrupt player owes the bank.
     *
     * @param player bankrupt player
     */
    void propertiesWillBeAuctioned(const Player &player);

    /**
     * Player's properties will be given to a player. This is
     * the case where the bankrupt player owes another player.
     *
     * @param player bankrupt player
     * @param owes player that is owed money
     */
    void assetsWillBeGiven(const Player &player, const Player &owes);
}

#endif //TASK2_MONEYIO_H
