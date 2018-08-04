#include <algorithm>
#include "Player.h"
#include "GameBoard.h"
#include "GameEngine.h"
#include "../spaces/Space.h"
#include "DicePair.h"
#include "../io/EngineIO.h"
#include "../io/DetailsIO.h"
#include "../io/MenuIO.h"
#include "../io/ApplyEffectIO.h"

namespace core {

    using namespace std;
    using namespace spaces;

    GameEngine::GameEngine(const GameBoard &board, vector<Player *> &allPlayers, DicePair &dice) :
            board(board), allPlayers(allPlayers), dice(dice) {
        io::println("Game Engine initialized.");
    }

    void GameEngine::start() {

        io::println("Game Engine started.");
        uint round = 1;

        while (gameRunning) {
            io::doubleLine();
            io::newRound(round++);

            for (vector<Player *>::iterator p = allPlayers.begin(); p < allPlayers.end(); p++) {
                if (allPlayers.size() == 1) {
                    io::doubleLine();
                    io::println("The winner is " + (*p)->getName() + "!");
                    endGame();
                    break;
                } else {
                    io::singleLine();
                    io::println();
                    io::newTurn(**p);
                    mainMenu(**p, false);

                    if ((*p)->isBankrupt()) {
                        delete *p;
                        allPlayers.erase(p);
                        p--;
                    } else {
                        mainMenu(**p, true);
                    }
                }
            }
        }
        io::doubleLine();
    }

    void GameEngine::mainMenu(Player &currP, const bool endTurn) {

        willRollAgain = false;
        uint choice;
        do {
            if (willRollAgain) {
                io::println();
                io::rollAgain(currP);
            }
            willRollAgain = false;

            io::println("\n~~~Main Menu~~~");
            io::generalWhatToDo(currP);
            choice = io::mainMenuChoice(currP, endTurn);

            switch (choice) {
                case 0:
                    if (!endTurn) {
                        io::println("\n~~~Play~~~");
                        dice.reset();
                        currP.rollDice(dice); // player given dice to roll
                        playTurn(currP);
                    }
                    break;
                case 1:
                    io::println("\n~~~Player details~~~");
                    io::printPlayerDetails(currP);
                    io::enterToContinue();
                    break;
                case 2:
                    io::println("\n~~~Property and Group details~~~");
                    io::printOwnedPropertiesDetails(currP);
                    io::printOwnedGroupsDetails(currP);
                    io::enterToContinue();
                    break;
                case 3:
                    manageProperties(currP, allPlayers);
                    break;
                default:
                    io::unhandledSwitchCase("Main Menu");
            }
        } while (choice != 0 || willRollAgain);
    }

    void GameEngine::playTurn(Player &currP) {

        // Get current space id and new space
        const uint currSpaceId = currP.getCurrSpaceId();
        Space *newS = board.getSpace(currSpaceId + dice.getDice1() + dice.getDice2());

        // Player advances to new position
        currP.advanceTo(newS);
        io::landedOn(currP, *newS, dice);

        // Opportunity to roll again
        if (dice.dice1 == dice.dice2) {
            io::willRollAgain(currP);
            willRollAgain = true;
        }
        dice.reset();

        // Player passed the GO
        if (newS->getId() < currSpaceId) {
            currP.gainMoney(GameBoard::GOPAY);
            io::passedGo(currP);
        }

        // Apply effect
        const string effectMessage = newS->applyEffect(currP, allPlayers, board);
        if (!currP.isBankrupt()) {
            io::printEffectMessage(effectMessage);
        } else {
            willRollAgain = false;
        }
    }

    void GameEngine::endGame() {

        io::println("Any remaining players deleted.");
        for (vector<Player *>::iterator p = allPlayers.begin(); p < allPlayers.end(); p++) {
            delete *p;
        }
        gameRunning = false;
    }
}
