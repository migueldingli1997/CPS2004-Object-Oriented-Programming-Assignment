#include "Monopoly.h"

void Monopoly::start() {

    // Randomness
    srand((unsigned) time(NULL));

    // Game board
    GameBoard board = GameBoard();

    // Players
    vector<Player *> players = vector<Player *>();
    io::println("How many players?");
    int amountOfPlayers = io::intIn(2, 20);
    
    string playerName; // stores inputs
    const uint startingMoney = 1500; // initial player balance

    // Create players
    bool nameTaken;
    string nameInput;
    for (int i=0; i < amountOfPlayers; i++) {
        io::print("Insert a unique name for player " + to_string(i + 1) + ": ");
        cin >> nameInput;

        nameTaken = false;
        for (vector<Player *>::const_iterator p = players.begin(); p < players.end(); p++) {
            if ((*p)->getName().compare(nameInput) == 0) {
                io::printlnIndented("\"" + nameInput + "\" already taken.");
                nameTaken = true;
                break;
            }
        }

        if (nameTaken) {
            i--; // so that name can get inserted again
        } else {
            players.push_back(new Player((uint) i, nameInput, startingMoney, board.getSpace(0)));
        }
    }

    DicePair dice = DicePair();
    GameEngine engine = GameEngine(board, players, dice);
    engine.start();
}