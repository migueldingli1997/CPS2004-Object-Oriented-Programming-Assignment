#ifndef TASK2_GENERALIO_H
#define TASK2_GENERALIO_H

#include <string>
#include <vector>
#include <array>
#include "../spaces/GroupEnum.h"

namespace io {

    // Standard indentation usually used to display a note
    const std::string indent = "\t";

    // Prints a particular string (without newline)
    void print(const std::string &toOutput);

    // Prints a newline
    void println();

    // Prints a particular string with a newline
    void println(const std::string &toOutput);

    // Prints an indented string with a newline
    void printlnIndented(const std::string &toOutput);

    // Asks for a general yes (y) or no (n) answer
    bool boolIn();

    // Asks for an integer in the range [lowerLimit, upperLimit]
    uint intIn(const uint lowerLimit, const uint upperLimit);

    // Asks the user to press enter to continue
    void enterToContinue();

    // Clears the input buffer
    void resetInput();

    // Outputs a particular character for a number of times
    void repeatChar(const char ch, const uint times);
}

#endif //TASK2_INPUTOUTPUT_H
