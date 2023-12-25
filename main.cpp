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
	FILE* fs;
	freopen_s(&fs, "CONOUT$", "w", stdout);

	// Create GUI
	gui::CreateHWindow("example window");
	gui::CreateDevice();
	gui::CreateImGui();
	
	// Check for secure boot status
	if (globals::IsSecureBootEnabled())
	{
		LogAndExit("[-] Secure boot has to be disabled.\n", fs);
	}

	// Find process & get necessities
	if (!mem.GetProcessID("PathOfExileSteam.exe"))
	{
		LogAndExit("[-] Unable to find process.\n", fs);
	}

	if (!mem.GetProcessHandle())
	{
		LogAndExit("[-] Unable to get the handle of the process.\n", fs);
	}

	// Getting module data
	MODULEENTRY32 mod = mem.GetModuleEntry("PathOfExileSteam.exe");
	globals::BaseModule = (uintptr_t)mod.modBaseAddr;
	if (!globals::BaseModule)
	{
		LogAndExit("[-] Invalid Base Module.\n", fs);
	}
	globals::BaseModuleSize = (uintptr_t)mod.modBaseSize;
	if (!globals::BaseModuleSize)
	{
		LogAndExit("[-] Invalid Base Module Size.\n", fs);
	}

	// Getting offsets
	offsets::RunOffsetDumper();
	if (!offsets::GetOffsetsFromDump()) {
		LogAndExit("[-] Failed to get offsets from dump.\n", fs);
	}

	globals::BaseAddress = mem.Read<uintptr_t>(globals::BaseModule + offsets::player_base_address);
	if (!globals::BaseAddress) {
		LogAndExit("[-] Invalid Base Address\n", fs);
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

	if (fs != NULL)
		fclose(fs);

	return EXIT_SUCCESS;
}