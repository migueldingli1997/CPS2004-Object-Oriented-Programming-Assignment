#include <array>
#include "GameBoard.h"
#include "../spaces/Xorti.h"
#include "../spaces/Tax.h"
#include "../spaces/Property.h"
#include "../spaces/Street.h"
#include "../spaces/Railroad.h"
#include "../spaces/Utility.h"
#include "../io/GeneralIO.h"
#include "../spaces/EmptySpace.h"
#include "../exceptions/BoardInitializationExceptions.h"

namespace core {

    using namespace std;
    using namespace spaces;

    const array<uint, GameBoard::COLOURCOUNT> GameBoard::STREETPRICES = {60, 100, 140, 180, 220, 260, 300, 375};
    const array<uint, GameBoard::COLOURCOUNT> GameBoard::BUILDCOSTS = {50, 50, 100, 100, 150, 150, 200, 200};
    const array<uint, GameBoard::COLOURCOUNT> GameBoard::RENTCOSTS = {3, 6, 10, 14, 18, 22, 26, 47}; // when 0 houses
    const array<uint, GameBoard::TAXCOUNT> GameBoard::TAXCOSTS = {100, 200};
    const array<PropGroup, GameBoard::COLOURCOUNT> GameBoard::STREETCOLOURS = {
            PropGroup::BROWN, PropGroup::CYAN, PropGroup::MAGENTA, PropGroup::ORANGE,
            PropGroup::RED, PropGroup::YELLOW, PropGroup::GREEN, PropGroup::BLUE};
    const array<string, GameBoard::SPACECOUNT> GameBoard::NAMES = {
            "GO", "MSIDA", "XORTI", "ZABBAR", "INCOME TAX", //0 to 4
            "VALLETTA STATION", "MARSASKALA", "XORTI", "QORMI", "MARSAXLOKK", // 5 to 9
            "JAIL", "MOSTA", "TAD-DAWL", "BIRKIRKARA", "NAXXAR", // 10 to 14
            "HAMRUN STATION", "VICTORIA", "XORTI", "ZEBBUG", "BIRGU", // 15 to 19
            "FREE PARKING", "MELLIEHA", "XORTI", "GHARGHUR", "NADUR", // 20 to 24
            "S.SALVATORE STATION", "SAN GILJAN", "SLIEMA", "TAL-ILMA", "BALZAN", // 25 to 29
            "GO TO JAIL", "PORTOMASO", "TIGNE POINT", "XORTI", "WARDIJA", // 30 to 34
            "MUSEUM STATION", "XORTI", "VALLETTA", "SUPER TAX", "MDINA"}; // 35 to 39

    template<>
    Space *GameBoard::nextSpace<Street>(const uint id) {

        Property *street = new Street(id, NAMES[id], STREETCOLOURS[colourIndex], groups[(uint) (STREETCOLOURS[colourIndex])],
                                      (uint) STREETPRICES[colourIndex], (uint) RENTCOSTS[colourIndex], (uint) BUILDCOSTS[colourIndex]);
        groups[(uint) (STREETCOLOURS[colourIndex])].push_back(street);
        return street;
    }

    template<>
    Space *GameBoard::nextSpace<Railroad>(const uint id) {

        Property *railroad = new Railroad(id, NAMES[id], PropGroup::RAILROAD, groups[(uint) PropGroup::RAILROAD], 200);
        groups[(uint) (PropGroup::RAILROAD)].push_back(railroad);
        return railroad;
    }

    template<>
    Space *GameBoard::nextSpace<Utility>(const uint id) {

        Property *utility = new Utility(id, NAMES[id], PropGroup::UTILITY, groups[(uint) (PropGroup::UTILITY)], 150);
        groups[(uint) (PropGroup::UTILITY)].push_back(utility);
        return utility;
    }

    template<>
    Space *GameBoard::nextSpace<Xorti>(const uint id) {
        return new Xorti(id, NAMES[id]);
    }

    template<>
    Space *GameBoard::nextSpace<Tax>(const uint id) {
        return new Tax(id, NAMES[id], TAXCOSTS[taxIndex++]);
    }

    template<>
    Space *GameBoard::nextSpace<EmptySpace>(const uint id) {
        return new EmptySpace(id, NAMES[id]);
    }

    GameBoard::GameBoard() : spaces(array<Space *, GameBoard::SPACECOUNT>()),
                             groups(array<vector<Property *>, GROUPCOUNT>()) {

        // Initializing groups
        for (uint i = 0; i < groups.size(); i++) {
            groups[i] = vector<Property *>();
        }

        // Initializing indexes
        spaceIndex = colourIndex = taxIndex = id = 0;

        // 0 to 4
        spaces[spaceIndex++] = nextSpace<EmptySpace>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Tax>(id++);
        colourIndex++; // next colour group

        // 5 to 9
        spaces[spaceIndex++] = nextSpace<Railroad>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 10 to 14
        spaces[spaceIndex++] = nextSpace<EmptySpace>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Utility>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 15 to 19
        spaces[spaceIndex++] = nextSpace<Railroad>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 20 to 24
        spaces[spaceIndex++] = nextSpace<EmptySpace>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 25 to 29
        spaces[spaceIndex++] = nextSpace<Railroad>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Utility>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 30 to 34
        spaces[spaceIndex++] = nextSpace<EmptySpace>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // next colour group

        // 35 to 39
        spaces[spaceIndex++] = nextSpace<Railroad>(id++);
        spaces[spaceIndex++] = nextSpace<Xorti>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        spaces[spaceIndex++] = nextSpace<Tax>(id++);
        spaces[spaceIndex++] = nextSpace<Street>(id++);
        colourIndex++; // to get to colourCount

        validateBoard();

        io::println("Gameboard created.");
    }

    GameBoard::~GameBoard() {

        for (uint i = 0; i < spaces.size(); i++) {
            delete spaces[i];
        }
        io::println("Spaces deleted.");
    }

    void GameBoard::validateBoard() const throw() {

        // Checking final indexes
        InvalidGameBoardIndexException exc1;
        if (id != SPACECOUNT || spaceIndex != SPACECOUNT || colourIndex != COLOURCOUNT || taxIndex != TAXCOUNT) {
            throw exc1;
        }

        // Checking spaces and space IDs
        InvalidSpaceIdException exc2;
        NullSpaceException exc3;
        for (uint i = 0; i < spaces.size(); i++) {
            if (spaces[i]->getId() != i) {
                throw exc2;
            } else if (spaces[i] == nullptr) {
                throw exc3;
            }
        }

        // Checking group sizes
        InvalidGameBoardGroupSizeException exc4;
        for (uint i = 0; i < groups.size(); i++) {
            if (groups[i].size() != groupSize((PropGroup) i)) {
                throw exc4;
            }
        }
    }

    Space *GameBoard::getSpace(const uint spaceIndex) const {
        return spaces[spaceIndex % spaces.size()];
    }
}