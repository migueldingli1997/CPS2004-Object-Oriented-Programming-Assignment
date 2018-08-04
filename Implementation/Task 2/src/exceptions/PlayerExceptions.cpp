#include "PlayerExceptions.h"

const char *NotEnoughMoneyException::what() const throw() {
    return "Player did not have enough money.";
}

