#ifndef TASK2_PLAYERDECISIONIO_H
#define TASK2_PLAYERDECISIONIO_H

#include <string>

namespace io {

    /**
     * Displays the message (which should be in the form of a
     * question) and expects a yes/no answer from the user.
     *
     * @param message message output to the user
     * @return true if the user answered 'yes'
     */
    bool yesNoDecision(const std::string message);

    /**
     * Displays the message (which should be in the form of a
     * question) and asks the user to insert a value between
     * (and including) the lower and upper limits specified.
     *
     * @param message message output to the user
     * @param lowerLimit minimum value accepted
     * @param upperLimit maximum value accepted
     * @return a value in the range [lowerLimit, upperLimit]
     */
    uint valueDecision(const std::string message, const uint lowerLimit, const uint upperLimit);
}

#endif //TASK2_PLAYERDECISIONIO_H
