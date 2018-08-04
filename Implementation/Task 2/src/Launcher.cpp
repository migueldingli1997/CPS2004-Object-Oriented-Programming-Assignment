#include "Tester.h"
#include "Monopoly.h"
#include <iostream>

int main() {

    Tester tests = Tester();
    tests.start();

    std::cout << "\nStarting Monopoly...\n" << std::endl;

    Monopoly game = Monopoly();
    game.start();
}