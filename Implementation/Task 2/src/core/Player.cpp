#include <algorithm>
#include "Player.h"
#include "../io/GeneralIO.h"
#include "DicePair.h"
#include "../spaces/Space.h"
#include "../exceptions/PlayerExceptions.h"
#include "GameBoard.h"

namespace core {

    using namespace spaces;
    using namespace std;

    Player::Player(const uint id, const string &name, uint startBalance, const Space *startSpace) :
            id(id), name(name), balance(startBalance), currentSpaceId(startSpace->getId()),
            properties(vector<Property *>()), bankrupt(false) {
        io::printlnIndented(name + " created.");
    }

    void Player::gainMoney(const uint amount) {
        balance += amount;
    }

    void Player::loseMoney(uint amount) throw() {

        if (affords(amount)) {
            balance -= amount;
        } else {
            // Avoided by using method affords before calling this function
            NotEnoughMoneyException exc;
            throw exc;
        }
    }

    bool Player::affords(const uint amount) const {
        return balance >= amount;
    }

    void Player::rollDice(DicePair &toRoll) const {
        toRoll.roll();
    }

    void Player::addProperty(Property &prop) {
        properties.push_back(&prop);
    }

    void Player::removeProperty(const Property &prop) {
        properties.erase(remove(properties.begin(), properties.end(), &prop), properties.end());
    }

    uint Player::getBalance() const {
        return balance;
    }

    const uint Player::getCurrSpaceId() const {
        return currentSpaceId;
    }

    const vector<Property *> &Player::getProps() const {
        return properties;
    }

    bool Player::isBankrupt() const {
        return bankrupt;
    }

    void Player::advanceTo(const Space *newSpace) {
        currentSpaceId = (newSpace->getId()) % GameBoard::SPACECOUNT;
    }

    void Player::setToBankrupt() {
        bankrupt = true;
    }

    const std::string Player::getName() const {
        return name;
    }

    bool Player::operator==(const Player &player) const {
        return id == player.id;
    }

    bool Player::operator!=(const Player &player) const {
        return id != player.id;
    }

    ostream &operator<<(ostream &os, const Player &p) {

        os << p.getName();
        return os;
    }
}