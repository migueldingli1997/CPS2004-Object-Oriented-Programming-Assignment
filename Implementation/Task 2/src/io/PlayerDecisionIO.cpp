#include "PlayerDecisionIO.h"
#include "GeneralIO.h"

namespace io {

    using namespace std;

    bool yesNoDecision(const string message) {

        println(message);
        return boolIn();
    }

    uint valueDecision(const string message, const uint lowerLimit, const uint upperLimit) {

        println(message);
        return intIn(lowerLimit, upperLimit);
    }
}