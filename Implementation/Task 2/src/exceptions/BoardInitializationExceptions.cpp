#include "BoardInitializationExceptions.h"

const char *InvalidGameBoardIndexException::what() const throw() {
    return "GameBoard initialization index was incorrect.";
}

const char *InvalidSpaceIdException::what() const throw() {
    return "Space ID was incorrect (not equal to space's index in spaces array)";
}

const char *InvalidGameBoardGroupSizeException::what() const throw() {
    return "GameBoard initialization group size was incorrect.";
}

const char *NullSpaceException::what() const throw() {
    return "GameBoard initialization space was null.";
}
