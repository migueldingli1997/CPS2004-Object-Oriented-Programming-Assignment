#ifndef TASK2_PROPERTYMANAGEMENT_H
#define TASK2_PROPERTYMANAGEMENT_H

#include "Player.h"

namespace core {

    using namespace spaces;

    /**
     * Manage properties owned by the specified player.
     * Possible options depend on the type of property.
     */
    void manageProperties(Player &player, std::vector<Player *> &allPlayers);
}

#endif //TASK2_PROPERTYMANAGEMENT_H
