#include "../include/board.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>

void displayColorfulBoard(char x, char o, const std::string &u1, 
                         const std::string &u2, const std::vector<char> &a) {
    clearScreen();

    // Player headers with icons
    std::cout << "\n " << person << " " << PINK << BOLD << u1 << RESET << " (" << (x == 'X' ? crossIcon : circleIcon) << ")\n";
    std::cout << " " << (u2 == "Computer" ? robot : person) << " " << CYAN << BOLD << u2 << RESET << " (" << (o == 'X' ? crossIcon : circleIcon) << ")\n\n";

    // Top border
    std::cout << "   " << cornerTL << horizontalLine << cornerTR << "\n";

    for (int i = 0; i < 9; i += 3) {
        std::cout << "   " << verticalLine;
        for (int j = i; j < i + 3; ++j) {
            char ch = a[j];
            if (ch == 'X') std::cout << " " << RED << BOLD << crossIcon << RESET << " " << verticalLine;
            else if (ch == 'O') std::cout << " " << BLUE << BOLD << circleIcon << RESET << " " << verticalLine;
            else std::cout << "  " << YELLOW << ch << "  " << verticalLine;
        }
        std::cout << "\n";

        if (i < 6) std::cout << "   " << tee << horizontalLine << "\n";
    }

    // Bottom border
    std::cout << "   " << cornerBL << horizontalLine << cornerBR << "\n\n";
}

int checkWin(const std::vector<char> &a) {
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto &combo : winCombos) {
        if (a[combo[0]] == a[combo[1]] && a[combo[1]] == a[combo[2]]) {
            return 1;
        }
    }

    for (char c : a) {
        if (c != 'X' && c != 'O') {
            return -1;
        }
    }

    return 0;
}
