#include "EngineIO.h"
#include "../core/Player.h"
#include "../spaces/Property.h"
#include "../core/DicePair.h"
#include "GeneralIO.h"
#include "../core/GameBoard.h"

namespace io {

    using namespace std;
    using namespace spaces;
    using namespace core;

    void newRound(const uint round) {
        println("ROUND " + to_string(round));
    }

    void newTurn(const Player &player) {
        println("It's " + player.getName() + "'s turn!");
    }

    void willRollAgain(const Player &player) {
        println(player.getName() + " will roll again later since a double was rolled!");
    }

    void rollAgain(const Player &player) {
        println(player.getName() + " will now roll again...");
    }

    void playAgain(const Player &player) {
        println(player.getName() + " will now play at the new space...");
    }

    void landedOn(const Player &player, const Space &space, const DicePair &dice) {
        println(player.getName() + " rolled a " + to_string(dice.getDice1()) + " and a " + to_string(dice.getDice2()) +
                " and landed on " + space.getName());
    }

    void passedGo(const Player &player) {
        println(player.getName() + " passed GO and received " + to_string(core::GameBoard::GOPAY) + ".");
    }

    void generalWhatToDo(const Player &player) {
        println(player.getName() + ", what do you want to do?");
    }

    void singleLine() {

        repeatChar('-', 41);
        println();
    }

    void doubleLine() {

        repeatChar('=', 41);
        println();
    }
}
