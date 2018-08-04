#include "Utility.h"
#include "../io/DetailsIO.h"

namespace spaces {

    using namespace std;

    Utility::Utility(const uint id, const string &name, const PropGroup group, const vector<Property *> &propGroup,
                     const uint price) : Property(id, name, group, propGroup, price) {}

    void Utility::display(const bool table) const {

        // Print property details followed by two N/As
        Property::display(table);
        if (table) {
            io::printTwoRowElements_NA();
        }
    }

    uint Utility::getRent() const {

        if (mortgaged) {
            return 0; // zero if property is mortgaged
        } else if (amountOwnedFromGroup() == propGroup.size()) {
            // Represents a random throw of a pair of dice (1-6 and 1-6)
            return (uint) (((rand() % 6) + (rand() % 6) + 2)) * 10;
        } else {
            // Represents a random throw of a pair of dice (1-6 and 1-6)
            return (uint) (((rand() % 6) + (rand() % 6) + 2)) * 4;
        }
    }
}