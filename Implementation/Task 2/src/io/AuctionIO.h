#ifndef TASK2_AUCTIONIO_H
#define TASK2_AUCTIONIO_H

#include <sys/types.h>

namespace core {

    class Player;
}

namespace spaces {

    class Property;
}

namespace io {

    using namespace core;
    using namespace spaces;

    /**
     * Asks if the player wishes to participate in the auction.
     *
     * @param player player to ask
     * @param prop property to be auctioned off
     * @return true if player wishes to participate in auction
     */
    bool auctionParticipate(const Player &player, const Property &prop);

    /**
     * Asks the player how much money to bid on the property.
     *
     * @param player player to ask
     * @param prop property being auctioned off
     * @return player's bid
     */
    uint auctionBid(const Player &player, const Property &prop);

    /**
     * Displays the current highest bid and respective bidder.
     *
     * @param bid highest bid
     * @param bidder highest bidder
     */
    void currentHighestBid(const uint bid, const Player &bidder);

    /**
     * Asks if the player wishes to change the placed bid.
     *
     * @param player player to ask
     * @return true if player wishes to change bid
     */
    bool auctionChangeBidRequest(const Player &player);
}

#endif //TASK2_AUCTIONIO_H
