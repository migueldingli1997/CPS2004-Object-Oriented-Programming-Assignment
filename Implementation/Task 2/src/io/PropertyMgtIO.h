#ifndef TASK2_PROPERTYMGTIO_H
#define TASK2_PROPERTYMGTIO_H

namespace spaces {

    class Property;

    class Street;
}

namespace core {

    class Player;
}

namespace io {

    using namespace spaces;
    using namespace core;

    // GENERAL; Message to ask player to select a property or return
    void selectPropertyOrReturn(const Player &player);

    // MORTGAGE; Property cannot be mortgaged since it contains houses
    void cannotMortgageHasHouses(const Property &prop);

    // MORTGAGE; Property successfully mortgaged
    void mortgageSuccess(const Property &prop, const uint fee);

    // TRADING; Property cannot be traded since a property in the same group has houses
    void cannotTradeHasHouses(const Property &prop);

    // TRADING; Message to ask player to choose a player to trade with
    void selectPlayerOrReturn(const Player &player);

    // TRADING; Asks the player receiving the trade request to accept/decline
    bool tradeRequest(const Player &from, const Player &to);

    // TRADING; Displays an offer to the player receiving the trade request
    void tradeOffer(const Player &from, const Player &to, const Property &prop, const uint money);

    // TRADING; Asks the player making the trade request to accept the offer
    bool tradeReturnRequest(const Player &from, const Player &to);

    // TRADING; Displays an offer to the player making the trade request
    void tradeReturnOffer(const Player &from, const Player &to, const Property *prop, const uint money);

    // TRADING; Message to ask the player to select a property or none (skip)
    void selectPropertyOrSkip(const Player &player);

    // TRADING; Asks player to insert an optional extra amount of money
    uint howMuchToAdd(const Player &player);

    // TRADING; Trading was cancelled by the specified player
    void tradeCancelled(const Player &player);

    // BUILD HOUSE; House cannot be built since a house in group is not owned
    void cannotBuildGroupNotOwned(const Property &prop);

    // BUILD HOUSE; House cannot be built since a house in group is mortgaged
    void cannotBuildMortgaged(const Property &prop);

    // BUILD HOUSE; House cannot be built since a house in group has less houses
    void cannotBuildUniformly(const Property &prop);

    // BUILD HOUSE; House cannot be built since house limit was reached
    void cannotBuildMaxReached(const Street &street);

    // BUILD HOUSE; Asks the player to confirm the building of a house
    bool wantToBuild(const Player &player, const Street &street);

    // BUILD HOUSE; Message to indicate that house was successfully built
    void houseBuildSuccess(const Street &street);

    // SELL HOUSE; House cannot be sold since a house in group has more houses
    void cannotSellNotUniform(const Property &prop);

    // SELL HOUSE; House cannot be sold since there is no houses built
    void cannotSellHasNoHouses(const Street &street);

    // SELL HOUSE; Asks the player to confirm the selling of a house
    bool wantToSellHouse(const Player &player, const Street &street);

    // SELL HOUSE; Message to indicate that house was successfully sold
    void houseSoldSuccessfully(const Street &street);
}

#endif //TASK2_PROPERTYMGTIO_H
