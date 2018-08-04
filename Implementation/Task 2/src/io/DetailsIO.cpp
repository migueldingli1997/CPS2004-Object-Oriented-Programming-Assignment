#include <string>
#include "DetailsIO.h"
#include "../spaces/Property.h"
#include "../core/Player.h"
#include "../core/GameBoard.h"
#include "GeneralIO.h"

namespace io {

    using namespace std;
    using namespace spaces;
    using namespace core;

    void printTwoRowElements_NA() {

        printRowElement<string, PropTableColWidths>("N/A", PropTableColWidths::HOUSECOUNT);
        printRowElement<string, PropTableColWidths>("N/A", PropTableColWidths::BUILDCOST);
    }

    void printPlayerDetails(const Player &player) {

        println("Balance: " + to_string(player.getBalance()));
        println("Properties: " + to_string(player.getProps().size()));
    }

    void printOwnedPropertiesDetails(const Player &player) {

        const vector<Property *> &properties = player.getProps();
        if (properties.size() != 0) {
            // Header
            longHorizontalSeparator();
            printRowElement<string, PropTableColWidths>("", PropTableColWidths::INDEX);
            printRowElement<string, PropTableColWidths>("NAME", PropTableColWidths::NAME);
            printRowElement<string, PropTableColWidths>("GROUP", PropTableColWidths::GROUP);
            printRowElement<string, PropTableColWidths>("PRICE", PropTableColWidths::PRICE);
            printRowElement<string, PropTableColWidths>("MORTG", PropTableColWidths::MORTGAGED);
            printRowElement<string, PropTableColWidths>("RENT", PropTableColWidths::RENT);
            printRowElement<string, PropTableColWidths>("HOUSES", PropTableColWidths::HOUSECOUNT);
            printRowElement<string, PropTableColWidths>("BUILD COST", PropTableColWidths::BUILDCOST);
            println(columnSeparator);
            longHorizontalSeparator();

            // Body
            uint i = 0;
            for (vector<Property *>::const_iterator p = properties.begin(); p < properties.end(); p++) {
                printRowElement<int, PropTableColWidths>(++i, PropTableColWidths::INDEX);
                (*p)->display(true);
                println(columnSeparator);
            }
            longHorizontalSeparator();
        } else {
            println("No properties owned.");
        }
    }

    void printOwnedGroupsDetails(const Player &player) {

        // Initialize counts
        array<int, GROUPCOUNT> counts = array<int, GROUPCOUNT>();
        for (uint i = 0; i < counts.size(); i++) {
            counts[i] = 0;
        }

        const vector<Property *> &properties = player.getProps();
        if (properties.size() != 0) {
            // Count properties in groups
            for (vector<Property *>::const_iterator p = properties.begin(); p < properties.end(); p++) {
                ++counts[(uint) (*p)->getGroup()];
            }

            // Header
            shortHorizontalSeparator();
            printRowElement<string, GroupTableColWidths>("", GroupTableColWidths::INDEX);
            printRowElement<string, GroupTableColWidths>("GROUP", GroupTableColWidths::GROUP);
            printRowElement<string, GroupTableColWidths>("OWNED", GroupTableColWidths::OWNED);
            printRowElement<string, GroupTableColWidths>("TOTAL", GroupTableColWidths::TOTAL);
            println(columnSeparator);
            shortHorizontalSeparator();

            // Body
            for (uint j = 0; j < counts.size(); j++) {
                printRowElement<int, GroupTableColWidths>(j + 1, GroupTableColWidths::INDEX);
                printRowElement<string, GroupTableColWidths>(groupName((PropGroup) j), GroupTableColWidths::GROUP);
                printRowElement<int, GroupTableColWidths>(counts[j], GroupTableColWidths::OWNED);
                printRowElement<int, GroupTableColWidths>(groupSize((PropGroup) j), GroupTableColWidths::TOTAL);
                println(columnSeparator);
            }
            shortHorizontalSeparator();
        }
    }

    void longHorizontalSeparator() {

        repeatChar('-', 1 + (uint) PropTableColWidths::TOTALWIDTH + 2 * (uint) PropTableColWidths::TOTALCOLUMNS);
        println();
    }

    void shortHorizontalSeparator() {

        repeatChar('-', 1 + (uint) GroupTableColWidths::TOTALWIDTH + 2 * (uint) GroupTableColWidths::TOTALCOLUMNS);
        println();
    }
}