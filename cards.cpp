/* cards.cpp
 * The normal ruleset as stated in the instructions.
 */
#include "Cards.h"
#include <iostream>
#include <sstream>
#include <chrono>

enum DISCARD_END { TOP = 0, BOTTOM = 1 };

/* Scope based timer struct based on class from YouTube channel The Cherno https://www.youtube.com/watch?v=oEx5vGNFrLk */
/* Used for testing speed of algorithm */
struct Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        std::chrono::duration<double> duration;
    public:
        Timer() {
            start = std::chrono::high_resolution_clock::now();
        }
        ~Timer() {
            end = std::chrono::high_resolution_clock::now();
            duration = (end - start);
            std::cout << "The code ran in " << duration.count() << " seconds!" << std::endl;
        }
};

int main(int argc, char** argv) {
    if (argc < 4)
        std::cout << "Not enough parameters!" << std::endl << "Usage: " << argv[0] << " [num players] [num cards] [num turns]" << std::endl;

    int numPlayers, numCards, numTurns;
    auto read = [](const char* v_String, int& v_ID, int min) {
        std::stringstream ss(v_String);
        ss >> v_ID;
        if (ss.fail()) {
            std::cout << "Each parameter must be a valid integer number!" << std::endl;
            return 1;
        }
        else if (v_ID < min) {
            std::cout << "Parameters must be greater than " << min << std::endl;
            return 1;
        }
        return 0;
    };

    if (read(argv[1], numPlayers, 2)) return 1;
    if (read(argv[2], numCards, 1)) return 1;
    if (read(argv[3], numTurns, 1)) return 1;

    Player* players = new Player[numPlayers]; // create player objects
    
    for (int p = 0; p < numPlayers; p++) {
        players[p].initializeCardPile(numCards); // initialize players with set no. of cards
    }

    int randomNumber, givingPlayer, discardEnd, acceptingPlayer, currentTurn = 1, winner = 0;
    // Main Loop:
    while (currentTurn < numTurns + 1 && !winner) { // while there is no winner and turn limit isn't reached
        // std::cin recieves from stdin
        std::cin >> randomNumber;
        givingPlayer = randomNumber % numPlayers;
        std::cin >> randomNumber;
        discardEnd = randomNumber % 2;
        std::cin >> randomNumber;
        acceptingPlayer = randomNumber % numPlayers;
        std::string s_DiscardEnd = (discardEnd == 1 ? "bottom" : "top");
        std::cout << "turn " << currentTurn << ": player " << givingPlayer + 1
            << " sends a card to " << acceptingPlayer + 1 << ", from " 
            << s_DiscardEnd << std::endl;

        // Use calculations:
        Card* givenCard;
        switch (discardEnd) {
            case DISCARD_END::TOP: givenCard = players[givingPlayer].cardPile.deleteFromFront();
                    break;
            case DISCARD_END::BOTTOM: givenCard = players[givingPlayer].cardPile.deleteFromBack();
                    break;
        }
        players[acceptingPlayer].cardPile.insertAtFront(givenCard);
        if (!players[givingPlayer].cardPile.getWeight()) // If card pile's weight is 0:
            winner = givingPlayer + 1; // Player wins!

        // Display each players statistics:
        for (int i = 0; i < numPlayers; i++) {
            std::cout << "\tplayer " << i + 1 << ": weight: " << players[i].cardPile.getWeight() << std::endl;
        }
        currentTurn++;
    }

    if (winner) // If game ended by a player having no cards left:
        std::cout << "Game is over; player " << winner << " has no cards left." << std::endl;
    else { // If game ended by the turn limit being surpassed:
        int winningPlayer = 0;
        for (int i = 1; i < numPlayers; i++) {
            if (players[i].cardPile.getWeight() < players[winningPlayer].cardPile.getWeight())
                winningPlayer = i;
        }
        std::cout << "No more turns. Player " << winningPlayer + 1 << " wins." << std::endl;
    }

    delete[] players;

    return 0;
}