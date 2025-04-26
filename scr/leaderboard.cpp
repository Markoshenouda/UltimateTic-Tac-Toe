#include "../include/leaderboard.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>

void showLeaderboard() {
    clearScreen();
    std::cout << GOLD << BOLD << "\n\t" << trophy << " LEADERBOARD " << trophy << RESET << "\n\n";
    std::cout << " " << std::string(50, '=') << "\n";
    std::cout << " " << std::setw(20) << std::left << "PLAYER"
              << std::setw(10) << "WINS"
              << std::setw(10) << "LOSSES"
              << std::setw(10) << "DRAWS" << "\n";
    std::cout << " " << std::string(50, '=') << "\n";

    std::ifstream scoreFile("score.txt");
    if (!scoreFile) {
        std::cout << " No game records found.\n";
        return;
    }

    std::map<std::string, std::vector<int>> stats;
    std::string line;

    while (getline(scoreFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('\t');
        size_t pos2 = line.find('\t', pos1 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos) continue;

        std::string player1 = line.substr(0, pos1);
        std::string player2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string result = line.substr(pos2 + 1);

        if (stats.find(player1) == stats.end()) stats[player1] = {0, 0, 0};
        if (stats.find(player2) == stats.end()) stats[player2] = {0, 0, 0};

        if (result == "DRAW") {
            stats[player1][2]++;
            stats[player2][2]++;
        } else {
            stats[result][0]++;
            std::string loser = (result == player1) ? player2 : player1;
            stats[loser][1]++;
        }
    }

    for (const auto& entry : stats) {
        std::cout << " " << std::setw(20) << std::left << entry.first << "  "
                  << std::setw(10) << GREEN << entry.second[0] << RESET
                  << std::setw(20) << RED << entry.second[1] << RESET
                  << std::setw(20) << YELLOW << entry.second[2] << RESET
                  << std::endl;
    }

    scoreFile.close();
    std::cout << " " << std::string(50, '=') << std::endl;
    std::cout << "\n " << star << " Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
