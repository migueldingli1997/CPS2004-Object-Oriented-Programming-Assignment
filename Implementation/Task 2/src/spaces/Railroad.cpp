#include "Railroad.h"
#include "../io/DetailsIO.h"

namespace spaces {

    using namespace std;

    Railroad::Railroad(const uint id, const string &name, const PropGroup group, const vector<Property *> &propGroup,
                       const uint price) : Property(id, name, group, propGroup, price) {}

    void Railroad::display(const bool table) const {

        // Print property details followed by two N/As
        Property::display(table);
        if (table) {
            io::printTwoRowElements_NA();
        }
    }

    uint Railroad::getRent() const {

        if (mortgaged) {
            return 0; // zero if property is mortgaged
        } else {
            switch (amountOwnedFromGroup()) {
                case 1:
                    return 25; // 1 railroad owned
                case 2:
                    return 50; // 2 railroads owned
                case 3:
                    return 100; // 3 railroads owned
                default:
                    return 200; // 4+ railroads owned
            }
        }
    }
}