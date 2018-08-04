#include "Tester.h"
#include <string>
#include <iostream>
#include <assert.h>
#include "core/Player.h"
#include "core/GameBoard.h"
#include "core/GameEngine.h"
#include "spaces/Space.h"
#include "spaces/Property.h"
#include "core/BankruptcyManagement.h"
#include "io/GeneralIO.h"

using namespace spaces;
using namespace core;
using namespace std;

void Tester::start() {

    GameBoard board = GameBoard();

    cout << "Perform player test ?" << endl;
    if (io::boolIn()) {
        playerTest(board);
    }

    cout << "Perform general property test ?" << endl;
    if (io::boolIn()) {
        propertyGeneralTest(board);
    }

    cout << "Perform property auction test ?" << endl;
    if (io::boolIn()) {
        propertyAuctionTest(board);
    }

    cout << "Perform property management test ?" << endl;
    if (io::boolIn()) {
        propertyManagementTest(board);
    }

    cout << "Perform bankruptcy management test ?" << endl;
    if (io::boolIn()) {
        bankruptcyManagementTest(board);
    }
}

void Tester::playerTest(const GameBoard &board) {

    cout << "\nPerforming player test..." << endl;

    Player p1 = Player(0, "Player 1", THOUSAND, board.getSpace(0));
    Player p2 = Player(1, "Player 2", THOUSAND, board.getSpace(0));

    assert (p1.affords(p1.getBalance()));
    assert (!p1.affords(p1.getBalance()+1));

    const uint originalBalance = p1.getBalance();
    p1.gainMoney(p1.getBalance());
    assert (p1.getBalance() == 2 * originalBalance);
    p1.loseMoney(p1.getBalance());
    assert (p1.getBalance() == 0);

    assert (!p1.isBankrupt());
    p1.setToBankrupt();
    assert (p1.isBankrupt());

    p1.advanceTo(board.getSpace(5));
    assert (p1.getCurrSpaceId() == 5);

    assert (p1 == p1);
    assert (!(p1 != p1));
    assert (p1 != p2);
    assert (!(p1 == p2));

    cout << "Player test successfully ended." << endl;
    cout << "==================================================\n" << endl;
}

void Tester::propertyGeneralTest(const GameBoard &board) {

    cout << "\nPerforming property (general) test..." << endl;

    Property *prop = dynamic_cast<Property *>(board.getSpace(1)); // first property is at index 1
    Player p1 = Player(0, "Player 1", THOUSAND, board.getSpace(0));
    Player p2 = Player(1, "Player 2", THOUSAND, board.getSpace(0));

    const uint p1OriginalBalance = p1.getBalance();
    prop->transferTo(p1, p1OriginalBalance / 2);
    assert (p1.getProps().size() == 1);
    assert (p2.getProps().size() == 0);
    assert (p1.getProps().at(0) == prop); // p1 has the property
    assert (prop->isOwnedBy(p1)); // p1 now owner
    assert (!prop->isOwnedBy(p2)); // not owned by p2
    assert (p1.getBalance() == p1OriginalBalance / 2); // balance halved
    assert (p2.getBalance() == THOUSAND); // default balance

    const uint p2OriginalBalance = p2.getBalance();
    prop->transferTo(p2, p2OriginalBalance / 2);
    assert (p1.getProps().size() == 0);
    assert (p2.getProps().size() == 1);
    assert (p2.getProps().at(0) == prop); // p2 has the property
    assert (!prop->isOwnedBy(p1)); // no longer owned by p1
    assert (prop->isOwnedBy(p2)); // p2 now owner
    assert (p1.getBalance() == THOUSAND); // balance increased
    assert (p2.getBalance() == p2OriginalBalance / 2); // balance halved

    prop->resetOwner(); // This only resets pointer in property
    assert (!prop->isOwnedBy(p1));
    assert (!prop->isOwnedBy(p2));

    p2.removeProperty(*prop); // This only removes property from player
    assert (p1.getProps().size() == 0);
    assert (p2.getProps().size() == 0);

    cout << "Property (general) test successfully ended." << endl;
    cout << "==================================================\n" << endl;
}

