#include "EmptySpace.h"
#include "../core/Player.h"

namespace spaces {

    using namespace core;
    using namespace std;

    EmptySpace::EmptySpace(uint id, const string &name) : Space(id, name) {}

    const string EmptySpace::applyEffect(Player &player, vector<Player *> &allPlayers, const GameBoard &board) {
        return "This space had no effect on the player.";
    }
}