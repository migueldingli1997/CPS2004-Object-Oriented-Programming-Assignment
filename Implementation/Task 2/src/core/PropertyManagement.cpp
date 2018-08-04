#include "PropertyManagement.h"
#include "../spaces/Property.h"
#include "GameBoard.h"
#include "../io/PropertyMgtIO.h"
#include "../io/DetailsIO.h"
#include "../io/MenuIO.h"
#include "../io/EngineIO.h"

namespace core {

    using namespace std;
    using namespace spaces;

    void manageProperties(Player &player, vector<Player *> &allPlayers) {

        uint choice;
        do {
            io::println("\n~~~Property manager menu~~~");
            io::printOwnedPropertiesDetails(player);
            io::selectPropertyOrReturn(player);

            choice = io::intIn(0, (uint) player.getProps().size());
            switch (choice) {
                case 0:
                    return;
                default:
                    // choice adjusted to start from zero
                    player.getProps()[choice - 1]->manageProperty(allPlayers);
            }
        } while (true);
    }
}