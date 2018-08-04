#ifndef TASK2_GAMEBOARD_H
#define TASK2_GAMEBOARD_H

#include <vector>
#include <array>
#include "../spaces/GroupEnum.h"

namespace spaces {

    class Space;

    class Property;
}

namespace core {

    using namespace spaces;

    class Player;

    class DicePair;

    class GameBoard final {

    public:
        static const uint SPACECOUNT = 40; // Total amount of spaces on the board
        static const uint GOPAY = 200; // Amount given to a player that passes 'GO'

        /**
         * Initializes spaces and groups vectors
         */
        GameBoard();

        /**
         * Destructor deletes spaces
         */
        ~GameBoard();

        /**
         * Returns the space at the specified index. This index should be identical
         * to the ID of the space. The function automatically wraps around the index
         * so that a value greater than the spaces count is taken to mean a number
         * of spaces from the start (i.e. 40 wrapped to 0 to indicate the start)
         *
         * @param spaceIndex index at which the returned space is found
         * @return pointer to the space at the specified index
         */
        Space *getSpace(const uint spaceIndex) const;

    private:
        static const uint COLOURCOUNT = 8; // Total amount of different colours on the board
        static const uint TAXCOUNT = 2; // Total amount of tax spaces

        static const std::array<uint, COLOURCOUNT> STREETPRICES;
        static const std::array<uint, COLOURCOUNT> BUILDCOSTS;
        static const std::array<uint, COLOURCOUNT> RENTCOSTS;
        static const std::array<uint, TAXCOUNT> TAXCOSTS;
        static const std::array<PropGroup, COLOURCOUNT> STREETCOLOURS;
        static const std::array<std::string, SPACECOUNT> NAMES;

        uint id; // Space id
        uint spaceIndex; // Index/counter for space
        uint colourIndex; // Index/counter for colour group
        uint taxIndex; // Index/counter for tax space

        std::array<Space *, SPACECOUNT> spaces; // All space pointers that make up the board
        std::array<std::vector<Property *>, GROUPCOUNT> groups; // All property pointers, grouped by PropGroup

        /**
         * Returns the next space in the sequence of spaces that make
         * up the gameboard, according to the type parameter. Also
         * inserts a pointer to the space in the appropriate group.
         *
         * @tparam T the type of the space to create and return
         * @param id the id of the space to be created and returned
         * @return a pointer to the newly created space
         */
        template<typename T>
        Space *nextSpace(const uint id);

        /**
         * Validates the board with respect to four criteria
         *   - Checks that all indexes used during creation (spaceIndex,
         *     colourIndex, etc.) match the expected final values
         *   - Checks that space IDs are an ordered sequence (0-39)
         *   - Checks that none of the spaces is a null pointer
         *   - Checks that the group sizes match the expected sizes
         * Throws appropriate exception if a criteria is not met.
         */
        void validateBoard() const throw();
    };
}

#endif //TASK2_GAMEBOARD_H
