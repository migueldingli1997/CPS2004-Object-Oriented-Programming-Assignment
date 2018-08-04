#ifndef TASK2_ENGINEIO_H
#define TASK2_ENGINEIO_H

#include <string>

namespace spaces {

    class Space;
}

namespace core {

    class Player;

    class DicePair;
}

namespace io {

    using namespace spaces;
    using namespace core;

    // Displays round count when it's a new round
    void newRound(const uint round);

    // Displays player that will play next
    void newTurn(const Player &player);

    // Player will roll again due to a double
    void rollAgain(const Player &player);

    // Player will not roll again due to the past double
    void willRollAgain(const Player &player);

    // Player will now play at the new space
    void playAgain(const Player &player);

    // Player rolled a particular amount and landed on a space
    void landedOn(const Player &player, const Space &space, const DicePair &dice);

    // Player passed 'GO' space and received money (amount defined in GameBoard)
    void passedGo(const Player &player);

    // Player is asked a generic "What do you want to do?" question
    void generalWhatToDo(const Player &player);

    // Error; Switch case was out of range in a menu
    void unhandledSwitchCase(const std::string menuName);

    // Displays a single line which splits a player's turn from the next
    void singleLine();

    // Displays a double line which splits a round from the next
    void doubleLine();
}

#endif //TASK2_ENGINEIO_H
