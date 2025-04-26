#include "../include/ai.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

bool isMoveValid(const std::vector<int> &used, int num) {
    return find(used.begin(), used.end(), num) == used.end();
}

void easyAI(const std::vector<char> &a, std::vector<int> &used, int &choice) {
    std::cout << " " << dice << " Computer is choosing randomly...\n";
    wait(500);
    choice = rand() % 9 + 1;
    while (!isMoveValid(used, choice)) {
        choice = rand() % 9 + 1;
    }
}

void mediumAI(const std::vector<char> &a, std::vector<int> &used, int &choice, 
              char aiSymbol, char playerSymbol) {
    std::cout << " " << brain << " Computer is strategizing...\n";
    wait(500);

    // Check for winning move
    for (int i = 0; i < 9; i++) {
        if (a[i] != 'X' && a[i] != 'O') {
            std::vector<char> temp = a;
            temp[i] = aiSymbol;
            if (checkWin(temp) == 1) {
                choice = i + 1;
                return;
            }
        }
    }

    // Block opponent
    for (int i = 0; i < 9; i++) {
        if (a[i] != 'X' && a[i] != 'O') {
            std::vector<char> temp = a;
            temp[i] = playerSymbol;
            if (checkWin(temp) == 1) {
                choice = i + 1;
                return;
            }
        }
    }

    // Prefer center
    if (a[4] == '5') {
        choice = 5;
        return;
    }

    // Then corners
    std::vector<int> corners = {0, 2, 6, 8};
    for (int corner : corners) {
        if (a[corner] != 'X' && a[corner] != 'O') {
            choice = corner + 1;
            return;
        }
    }

    // Otherwise random move
    choice = rand() % 9 + 1;
    while (!isMoveValid(used, choice)) {
        choice = rand() % 9 + 1;
    }
}

int minimax(std::vector<char> board, bool isMaximizing, char aiSymbol, char playerSymbol) {
    int result = checkWin(board);
    if (result == 1) return isMaximizing ? -10 : 10;
    if (result == 0) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                std::vector<char> temp = board;
                temp[i] = aiSymbol;
                int score = minimax(temp, false, aiSymbol, playerSymbol);
                bestScore = std::max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                std::vector<char> temp = board;
                temp[i] = playerSymbol;
                int score = minimax(temp, true, aiSymbol, playerSymbol);
                bestScore = std::min(score, bestScore);
            }
        }
        return bestScore;
    }
}

void hardAI(const std::vector<char> &a, std::vector<int> &used, int &choice, char aiSymbol) {
    std::cout << " " << genius << " Computer is calculating perfect move...\n";
    wait(500);

    int bestScore = -1000;
    int bestMove = -1;
    char playerSymbol = (aiSymbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 9; i++) {
        if (a[i] != 'X' && a[i] != 'O') {
            std::vector<char> temp = a;
            temp[i] = aiSymbol;
            int score = minimax(temp, false, aiSymbol, playerSymbol);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    choice = bestMove + 1;
}
