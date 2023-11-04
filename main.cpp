#include <Windows.h>
#include <iostream>
#include <thread>

#include "dependencies/globals.h"
#include "dependencies/gui/gui.h"
#include "core/memory/memory.h"

#include "core/game/sdk.h"
#include "core/features.h"

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow)
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);

	// Create GUI
	gui::CreateHWindow("example window");
	gui::CreateDevice();
	gui::CreateImGui();
	
	// check for secure boot status
	if (!globals::IsSecureBootEnabled())
	{
		LogAndExit("[-] Secure boot has to be disabled.\n");
	}

	// Find process & get necessities
	if (!mem.GetProcessID("PathOfExileSteam.exe"))
	{
		LogAndExit("[-] Unable to find process.\n");
	}

	if (!mem.GetProcessHandle())
	{
		LogAndExit("[-] Unable to get handle of the process.\n");
	}

	globals::BaseModule = mem.GetProcessModule("PathOfExileSteam.exe");
	if (!globals::BaseModule)
	{
		LogAndExit("[-] Unable to get handle of the process.\n");
	}

	globals::BaseAddress = mem.Read<uintptr_t>(globals::BaseModule + offsets::player_base_address);
	if (!globals::BaseAddress) {
		LogAndExit("[-] Invalid Base Address\n");
	}
	std::cout << std::hex << "Base Address: 0x" << globals::BaseAddress << '\n';

	// Main loop
	while (gui::isRunning)
	{
		// Updating player data
		player.UpdateData();

		// Features
		hack::AutoHeal();
		hack::AutoMana();
		hack::Zoom();

		// Rendering GUI
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// Destroy GUI
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	if (file != NULL)
		fclose(file);

	return EXIT_SUCCESS;
}