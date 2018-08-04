#include <random>
#include "Xorti.h"
#include "../core/Player.h"
#include "../io/GeneralIO.h"
#include "../io/ApplyEffectIO.h"
#include "../io/EngineIO.h"
#include "../core/GameBoard.h"
#include "../core/BankruptcyManagement.h"

namespace spaces {

    using namespace std;
    using namespace core;

    Xorti::Xorti(const uint id, const string &name) : Space(id, name) {}

    const string Xorti::applyEffect(Player &player, vector<Player *> &allPlayers, const GameBoard &board) {

        switch (rand() % 4) {
            case 0:
                return io::xorti_birthday(player, birthday(player, allPlayers));
            case 1:
                return io::xorti_parkingFine(player, parkingFine(player, allPlayers));
            case 2:
                return io::xorti_mepaFine(player, mepaFine(player, allPlayers));
            case 3:
                advanceToNewSpace(player, allPlayers, board);
                return ""; // Output is performed in the method instead
            default:
                return io::xorti_invalid;
        }
    }

    uint Xorti::birthday(Player &player, vector<Player *> &allPlayers) {

        const uint randPay = (uint) (rand() % 91) + 10; // 10 to 100

        for (vector<Player *>::iterator p = allPlayers.begin(); p < allPlayers.end(); p++) {
            if (**p != player) {
                if ((*p)->affords(randPay) || tryRecover(**p, allPlayers, randPay, player.getName() + "'s birthday")) {
                    player.gainMoney(randPay);
                    (*p)->loseMoney(randPay);
                } else {
                    bankrupt_owesPlayer(**p, player);
                }
            }
        }
        return randPay;
    }

    uint Xorti::parkingFine(Player &player, vector<Player *> &allPlayers) {

        const uint randFine = (uint) (rand() % 101) + 50; // 50 to 150

        if (player.affords(randFine) || tryRecover(player, allPlayers, randFine, "parking fine")) {
            player.loseMoney(randFine);
        } else {
            bankrupt_owesBank(player, allPlayers);
        }
        return randFine;
    }

    uint Xorti::mepaFine(Player &player, vector<Player *> &allPlayers) {

        const uint randFine = (uint) (rand() % 141) + 40; // 40 to 180
        const uint totalFine = randFine * (uint) player.getProps().size();

        if (player.affords(totalFine) || tryRecover(player, allPlayers, totalFine, "a MEPA fine")) {
            player.loseMoney(totalFine);
        } else {
            bankrupt_owesBank(player, allPlayers);
        }
        return randFine;
    }

    void Xorti::advanceToNewSpace(Player &player, vector<Player *> &allPlayers, const GameBoard &board) {

        const uint randAmount = (rand() % (GameBoard::SPACECOUNT - 1)) + 1; // 1 to 39

        // Player advances to new position
        Space *newS = board.getSpace(player.getCurrSpaceId() + randAmount);
        player.advanceTo(newS);

        // Output
        io::println(io::xorti_advanceSpaces(player, randAmount, *newS) + "\n");
        io::playAgain(player);

        // Apply effect
        io::println(newS->applyEffect(player, allPlayers, board));
    }
}