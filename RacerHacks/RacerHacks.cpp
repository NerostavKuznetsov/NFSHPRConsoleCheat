/*
*
* "NFS11Remastered.exe"+012791C0 -> x -> x + 5D0 -> Final Address = y
*
* STEJ = {SPIKES(5D0), TURBO(5D8), EMP(5DC), JAMMER(5E4)};
*
*
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
//uintptr_t RacerHacksAddress = 0x1412791C0;
BYTE STEJ[] = { 0x5D0, 0x5D8, 0x5DC, 0x5E4 };
//BYTR Cu
//BYTE CurrentValue[4] = { 0 };








COLOR_RED()
std::wcout << L"\n[!] dBase address 0x" << std::hex << modBaseAddr << L"\n";
//std::wcout << L"\n[!] PID: "  << PID << L"\n";

	while (true)
	{



		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			return;
		}
	}
}




