#include "../include/menu.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

void showRules() {
    clearScreen();
    std::cout << ORANGE << BOLD << "\n\t" << star << " GAME RULES " << star << RESET << "\n\n";
    std::cout << " " << person << " Players take turns placing " << crossIcon << " or " << circleIcon << "\n";
    std::cout << " " << trophy << " First to get 3 in a row wins!\n";
    std::cout << " " << handshake << " Full board = Draw\n";
    std::cout << " " << fire << " Control center and corners!\n\n";

    char choice;
    std::cout << " " << link << " View tutorial? (Y/N): ";
    std::cin >> choice;
    if (tolower(choice) == 'y') {
        #ifdef _WIN32
            system("start https://www.wikihow.com/Play-Tic-Tac-Toe");
        #else
            system("xdg-open https://www.wikihow.com/Play-Tic-Tac-Toe");
        #endif
    }
}

void showMainMenu() {
    clearScreen();
    std::cout << CYAN << BOLD << "\n\t" << rainbow << " THE MAIN MENU " << rainbow << RESET << "\n\n";
    std::cout << " " << person << " " << PINK << "1. Human vs Human\n" << RESET;
    std::cout << " " << robot << " " << BLUE << "2. Human vs Computer\n" << RESET;
    std::cout << " " << trophy << " " << YELLOW << "3. Leaderboard\n" << RESET;
    std::cout << " " << warning << " " << RED << "4. Exit Game\n\n" << RESET;
    std::cout << " " << check << " Enter choice (1-4): ";
}

bool selectSymbol(char &x, char &o, const std::string &u1) {
    char dec;
    std::cout << " " << u1 << ", choose " << crossIcon << " (X) or " << circleIcon << " (O): ";
    while (!(std::cin >> dec) || (toupper(dec) != 'X' && toupper(dec) != 'O')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << " " << warning << " Invalid choice! Enter X or O: " << RESET;
    }

    x = toupper(dec);
    o = (x == 'X') ? 'O' : 'X';
    return true;
}
