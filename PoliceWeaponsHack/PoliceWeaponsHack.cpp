#include "../Source/Includes.h"

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
    COLOR_GREEN();
    Banner();

    uintptr_t PoliceWeaponsHack = modBaseAddr + 0x12791C0; 
    uint32_t PoliceWeaponsOffsets[] = { 0x5C8, 0x5CC, 0x5D4, 0x5E8 };
    uint32_t CurrentValue[4];
    uint32_t MaxWeaponsValue = 99;
    static uint32_t OldWeaponsValue[4] = { 0 };

    uintptr_t FirstPointer = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)PoliceWeaponsHack, &FirstPointer, sizeof(FirstPointer), nullptr))
    {
        COLOR_RED();
        std::wcout << L"\n\n[!] Failed to read FirstPointer at address!";
        return;
    } 

    for (int i = 0; i < 4; i++)
    {
        uintptr_t FinalAddress = FirstPointer + PoliceWeaponsOffsets[1];

        if (!ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &CurrentValue, sizeof(CurrentValue[i]), nullptr))
        {
            COLOR_RED();
            std::wcout << L"\n\n[!] Failed to read memory at address!";
            return;
        }
    }

    bool Status = (CurrentValue[0] == MaxWeaponsValue && CurrentValue[1] == MaxWeaponsValue && CurrentValue[2] == MaxWeaponsValue && CurrentValue[3] == MaxWeaponsValue);

    COLOR_RED();
    std::wcout << L"\n[!] Current values:";
    std::wcout << L"\n[!] HELICOPTER ----------------> " << CurrentValue[0]; // ➡️ 0x5C8
    std::wcout << L"\n[!] COP EMP -------------------> " << CurrentValue[1]; // ➡️ 0x5CC
    std::wcout << L"\n[!] COP SPIKES ----------------> " << CurrentValue[2]; // ➡️ 0x5D4
    std::wcout << L"\n[!] COP ROADBLOCKS ------------> " << CurrentValue[3]; // ➡️ 0x5E8

    std::wcout << L"\n\n[!] Police Weapons are " << (Status ? L"ON (MAX VALUES)\n" : L"OFF (OLD VALUES)\n");
    std::wcout << L"[!] Press INSERT to toggle Police Weapons or ESC to return to the main menu...\n";

   while (true)
    {
        //if (GetAsyncKeyState(VK_INSERT) & 1)
        //{
            //for (int i = 0; i < 4; i++)
            //{

                //uintptr_t FinalAddress = FirstPointer + PoliceWeaponsOffsets[i];

                //if (OldWeaponsValue[i] == 0)
                //{
                    //ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &OldWeaponsValue[i], sizeof(OldWeaponsValue[i], nullptr));
                //
                //WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &MaxWeaponsValue, sizeof(MaxWeaponsValue), nullptr);
            //}
            //COLOR_GREEN();
            //std::wcout << L"\n[*] Police Weapons Hack -> ON (99 SDDDET)";
        //}

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
           
            return; 
        }
    }
}
