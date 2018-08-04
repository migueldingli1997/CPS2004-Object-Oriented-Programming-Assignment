#ifndef TASK2_BANKRUPTCYMANAGEMENT_H
#define TASK2_BANKRUPTCYMANAGEMENT_H

#include <string>
#include <vector>

namespace core {

    class Player;

    /**
     * Places a player in recovery mode since the player does not afford to
     * pay for something. The property manager will be used to allow the
     * player to try to gain money for mortgaging, trading, houses, etc.
     *
     * @param player player that is placed recovery mode
     * @param allPlayers all players in the game
     * @param amount the amount that the player does not afford
     * @param toPayFor what the player does not afford to pay
     * @return whether the recovery attempt was successful
     */
    bool tryRecover(Player &player, std::vector<Player *> &allPlayers, const uint amount, const std::string toPayFor);

    /**
     * The player is bankrupt and owes the bank. Properties
     * owned by the player are auctioned off to other players.
     *
     * @param player player that is bankrupt
     * @param allPlayers all players in the game
     */
    void bankrupt_owesBank(Player &player, std::vector<Player *> &allPlayers);

    /**
     * The player is bankrupt and owes a player. All assets (money and
     * propeties) will be given to the player that is owed money.
     *
     * @param player player that is bankrupt
     * @param owes player that is owed money
     */
    void bankrupt_owesPlayer(Player &player, Player &owes);
}

#endif //TASK2_BANKRUPTCYMANAGEMENT_H
