#ifndef TASK2_PLAYEREXCEPTIONS_H
#define TASK2_PLAYEREXCEPTIONS_H

#include <exception>

/**
 * Exception used when the player's function to reduce money
 * is called, but the player does not have enough money. Such
 * a situation is avoided by using the player's affords function.
 */
class NotEnoughMoneyException : public std::exception {
    virtual const char *what() const throw();
};

#endif //TASK2_PLAYEREXCEPTIONS_H
