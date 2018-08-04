#ifndef TASK2_RAILROAD_H
#define TASK2_RAILROAD_H

#include <array>
#include "Property.h"

namespace spaces {

    class Railroad final : public Property {

    public:
        /**
         * @param id space ID
         * @param name space name
         * @param group group that property belongs to
         * @param propGroup pointers to all properties in group
         * @param price cost to purchase the property
         */
        Railroad(const uint id, const std::string &name, const PropGroup group, const std::vector<Property *> &propGroup,
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
         * Calculated based on the number of Railroad
         * properties owned by the Railroad's owner.
         *
         * @return rent to be paid
         */
        uint getRent() const override;
    };
}

#endif //TASK2_RAILROAD_H
