#include "include/constants.hpp"
#include "include/utils.hpp"
#include "include/board.hpp"
#include "include/ai.hpp"
#include "include/leaderboard.hpp"
#include "include/menu.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <limits>

int main() {
    #ifdef _WIN32
        system("chcp 65001");
        system("color 0D");
    #endif

    srand(time(NULL));

    char x, o;
    int choice;
    std::string u1, u2;
    int menuChoice;
    std::vector<char> boardVec(9);
    char playAgain;
    int aiLevel = 0;

    while (true) {
        showRules();
        showMainMenu();

        while (!(std::cin >> menuChoice) || menuChoice < 1 || menuChoice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << RED << " " << warning << " Invalid input! Enter 1-4: " << RESET;
        }

        if (menuChoice == 4) {
            std::cout << "\n " << sparkle << " Thanks for playing! " << sparkle << "\n";
            break;
        }

        if (menuChoice == 3) {
            showLeaderboard();
            continue;
        }

        clearScreen();
        std::cout << " " << person << " Enter name of player 1: ";
        std::cin >> u1;

        if (menuChoice == 1) {
            std::cout << " " << person << " Enter name of player 2: ";
            std::cin >> u2;
        } else {
            u2 = "Computer";
            std::cout << "\n " << robot << " Select AI difficulty:\n";
            std::cout << " " << dice << " 1. Easy\n";
            std::cout << " " << brain << " 2. Medium\n";
            std::cout << " " << genius << " 3. Hard\n";
            std::cout << " " << check << " Enter choice (1-3): ";
            while (!(std::cin >> aiLevel) || aiLevel < 1 || aiLevel > 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << RED << " " << warning << " Invalid input! Enter 1-3: " << RESET;
            }
        }

        selectSymbol(x, o, u1);

        std::ofstream scoreFile("score.txt", std::ios::app);
        scoreFile << u1 << "\t" << u2 << "\t";
        scoreFile.close();

        do {
            boardVec = {'1','2','3','4','5','6','7','8','9'};
            std::vector<int> usedMoves;
            int currentPlayer = 1;
            int score = -1;

            while (score == -1) {
                displayColorfulBoard(x, o, u1, u2, boardVec);

                if (currentPlayer == 1 || menuChoice == 1) {
                    std::cout << " " << (currentPlayer == 1 ? u1 : u2) << ", enter position (1-9): ";
                    while (!(std::cin >> choice) || choice < 1 || choice > 9 ||
                           !isMoveValid(usedMoves, choice) || boardVec[choice-1] == 'X' || boardVec[choice-1] == 'O') {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << RED << " " << warning << " Invalid move! Try again: " << RESET;
                    }
                } else {
                    switch (aiLevel) {
                        case 1: easyAI(boardVec, usedMoves, choice); break;
                        case 2: mediumAI(boardVec, usedMoves, choice, o, x); break;
                        case 3: hardAI(boardVec, usedMoves, choice, o); break;
                    }
                    std::cout << " " << robot << " Computer chooses position " << choice << "\n";
                    wait(500);
                }

                usedMoves.push_back(choice);
                boardVec[choice-1] = (currentPlayer == 1) ? x : o;
                score = checkWin(boardVec);
                currentPlayer = (currentPlayer % 2) + 1;
            }

            displayColorfulBoard(x, o, u1, u2, boardVec);
            std::ofstream scoreFile("score.txt", std::ios::app);

            if (score == 1) {
                std::string winner = (currentPlayer == 1) ? u2 : u1;
                std::cout << GREEN << "\n " << trophy << " " << winner << " wins! " << trophy << "\n" << RESET;
                scoreFile << winner << "\n";
            } else {
                std::cout << YELLOW << "\n " << handshake << " It's a draw! " << handshake << "\n" << RESET;
                scoreFile << "DRAW\n";
            }
            scoreFile.close();

            std::cout << "\n " << star << " Play again with same players? (y/n): ";
            std::cin >> playAgain;
        } while (tolower(playAgain) == 'y');
    }

    return 0;
}
