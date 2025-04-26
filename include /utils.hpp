#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#define OS "nt"
#else
#define OS "posix"
#endif

void clearScreen();
void wait(int milliseconds);
