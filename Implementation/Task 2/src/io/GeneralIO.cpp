#include "GeneralIO.h"
#include <iostream>
#include <limits>
#include <iomanip>

namespace io {

    using namespace std;

    void print(const string &toOutput) {
        cout << toOutput;
    }

    void println() {
        cout << endl;
    }

    void println(const string &toOutput) {
        print(toOutput + "\n");
    }

    void printlnIndented(const string &toOutput) {

        print(indent);
        println(toOutput);
    }

    bool boolIn() {

        char choice;
        do {
            print("Yes (y) or No (n). Decision: ");
            cin >> choice;
            switch (choice) {
                case 'y':
                    resetInput();
                    return true; // valid input
                case 'n':
                    resetInput();
                    return false; // valid input
                default:
                    printlnIndented("Invalid input.");
            }
        } while (true);
    }

    uint intIn(const uint lowerLimit, const uint upperLimit) {

        uint input;
        do {
            print("Insert a value");
            print(lowerLimit >= 0 ? " from " + to_string(lowerLimit) : "");
            if (upperLimit >= 0)
                print(" up to " + to_string(upperLimit));
            print(": ");

            cin >> input;

            if (cin.good()) {
                if (lowerLimit >= 0 && input < lowerLimit) {
                    printlnIndented("Value too low.");
                }
                else if (upperLimit >= 0 && input > upperLimit) {
                    printlnIndented("Value too high.");
                }
                else {
                    resetInput();
                    return input; // valid input
                }
            } else {
                printlnIndented("Invalid input.");
                resetInput();
            }
        } while (true);
    }

    // Reference :: http://stackoverflow.com/questions/903221/press-enter-to-continue
    void enterToContinue() {

        print("Press ENTER to continue...");
        cin.ignore();
    }

    // Reference :: http://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
    void resetInput() {

        cin.clear(); // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
    }

    void repeatChar(const char ch, const uint times) {
        cout << setw(times) << setfill(ch) << "";
    }
}