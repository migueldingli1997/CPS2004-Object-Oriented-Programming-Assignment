#ifndef TASK2_APPLYEFFECTIO_H
#define TASK2_APPLYEFFECTIO_H

#include <string>

namespace spaces {

    class Space;

    class Property;
}

namespace core {

    class Player;
}

namespace io {

    using namespace spaces;
    using namespace core;

    // Property is owned by the player, so no rent had to be paid
    const std::string prop_ownedByPlayer(const Player &player, const Property &prop);

    // Property is not owned by the player but is mortgaged, so no rent had to be paid
    const std::string prop_ownedButMortgaged(const Player &player, const Property &prop);

    // Property is not owned by the player and is mortgaged, so rent had to be paid
    const std::string prop_payRent(const Player &player, const Property &prop, const uint rent);

    // Asks if the player wishes to purchase the property at a specified price
    bool prop_purchaseRequest(const Player &player, const Property &prop, const uint price);

    // Player purchased the property for a particular price
    const std::string prop_purchased(const Player &player, const Property &prop, const uint price);

    // Player won the auction and purchased the property for a particular price
    const std::string prop_auctionWon(const Player &player, const Property &prop, const uint price);

    // No player wished to participate in the auction
    const std::string prop_auctionSkip(const Property &prop);

    // A particular amount was collected from everyone for player's birthday
    const std::string xorti_birthday(const Player &player, const uint amount);

    // Player was fined a particular amount by MEPA for each building owned
    const std::string xorti_mepaFine(const Player &player, const uint amount);

    // Player was fined a particular amount for parking in a lecturer's spot
    const std::string xorti_parkingFine(const Player &player, const uint amount);

    // Player was advanced by a number of spaces and landed in a new space
    const std::string xorti_advanceSpaces(const Player &player, const uint amount, const spaces::Space &space);

    // Used if the switch cases do not cover all xorti
    const std::string xorti_invalid = "ERROR :: No xorti effect applied.";

    // Prints effect message; If message is empty (""), blank line is not printed
    void printEffectMessage(const std::string &msg);
}

#endif //TASK2_APPLYEFFECTIO_H
