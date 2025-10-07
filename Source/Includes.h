#pragma once

// ➡️ Colors
#define COLOR_RED()     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_INTENSITY)
#define COLOR_GREEN()   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_YELLOW()  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY) 

// ➡️ Includes
#include <iostream>
#include <windows.h>
#include <tlHelp32.h>
#include <string>
#include <tchar.h>

// ➡️ Global extern variables
extern uintptr_t modBaseAddr;