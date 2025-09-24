/*
* NFSHPR - NK Cheats / NFSHPR - Console Basic Cheat
*
* |-------------------------------------|
* | [!] Status/Aviso/Info - RED         |
* | [*] Aplicado/Menu/ASCIIArt - GREEN  |
* | [~] Esperando - YELLOW              |
* | [?] Input - YELLOW                  |
* |-------------------------------------|
*
* [!] Este programa é um software livre: você pode redistribuí-lo e/ou modificá-lo como quiser.
*/

#include "Includes.h"

void ShowMenu()
{
    system("cls");
    COLOR_GREEN()
    std::wcout << R"(
_____   _______________________  _________________                _________                         ______          ________              _____           ______________             _____ 
___  | / /__  ____/_  ___/__  / / /__  __ \__  __ \               __  ____/____________________________  /____      ___  __ )_____ __________(_)______    __  ____/__  /____________ __  /_
__   |/ /__  /_   _____ \__  /_/ /__  /_/ /_  /_/ /  ________     _  /    _  __ \_  __ \_  ___/  __ \_  /_  _ \     __  __  |  __ `/_  ___/_  /_  ___/    _  /    __  __ \  _ \  __ `/  __/
_  /|  / _  __/   ____/ /_  __  / _  ____/_  _, _/   _/_____/     / /___  / /_/ /  / / /(__  )/ /_/ /  / /  __/     _  /_/ // /_/ /_(__  )_  / / /__      / /___  _  / / /  __/ /_/ // /_  
/_/ |_/  /_/      /____/ /_/ /_/  /_/     /_/ |_|                 \____/  \____//_/ /_//____/ \____//_/  \___/      /_____/ \__,_/ /____/ /_/  \___/      \____/  /_/ /_/\___/\__,_/ \__/   )";
    std::wcout << "\n\n";
    std::wcout << "                                                                                                                                                                               By: Nerostav Kuznetsov\n";
    COLOR_RED()
    std::wcout << L"[!] CTRL + CLICK to follow the link                                                        \n";
    std::wcout << L"[!] Steam:   https://steamcommunity.com/profiles/76561198304587027                          \n";
    std::wcout << L"[!] Insta:   https://instagram.com/nrstv_kuznetsov                                           \n";
    std::wcout << L"[!] Github:  https://github.com/NerostavKuznetsov/NFSHPRConsoleBasicCheat                     \n";
    std::wcout << L"[!] Youtub:  https://youtube.com/@Kuzntsv-666                                                  \n";
    COLOR_GREEN()
    std::wcout << L" \n";
    std::wcout << L"╔═══════════════════════════════════════╗\n";
    std::wcout << L"║               MAIN MENU               ║\n";
    std::wcout << L"╠═══════════════════════════════════════╣\n";
    std::wcout << L"║ 1  ➡️  Infinite Boost                 ║\n";
    std::wcout << L"║ 2  ➡️  Racer Hacks                    ║\n";
    std::wcout << L"║ 3  ➡️  Cop Hacks                      ║\n";
    std::wcout << L"║ 4  ➡️  *                              ║\n";
    std::wcout << L"║ 5  ➡️  *                              ║\n";
    std::wcout << L"║ 6  ➡️  *                              ║\n";
    std::wcout << L"║ 7  ➡️  *                              ║\n";
    std::wcout << L"║ 8  ➡️  *                              ║\n";
    std::wcout << L"║ 9  ➡️  *                              ║\n";
    std::wcout << L"║ z  ➡️  Exit                           ║\n";
	std::wcout << L"╠═══════════════════════════════════════╣\n";
    std::wcout << L"║ Need For Speed Hot Porsuit Remastered ║\n";
    std::wcout << L"╚═══════════════════════════════════════╝\n";
}

DWORD GetProcessIdByName(const std::wstring& processName)
{
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 PE32;
        PE32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32FirstW(hSnapshot, &PE32))
        {
            do
            {
                if (processName == PE32.szExeFile)
                {
                    processID = PE32.th32ProcessID;
                    break;
                }
            } while (Process32NextW(hSnapshot, &PE32));
        }
        CloseHandle(hSnapshot);
        return processID;
    }
}

uintptr_t GetModuleBaseAddress(uintptr_t ProcessID, const wchar_t* modBaseName) 
{
    uintptr_t baseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W MEW32;
        MEW32.dwSize = sizeof(MODULEENTRY32W);
        if (Module32FirstW(hSnapshot, &MEW32))
        {
            do
            {
                if (!_wcsicmp(MEW32.szModule, modBaseName))
                {
                    baseAddress = (uintptr_t)(MEW32.modBaseAddr); // <----
                    break;
                }
            } while (Module32NextW(hSnapshot, &MEW32));
        }
        CloseHandle(hSnapshot);
        return baseAddress;
    }
}

uintptr_t modBaseAddr = 0; 

int main()
{
    setlocale(LC_ALL, "PT_BR.UTF-8"); 
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleTitleA("NFSHPR - NK Cheats");

    DWORD PID = GetProcessIdByName(L"NFS11Remastered.exe");

    while (PID == 0) 
    {
        system("cls");
        COLOR_YELLOW()
        std::wcout << L"[~] Waiting for NFS11Remastered.exe";
        for (int i = 0; i < 6; i++)
        {
            std::wcout << L".";
            Sleep(666);
        }
        PID = GetProcessIdByName(L"NFS11Remastered.exe");

    }

    modBaseAddr = GetModuleBaseAddress(PID, L"NFS11Remastered.exe");

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    BOOL running = TRUE;

    while (running)
    {
        ShowMenu();
        COLOR_RED()
        std::wcout << L"\n[!] Base address: 0x" << std::hex << modBaseAddr << L"\n";
        std::wcout << L"[!] ProcessID: " << std::dec << PID << L"\n";
        COLOR_YELLOW()
        std::wcout << L"[?] Enter your option (1-9): ";
        std::wstring input;

        while (true)
        {
            wchar_t ch = _getwch();

            if (ch == 13) break;  
            if (ch == L'\b' && !input.empty())
            {
                input.pop_back();
                std::wcout << L"\b \b";
            }
            else if (iswdigit(ch) || ch == L'z') 
            {
                input += ch;
                std::wcout << ch;
            }
        }

        if (input.empty())
        {
            COLOR_RED()
            std::wcout << L"\n[!] Empty option\n";
            Sleep(1666);
            continue; 
        }
        else if (input.length() > 1)
        {
            COLOR_RED()
            std::wcout << L"\n[!] Invalid option. Please enter a single digit or 'z' to exit\n";
            Sleep(1666);
            continue; 
        }

        wchar_t option = input[0];

        switch (option) 
        {
        case '1':
            system("cls");
            FunctionInfiniteBoost(hProcess);
            break;
        case'2':
            system("cls");
            FunctionRacerHacks(hProcess);
			break;
        case 'z':
            system("cls");
            COLOR_RED()
            std::wcout << L"[!] Closing the program";
            for (int i = 0; i < 6; i++)
            {
                std::wcout << L".";
                Sleep(666);
            }
            Sleep(1666);
            running = FALSE; 
            break;
        }
    }
    CloseHandle(hProcess);
}