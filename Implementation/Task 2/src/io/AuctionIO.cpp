#include "AuctionIO.h"
#include "PlayerDecisionIO.h"
#include "GeneralIO.h"
#include "../core/Player.h"
#include "../spaces/Property.h"

namespace io {

    bool auctionParticipate(const Player &player, const Property &prop) {
        return yesNoDecision(player.getName() + ", do you wish to bid on " + prop.getName() + "?");
    }

    uint auctionBid(const Player &player, const Property &prop) {
        return valueDecision(player.getName() + ", how much do you want to bid?", 0, player.getBalance());
    }

    void currentHighestBid(const uint bid, const Player &bidder) {
        println("Currently, the highest bidder is " + bidder.getName() + " with a bid of " + to_string(bid));
    }

    bool auctionChangeBidRequest(const Player &player) {
        return yesNoDecision(player.getName() + ", do you wish to change your bid?");
    }
}
