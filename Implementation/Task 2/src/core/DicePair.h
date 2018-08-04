#ifndef TASK2_DICEPAIR_H
#define TASK2_DICEPAIR_H

namespace core {

    class GameEngine;

    class DicePair final {

    public:
        friend class core::GameEngine; // so that only engine can reset the dice

        /**
         * The amount of sides each dice has
         */
        static const uint SIDES = 6;

        /**
         * Constructor (Note: resets the dice)
         */
        DicePair();

        /**
         * Generates two separate integer values from 1 to diceSides
         * corresponding to two dice rolls, IF the dice was not yet rolled.
         */
        void roll();

        /**
         * Returns the value of the first dice.
         *
         * @return integer value in the range [1, diceSides]
         */
        uint getDice1() const;

        /**
         * Returns the value of the second dice.
         *
         * @return integer value in the range [1, diceSides]
         */
        uint getDice2() const;

    private:
        uint dice1; // value of first dice (from 1 to SIDES)
        uint dice2; // value of second dice (from 1 to SIDES)
        bool rolled; // indicates if the dice was rolled

        /**
         * Resets the dice so that it can be rolled by a player.
         */
        void reset();
    };
}

#endif //TASK2_DICE_H
