#ifndef TASK2_DETAILSIO_H
#define TASK2_DETAILSIO_H

#include <iomanip>
#include <iostream>

namespace core {

    class Player;

    enum class PropGroup;
}

namespace io {

    using namespace core;

    // Separator which shows column borders
    const std::string columnSeparator = "| ";

    // Displays player details
    void printPlayerDetails(const Player &player);

    // Displays details about properties owned by a player
    void printOwnedPropertiesDetails(const Player &player);

    // Displays details about groups of properties owned by a player
    void printOwnedGroupsDetails(const Player &player);

    // Horizontal separator for property table
    void longHorizontalSeparator();

    // Horizontal separator for groups table
    void shortHorizontalSeparator();

    /**
     * Prints a row element with column width specified by the
     * specified group that the specified value belongs to.
     *
     * @tparam T the type of value to be printed
     * @tparam G the type of column that the value belongs to
     * @param value the value to be printed
     * @param group the column that the value belongs to
     * Reference :: http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
     */
    template<typename T, typename G>
    void printRowElement(const T value, const G group) {
        std::cout << columnSeparator << std::left << std::setw((uint) group) << std::setfill(' ') << value;
    };

    // Prints the last two columns of the properties table, with values N/A (for non-streets)
    void printTwoRowElements_NA();

    // Column widths used in the properties table
    enum class PropTableColWidths {
        INDEX = 3,
        NAME = 25,
        GROUP = 10,
        PRICE = 6,
        MORTGAGED = 6,
        HOUSECOUNT = 7,
        BUILDCOST = 11,
        RENT = 5,
        TOTALWIDTH = 73, // to be edited whenever any of the above are edited
        TOTALCOLUMNS = 8 // to be edited whenever a width is added/removed
    };

    // Column widths used in the groups table
    enum class GroupTableColWidths {
        INDEX = 3,
        GROUP = 10,
        OWNED = 6,
        TOTAL = 6,
        TOTALWIDTH = 25, // to be edited whenever any of the above are edited
        TOTALCOLUMNS = 4 // to be edited whenever a width is added/removed
    };
}

#endif //TASK2_DETAILSIO_H
