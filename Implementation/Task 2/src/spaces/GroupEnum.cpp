#include "GroupEnum.h"

namespace core {

    const std::string groupName(const PropGroup theGroup) {

        switch (theGroup) {
            case PropGroup::BROWN:
                return "Brown";
            case PropGroup::CYAN:
                return "Cyan";
            case PropGroup::MAGENTA:
                return "Magenta";
            case PropGroup::ORANGE:
                return "Orange";
            case PropGroup::RED:
                return "Red";
            case PropGroup::YELLOW:
                return "Yellow";
            case PropGroup::GREEN:
                return "Green";
            case PropGroup::BLUE:
                return "Blue";
            case PropGroup::RAILROAD:
                return "Railroad";
            case PropGroup::UTILITY:
                return "Utility";
            default:
                return "DefaultGroupName";
        }
    }

    uint groupSize(const PropGroup theGroup) {

        switch (theGroup) {
            case PropGroup::BROWN:
                return 2;
            case PropGroup::BLUE:
                return 2;
            case PropGroup::RAILROAD:
                return 4;
            case PropGroup::UTILITY:
                return 2;
            default:
                return 3; // other
        }
    }
}
