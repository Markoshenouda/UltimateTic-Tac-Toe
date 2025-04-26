#pragma once
#include <vector>

bool isMoveValid(const std::vector<int> &used, int num);
void easyAI(const std::vector<char> &a, std::vector<int> &used, int &choice);
void mediumAI(const std::vector<char> &a, std::vector<int> &used, 
              int &choice, char aiSymbol, char playerSymbol);
void hardAI(const std::vector<char> &a, std::vector<int> &used, 
            int &choice, char aiSymbol);
int minimax(std::vector<char> board, bool isMaximizing, char aiSymbol, char playerSymbol);
