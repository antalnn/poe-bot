#include <Windows.h>
#include <iostream>
#include <thread>

#include "dependencies/gui/gui.h"

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow) {
#if _DEBUG
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);

	printf("base by antalnn\n");
#endif

	// create gui
	gui::CreateHWindow("example window");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{
		gui::BeginRender();

		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

#if _DEBUG
	fclose(file);
#endif

	return EXIT_SUCCESS;
}