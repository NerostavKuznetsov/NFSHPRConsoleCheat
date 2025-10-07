#include "../Source/Includes.h"

static void Banner()
{
	std::wcout << R"(
_________     _________   ______  ___     _________     
__  ____/___________  /   ___   |/  /___________  /____ 
_  / __ _  __ \  __  /    __  /|_/ /_  __ \  __  /_  _ \
/ /_/ / / /_/ / /_/ /     _  /  / / / /_/ / /_/ / /  __/
\____/  \____/\__,_/      /_/  /_/  \____/\__,_/  \___/   )";
}

void GodMode(HANDLE hProcess)
{
	system("cls");
	COLOR_GREEN();
	Banner();



	while (true)
	{



		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			return;
		}
	}
}

