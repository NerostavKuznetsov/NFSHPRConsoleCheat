#include "../Source/Includes.h"

static void Banner() 
{
    std::wcout << R"(
________                              ___       __                                            ______  __            ______  
___  __ \_____ ___________________    __ |     / /__________ _____________________________    ___  / / /_____ _________  /__
__  /_/ /  __ `/  ___/  _ \_  ___/    __ | /| / /_  _ \  __ `/__  __ \  __ \_  __ \_  ___/    __  /_/ /_  __ `/  ___/_  //_/
_  _, _// /_/ // /__ /  __/  /        __ |/ |/ / /  __/ /_/ /__  /_/ / /_/ /  / / /(__  )     _  __  / / /_/ // /__ _  ,<   
/_/ |_| \__,_/ \___/ \___//_/         ____/|__/  \___/\__,_/ _  .___/\____//_/ /_//____/      /_/ /_/  \__,_/ \___/ /_/|_|  
                                                                /_/                                                               )";
}

void RacerWeaponsHack(HANDLE hProcess)
{
	system("cls");
    CONSOLE_CURSOR_INFO Cursor = { 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
    COLOR_GREEN();
    Banner();

    uintptr_t RacerWeaponsHack = (modBaseAddr + 0x12791C0);
    uint32_t RacerWeaponsOffsets[] = { 0x5D0, 0x5D8, 0x5DC, 0x5E4 };
    uint32_t CurrentValue[4];
    uint32_t MaxWeaponsValue = 99;
    static uint32_t OldWeaponsValue[4] = { 0 }; // ➡️ Armazena os valores da corrida atual

    uintptr_t FirstPointer = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)RacerWeaponsHack, &FirstPointer, sizeof(FirstPointer), nullptr))
    {
        COLOR_RED();
        std::wcout << L"\n\n[!] Failed to read FirstPointer at address!";
		Sleep(1666);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        uintptr_t FinalAddress = FirstPointer + RacerWeaponsOffsets[i];

        if (!ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &CurrentValue[i], sizeof(CurrentValue[i]), nullptr))
        {
            COLOR_RED();
            std::wcout << L"\n\n[!] Failed to read memory at address!";
            return;
        }
    }

    // ➡️ Status = true  -> todos os valores são 99
    // ➡️ Status = false -> Valores originais
    bool Status = (CurrentValue[0] == MaxWeaponsValue) && (CurrentValue[1] == MaxWeaponsValue) && (CurrentValue[2] == MaxWeaponsValue) && (CurrentValue[3] == MaxWeaponsValue);

    COLOR_RED();
    std::wcout << L"\n[!] Current values:";
    std::wcout << L"\n[!] SPIKES ----------------> " << CurrentValue[0]; // ➡️ 0x5D0
    std::wcout << L"\n[!] TURBO -----------------> " << CurrentValue[1]; // ➡️ 0x5D8
    std::wcout << L"\n[!] EMP -------------------> " << CurrentValue[2]; // ➡️ 0x5DC
    std::wcout << L"\n[!] JAMMER ----------------> " << CurrentValue[3]; // ➡️ 0x5E4

    std::wcout << L"\n\n[!] Racer Weapons are " << (Status ? L"ON (MAX VALUES)\n" : L"OFF (OLD VALUES)\n");
    std::wcout << L"[!] Press INSERT to toggle Racer Weapons or ESC to return to the main menu...\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!Status)
            {
                for (int i = 0; i < 4; i++)
                {
                    uintptr_t FinalAddress = FirstPointer + RacerWeaponsOffsets[i];

					if (OldWeaponsValue[i] == 0) // ➡️ Se for a primeira vez que ativamos, salvamos o valor atual
                    {
                        ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &OldWeaponsValue[i], sizeof(OldWeaponsValue[i]), nullptr);
                    }
                    WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &MaxWeaponsValue, sizeof(MaxWeaponsValue), nullptr);
                }
                COLOR_GREEN();
                std::wcout << L"\n[*] Racer Weapons -> ON (99 SET)";
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    uintptr_t FinalAddress = FirstPointer + RacerWeaponsOffsets[i];
                    WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &OldWeaponsValue[i], sizeof(OldWeaponsValue[i]), nullptr);
                }
                COLOR_GREEN();
                std::wcout << L"\n[*] Racer Weapons -> OFF (OLD VALUES SET)";
            }

            Status = !Status;

            for (int i = 0; i < 4; i++)
            {
                uintptr_t FinalAddress = FirstPointer + RacerWeaponsOffsets[i];
                ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &CurrentValue[i], sizeof(CurrentValue[i]), nullptr);
            }

            Sleep(666);
			system("cls");

            COLOR_GREEN();
            Banner();
            COLOR_RED();
            std::wcout << L"\n[!] Current values:";
            std::wcout << L"\n[!] SPIKES ----------------> " << CurrentValue[0];
            std::wcout << L"\n[!] TURBO -----------------> " << CurrentValue[1];
            std::wcout << L"\n[!] EMP -------------------> " << CurrentValue[2];
            std::wcout << L"\n[!] JAMMER ----------------> " << CurrentValue[3];

            std::wcout << L"\n\n[!] Racer Weapons are " << (Status ? L"ON (MAX VALUES)\n" : L"OFF (OLD VALUES)\n");
            std::wcout << L"[!] Press INSERT to toggle Racer Weapons Hack or ESC to return to the main menu...\n";
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return;
        }
    }
}
