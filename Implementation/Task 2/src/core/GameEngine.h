#ifndef TASK2_GAMEENGINE_H
#define TASK2_GAMEENGINE_H

#include <vector>
#include "PropertyManagement.h"

namespace core {

    class GameBoard;

    class Player;

    class DicePair;

    class GameEngine final {

    public:
        /**
         * @param board game board containing the spaces
         * @param allPlayers pointers to all playing players
         * @param dice dice that will be given to players to roll
         */
        GameEngine(const GameBoard &board, std::vector<Player *> &allPlayers, DicePair &dice);

        /**
         * Start the game
         */
        void start();

    private:
        const GameBoard &board; // game board containing the spaces
        std::vector<Player *> &allPlayers; // pointers to all playing players
        DicePair &dice; // dice given to a player to roll

        bool willRollAgain; // indicates whether current player will roll again
        bool gameRunning = true; // indicates whether the game has not ended yet

        /**
         * Runs the main menu for the specified player.
         *
         * @param endTurn true if menu should show "end turn" instead of "roll dice"
         */
        void mainMenu(Player &currP, const bool endTurn);

        /**
         * Allows the specified player to play (roll, move, and so on)
         *
         * @param currP player to give turn to
         */
        void playTurn(Player &currP);

        /**
         * Ends the game (when all but one player are bankrupt)
         */
        void endGame();
    };
}

#endif //TASK2_GAMEENGINE_H
