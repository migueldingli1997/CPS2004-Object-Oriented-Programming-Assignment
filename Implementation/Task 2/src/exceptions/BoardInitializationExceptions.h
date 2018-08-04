#ifndef TASK2_BOARDINITIALIZATIONEXCEPTION_H
#define TASK2_BOARDINITIALIZATIONEXCEPTION_H

#include <exception>

/**
 * Exception used when one of the indexes that results
 * from the creation of the gameboard is not as expected
 */
class InvalidGameBoardIndexException : public std::exception {
    virtual const char *what() const throw();
};

/**
 * Exception used when one of the space IDs is not as
 * expected. Space IDs should be equal to the index of
 * the particular space in the main array of spaces.
 */
class InvalidSpaceIdException : public std::exception {
    virtual const char *what() const throw();
};

/**
 * Exception used when one of the spaces is null.
 */
class NullSpaceException : public std::exception {
    virtual const char *what() const throw();
};

/**
 * Exception used when one of the groups of spaces contains
 * more or less properties than the expected amount of spaces.
 */
class InvalidGameBoardGroupSizeException : public std::exception {
    virtual const char *what() const throw();
};

#endif //TASK2_BOARDINITIALIZATIONEXCEPTION_H
