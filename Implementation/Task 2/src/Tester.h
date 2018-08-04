#ifndef TASK2_TESTER_H
#define TASK2_TESTER_H

#include <sys/param.h>
#include <vector>

namespace core {

    class GameBoard;

    class Player;
}

class Tester final {

public:
    void start();

private:
    const uint THOUSAND = 1000;

    void playerTest(const core::GameBoard &board);

    void propertyGeneralTest(const core::GameBoard &board);

    void propertyAuctionTest(const core::GameBoard &board);

    void propertyManagementTest(const core::GameBoard &board);

    void bankruptcyManagementTest(const core::GameBoard &board);
};

#endif //TASK2_TESTER_H