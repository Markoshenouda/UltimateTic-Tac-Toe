#pragma once
#include <vector>
#include <string>

void displayColorfulBoard(char x, char o, const std::string &u1, 
                         const std::string &u2, const std::vector<char> &a);
int checkWin(const std::vector<char> &a);
