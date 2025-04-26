#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

void clearScreen() {
    if (OS == "nt") system("cls");
    else system("clear");
    std::cout << PURPLE << BOLD << "\n\t" << star << " ULTIMATE TIC-TAC-TOE " << star << RESET << "\n";
}

void wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
