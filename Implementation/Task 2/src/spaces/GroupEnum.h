#ifndef TASK2_GROUPENUM_H
#define TASK2_GROUPENUM_H

#include <string>

namespace core {

    // Assigned to properties
    enum class PropGroup {
        BROWN = 0,
        CYAN = 1,
        MAGENTA = 2,
        ORANGE = 3,
        RED = 4,
        YELLOW = 5,
        GREEN = 6,
        BLUE = 7,
        RAILROAD = 8,
        UTILITY = 9
    };

    const uint GROUPCOUNT = 10; // Amount of groups (Excluding DEFAULTGROUP)

    /**
     * Gets a string representation of the specified group.
     */
    const std::string groupName(const PropGroup theGroup);

    /**
     * Gets the number of properties expected to belong to a group.
     */
    uint groupSize(const PropGroup theGroup);
}

#endif //TASK2_GROUPENUM_H
