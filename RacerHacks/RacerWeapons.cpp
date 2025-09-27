#include <Includes.h>

void FunctionRacerWeapons(HANDLE hProcess)
{
    system("cls");
    COLOR_GREEN()
        std::wcout << R"(
________                              ___       __                                        
___  __ \_____ ___________________    __ |     / /__________ _____________________________
__  /_/ /  __ `/  ___/  _ \_  ___/    __ | /| / /_  _ \  __ `/__  __ \  __ \_  __ \_  ___/
_  _, _// /_/ // /__ /  __/  /        __ |/ |/ / /  __/ /_/ /__  /_/ / /_/ /  / / /(__  ) 
/_/ |_| \__,_/ \___/ \___//_/         ____/|__/  \___/\__,_/ _  .___/\____//_/ /_//____/  
                                                             /_/                           )";
    uintptr_t RacerWeapons = modBaseAddr + 0x12791C0;
    uintptr_t FirstPointer = 0;
    uint32_t CurrentValue[4];
    uint32_t MaxSkillsValue = 99;
    uint32_t SkillsOffsets[] = { 0x5D0, 0x5D8, 0x5DC, 0x5E4 };
    static uint32_t OldSkillsValue[4] = { 0 }; // ➡️ Armazena os valores da corrida atual

    if (!ReadProcessMemory(hProcess, (LPCVOID)RacerWeapons, &FirstPointer, sizeof(FirstPointer), nullptr))
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

    bool Status = (CurrentValue[0] == MaxSkillsValue && CurrentValue[1] == MaxSkillsValue && CurrentValue[2] == MaxSkillsValue && CurrentValue[3] == MaxSkillsValue);
    // status = true  -> todos os valores são 99
    // status = false -> valores originais

    COLOR_RED()
        std::wcout << L"\n\n[!] Current values:";
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

                    if (OldSkillsValue[i] == 0)
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

            COLOR_RED()
            std::wcout << L"\n[!] SPIKES ----------------> " << CurrentValue[0];
            std::wcout << L"\n[!] TURBO -----------------> " << CurrentValue[1];
            std::wcout << L"\n[!] EMP -------------------> " << CurrentValue[2];
            std::wcout << L"\n[!] JAMMER ----------------> " << CurrentValue[3] << L"\n";
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return;
        }
    }
}
