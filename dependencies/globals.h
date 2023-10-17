#pragma once
#include <iostream>

inline void LogAndExit(std::string message) {
	std::cout << message;
	system("pause");
	exit(1);
}

namespace globals
{
	inline uintptr_t BaseModule{};
	inline uintptr_t BaseAddress{};

	// Global feature variables
	inline bool bAutoHeal{ false };
	inline int iHealPercentage{ 50 };
	inline int iHealDelay{ 100 };

	inline bool bAutoMana{ false };
	inline int iManaPercentage{ 50 };
	inline int iManaDelay{ 100 };

	inline bool bZoom{ false };
	inline float fZoomValue{ 1.5f };

	// Temporary lazy keybind system
	inline int iSelectedHealKeybind = 0;
	inline int iSelectedManaKeybind = 0;

	inline const char* Keybinds[]
	{
		"NUM1",
		"NUM2",
		"NUM3",
		"NUM4",
		"NUM5"
	};

	inline const int GetKeybind(int code)
	{
		switch (code)
		{
		case 0:
			return '1';
			break;
		case 1:
			return '2';
			break;
		case 2:
			return '3';
			break;
		case 3:
			return '4';
			break;
		case 4:
			return '5';
			break;
		default:
			return NULL;
			break;
		}
	}
}