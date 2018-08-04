#ifndef TASK2_UTILITY_H
#define TASK2_UTILITY_H

#include "Property.h"

namespace spaces {

    class Utility final : public Property {

    public:
        /**
         * @param id space ID
         * @param name space name
         * @param group group that property belongs to
         * @param propGroup pointers to all properties in group
         * @param price cost to purchase the property
         */
        Utility(const uint id, const std::string &name, const PropGroup group, const std::vector<Property *> &propGroup,
                const uint price);

        /**
         * Calls the superclass display and prints out
         * an additional two elements containing N/A if
         * the output is intended to be in table form.
         *
         * @param table true to output in table form
         */
        void display(const bool table) const override;

        /**
         * Calculated by simulating two dice throws and
         * multiplying accordingly based on whether the
         * group of properties is owned by the owner or not.
         *
         * @return rent to be paid
         */
        uint getRent() const override;
    };
}

#endif //TASK2_UTILITY_H
