#include <Includes.h>

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

void FunctionRacerWeaponsHack(HANDLE hProcess)
{
	system("cls");
    CONSOLE_CURSOR_INFO Cursor = { 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
    Banner();

    uintptr_t RacerWeaponsHack = modBaseAddr + 0x12791C0;
    uintptr_t FirstPointer = 0;
    uint32_t CurrentValue[4];
    uint32_t MaxSkillsValue = 99;
    uint32_t SkillsOffsets[] = { 0x5D0, 0x5D8, 0x5DC, 0x5E4 };
    static uint32_t OldSkillsValue[4] = { 0 }; // ➡️ Armazena os valores da corrida atual

    if (!ReadProcessMemory(hProcess, (LPCVOID)RacerWeaponsHack, &FirstPointer, sizeof(FirstPointer), nullptr))
    {
        COLOR_RED()
            std::wcout << L"\n\n[!] Failed to read FirstPointer at address!";
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        uintptr_t FinalAddress = FirstPointer + SkillsOffsets[i];

        if (!ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &CurrentValue[i], sizeof(CurrentValue[i]), nullptr))
        {
            COLOR_RED()
                std::wcout << L"\n\n[!] Failed to read memory at address!";
            return;
        }
    }

    // ➡️ Status = true  -> todos os valores são 99
    // ➡️ Status = false -> valores originais
    bool Status = (CurrentValue[0] == MaxSkillsValue && CurrentValue[1] == MaxSkillsValue && CurrentValue[2] == MaxSkillsValue && CurrentValue[3] == MaxSkillsValue);
    
    COLOR_RED()
    std::wcout << L"\n[!] Current values:";
    std::wcout << L"\n[!] SPIKES ----------------> " << CurrentValue[0];
    std::wcout << L"\n[!] TURBO -----------------> " << CurrentValue[1];
    std::wcout << L"\n[!] EMP -------------------> " << CurrentValue[2];
    std::wcout << L"\n[!] JAMMER ----------------> " << CurrentValue[3];
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
                    uintptr_t FinalAddress = FirstPointer + SkillsOffsets[i];

					if (OldSkillsValue[i] == 0) // ➡️ Se for a primeira vez que ativamos, salvamos o valor atual
                    {
                        ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &OldSkillsValue[i], sizeof(OldSkillsValue[i]), nullptr);
                    }
                    WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &MaxSkillsValue, sizeof(MaxSkillsValue), nullptr);
                }
                COLOR_GREEN()
                std::wcout << L"\n[*] Racer Weapons -> ON (99 SET)";
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    uintptr_t FinalAddress = FirstPointer + SkillsOffsets[i];
                    WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &OldSkillsValue[i], sizeof(OldSkillsValue[i]), nullptr);
                }
                COLOR_GREEN()
                std::wcout << L"\n[*] Racer Weapons -> OFF (OLD VALUES SET)";
            }

            Status = !Status;

            for (int i = 0; i < 4; i++)
            {
                uintptr_t FinalAddress = FirstPointer + SkillsOffsets[i];
                ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &CurrentValue[i], sizeof(CurrentValue[i]), nullptr);
            }

            Sleep(1666);
			system("cls");

			COLOR_GREEN()
            Banner();
            COLOR_RED()
            std::wcout << L"\n[!] Current values:";
            std::wcout << L"\n[!] SPIKES ----------------> " << CurrentValue[0];
            std::wcout << L"\n[!] TURBO -----------------> " << CurrentValue[1];
            std::wcout << L"\n[!] EMP -------------------> " << CurrentValue[2];
            std::wcout << L"\n[!] JAMMER ----------------> " << CurrentValue[3];
            std::wcout << L"\n\n[!] Racer Weapons are " << (Status ? L"ON (MAX VALUES)\n" : L"OFF (OLD VALUES)\n");
            std::wcout << L"[!] Press INSERT to toggle Racer Weapons or ESC to return to the main menu...\n";
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return;
        }
    }
}
