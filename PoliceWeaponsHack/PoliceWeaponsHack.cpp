#include "Includes.h"

static void Banner()
{
    std::wcout << R"(  
________      __________                 ___       __                                            ______  __            ______  
___  __ \________  /__(_)__________      __ |     / /__________ _____________________________    ___  / / /_____ _________  /__
__  /_/ /  __ \_  /__  /_  ___/  _ \     __ | /| / /_  _ \  __ `/__  __ \  __ \_  __ \_  ___/    __  /_/ /_  __ `/  ___/_  //_/
_  ____// /_/ /  / _  / / /__ /  __/     __ |/ |/ / /  __/ /_/ /__  /_/ / /_/ /  / / /(__  )     _  __  / / /_/ // /__ _  ,<   
/_/     \____//_/  /_/  \___/ \___/      ____/|__/  \___/\__,_/ _  .___/\____//_/ /_//____/      /_/ /_/  \__,_/ \___/ /_/|_|  
                                                                /_/                                                               )";
}

void FunctionPoliceWeaponsHack(HANDLE hProcess)
{
    system("cls");
    CONSOLE_CURSOR_INFO Cursor = { 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
    COLOR_GREEN()
    Banner();

    uintptr_t PoliceWeaponsHack = modBaseAddr + 0x12791C0; 
    uint32_t PoliceWeaponsOffsets[] = { 0x5C8, 0x5CC, 0x5D4, 0x5E8 };
    uint32_t CurrentValue[4];
    uint32_t MaxWeaponsValue = 99;
    static uint32_t OldWeaponsValue[4] = { 0 };

    uintptr_t FirstPointer = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)PoliceWeaponsHack, &FirstPointer, sizeof(FirstPointer), nullptr))
    {
        std::wcout << L"\n\n[!] Failed to read FirstPointer at address!";
        return;
    } 

    std::wcout << L"Primeiro ponteiro: " << FirstPointer << "";







    while (true)
    {
        
        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
           
            return; 
        }
    }
}
