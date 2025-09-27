#include "Includes.h"

void FunctionInfiniteBoost(HANDLE hProcess)
{
	system("cls");	
	CONSOLE_CURSOR_INFO Cursor = { 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);

	COLOR_GREEN()
	std::wcout << R"(
________      ____________       __________           ________                   _____ 
____  _/_________  __/__(_)_________(_)_  /_____      ___  __ )____________________  /_
 __  / __  __ \_  /_ __  /__  __ \_  /_  __/  _ \     __  __  |  __ \  __ \_  ___/  __/
__/ /  _  / / /  __/ _  / _  / / /  / / /_ /  __/     _  /_/ // /_/ / /_/ /(__  )/ /_  
/___/  /_/ /_//_/    /_/  /_/ /_//_/  \__/ \___/      /_____/ \____/\____//____/ \__/   )";

	uintptr_t Instruction_Address = 0x1402BB332;  
	BYTE OriginalBytes[] = { 0xF3, 0x0F, 0x5C, 0xC8 };
	BYTE NOP_Bytes[4];
	BYTE CurrentValue[4] = { 0 };

	if(!ReadProcessMemory(hProcess, (LPCVOID)Instruction_Address, CurrentValue, sizeof(CurrentValue), nullptr))
	{
		COLOR_RED()
		std::wcout << L"\n\n[!] Failed to read at memory address";
		Sleep(1666);
		return;	
	}

	bool Status = (CurrentValue[0] == OriginalBytes[0] && CurrentValue[1] == OriginalBytes[1] && CurrentValue[2] == OriginalBytes[2] && CurrentValue[3] == OriginalBytes[3]);
	 
	std::fill(std::begin(NOP_Bytes), std::end(NOP_Bytes), 0x90);

	COLOR_RED()
	std::wcout << L"\n\n[!] Infinite Boost is " << (Status ? "disabled\n" : "enabled\n");
	std::wcout << L"[!] Press INSERT to toggle Infinite Boost or ESC to return to the main menu...\n";

	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			if (Status)
			{
				WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, NOP_Bytes, sizeof(NOP_Bytes), nullptr);
				COLOR_GREEN()
				std::wcout << L"[*] Infinite Boost has been successfully enabled\n";
			}
			else
			{
				WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, OriginalBytes, sizeof(OriginalBytes), nullptr);
				COLOR_GREEN()
				std::wcout << L"[*] Infinite Boost has been successfully disabled\n";
			}
			Status = !Status;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			return;
		}
	}
}