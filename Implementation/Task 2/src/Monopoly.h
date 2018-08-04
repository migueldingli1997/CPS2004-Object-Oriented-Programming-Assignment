#ifndef TASK2_MONOPOLY_H
#define TASK2_MONOPOLY_H

#include <string>
#include <iostream>
#include "core/Player.h"
#include "core/GameBoard.h"
#include "core/GameEngine.h"
#include "io/GeneralIO.h"
#include "core/DicePair.h"

using namespace spaces;
using namespace core;
using namespace std;

class Monopoly final {

public:
    void start();
};

#endif //TASK2_MONOPOLY_H
