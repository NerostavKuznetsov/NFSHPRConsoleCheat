/*
*  //uintptr_t RacerHacksAddress = 0x1412791C0;
* // Pointer path to STEJ skills
* "NFS11Remastered.exe"+012791C0 -> x -> x + 5D0 -> Final Address = y
*
* STEJ = {SPIKES(5D0), TURBO(5D8), EMP(5DC), JAMMER(5E4)};[
*/

#include <Includes.h>

void FunctionRacerHacks(HANDLE hProcess)
{
system("cls");
COLOR_GREEN()
std::wcout << R"(
________                              ______  __            ______         
___  __ \_____ ___________________    ___  / / /_____ _________  /_________
__  /_/ /  __ `/  ___/  _ \_  ___/    __  /_/ /_  __ `/  ___/_  //_/_  ___/
_  _, _// /_/ // /__ /  __/  /        _  __  / / /_/ // /__ _  ,<  _(__  ) 
/_/ |_| \__,_/ \___/ \___//_/         /_/ /_/  \__,_/ \___/ /_/|_| /____/   )";

uintptr_t RacerHacks = modBaseAddr + 0x12791C0;
BYTE SkillsOffsets[] = { 0x5D0, 0x5D8, 0x5DC, 0x5E4 };
BYTE CurrentValue[4] = { 0 };
BYTE DefaultSkillsValue = 0;
BYTE MaxSkillsValue = 99;

for (int i = 0; i < 4; i++)
{
	if (!ReadProcessMemory(hProcess, (LPCVOID)RacerHacks, &CurrentValue[i], sizeof(CurrentValue[i]), nullptr))
	{
		COLOR_RED()
		std::wcout << L"\n\n[!] Failed to read memory at address!";
		Sleep(1666);
		return;
	}
}

bool Status = (CurrentValue[0] == DefaultSkillsValue && CurrentValue[1] == DefaultSkillsValue && CurrentValue[2] == DefaultSkillsValue && CurrentValue[3] == DefaultSkillsValue);

std::wcout << L"...";






COLOR_RED()
std::wcout << L"\n[!] Base address: " << std::hex << modBaseAddr << L"\n";

	while (true)
	{






		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			return;
		}
	}
}




