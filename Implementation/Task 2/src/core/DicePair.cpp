#include <random>
#include "DicePair.h"

namespace core {

    DicePair::DicePair() {
        reset();
    }

    void DicePair::roll() {

        if (!rolled) {
            dice1 = (rand() % SIDES) + 1;
            dice2 = (rand() % SIDES) + 1;
            rolled = true;
        }
    }

    uint DicePair::getDice1() const {
        return dice1;
    }

    uint DicePair::getDice2() const {
        return dice2;
    }

    void DicePair::reset() {

        dice1 = 0;
        dice2 = 0;
        rolled = false;
    };
}