void Tester::propertyAuctionTest(const core::GameBoard &board) {

    cout << "\nPerforming property (auction) test..." << endl;

    Property *prop = dynamic_cast<Property *>(board.getSpace(1)); // first property is at index 1
    Player p1 = Player(0, "Player 1", THOUSAND, board.getSpace(0));
    Player p2 = Player(1, "Player 2", THOUSAND, board.getSpace(0));
    Player p3 = Player(2, "Player 3", THOUSAND, board.getSpace(0));

    vector<Player *> allPlayers = vector<Player *>();
    allPlayers.push_back(&p1);
    allPlayers.push_back(&p2);
    allPlayers.push_back(&p3);

    cout << "--------------------------------------------------\n" << endl;

    // RUN AUCTION
    cout << prop->auction(allPlayers) << endl;

    if (p1.getProps().size() == 1)
        assert (prop->isOwnedBy(p1));
    else if (p2.getProps().size() == 1)
        assert (prop->isOwnedBy(p2));
    else if (p3.getProps().size() == 1)
        assert (prop->isOwnedBy(p3));

    cout << "--------------------------------------------------\n" << endl;

    // Reduce participants
    p3.setToBankrupt();

    // RUN AUCTION
    cout << prop->auction(allPlayers) << endl;

    cout << "--------------------------------------------------\n" << endl;

    // Reduce participants to zero
    p1.setToBankrupt();
    p2.setToBankrupt();

    // RUN AUCTION
    cout << prop->auction(allPlayers) << endl;

    cout << "Property (auction) test successfully ended." << endl;
    cout << "==================================================\n" << endl;
}

void Tester::propertyManagementTest(const core::GameBoard &board) {

    cout << "\nPerforming property (management) test..." << endl;

    Property *prop = dynamic_cast<Property *>(board.getSpace(1)); // first property is at index 1
    Player p1 = Player(0, "Player 1", THOUSAND, board.getSpace(0));
    Player p2 = Player(1, "Player 2", THOUSAND, board.getSpace(0));
    Player p3 = Player(2, "Player 3", THOUSAND, board.getSpace(0));

    vector<Player *> allPlayers = vector<Player *>();
    allPlayers.push_back(&p1);
    allPlayers.push_back(&p2);
    allPlayers.push_back(&p3);

    cout << "--------------------------------------------------\n" << endl;

    prop->transferTo(p1, THOUSAND / 2);
    manageProperties(p1, allPlayers);

    cout << "Property (management) test successfully ended." << endl;
    cout << "==================================================\n" << endl;
}

void Tester::bankruptcyManagementTest(const core::GameBoard &board) {

    cout << "\nPerforming bankruptcy test..." << endl;

    Property *prop = dynamic_cast<Property *>(board.getSpace(1)); // first property is at index 1
    Player p1 = Player(0, "Player 1", THOUSAND, board.getSpace(0));
    Player p2 = Player(1, "Player 2", THOUSAND, board.getSpace(0));
    Player p3 = Player(2, "Player 3", THOUSAND, board.getSpace(0));

    vector<Player *> allPlayers = vector<Player *>();
    allPlayers.push_back(&p1);
    allPlayers.push_back(&p2);
    allPlayers.push_back(&p3);

    cout << "--------------------------------------------------\n" << endl;

    tryRecover(p1, allPlayers, 0, "TEST"); // need to recover zero

    cout << "--------------------------------------------------\n" << endl;

    tryRecover(p1, allPlayers, THOUSAND, "TEST"); // need to recover 1000

    prop->transferTo(p1, 0); // give p1 a property
    assert (prop->isOwnedBy(p1));
    bankrupt_owesBank(p1, allPlayers); // p1 owes bank
    assert (!prop->isOwnedBy(p1));
    assert (p1.getBalance() == 0);

    cout << "--------------------------------------------------\n" << endl;

    prop->transferTo(p2, 0); // give p2 a property
    assert (prop->isOwnedBy(p2));

    const uint p2Balance = p2.getBalance();
    const uint p3Balance = p3.getBalance();

    bankrupt_owesPlayer(p2, p3); // p2 owes p3
    assert (prop->isOwnedBy(p3));
    assert (p2.getBalance() == 0);
    assert (p3.getBalance() == p2Balance + p3Balance);

    cout << "Bankruptcy test successfully ended." << endl;
    cout << "==================================================\n" << endl;
}