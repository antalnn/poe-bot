#pragma once
#include <iostream>

inline void LogAndExit(std::string message, FILE* fs = nullptr) {
	if (fs != nullptr)
		fclose(fs);

	std::cout << message;
	system("pause");
	exit(1);
}

namespace globals
{
	inline uintptr_t BaseModule{};
	inline uintptr_t BaseModuleSize{};
	inline uintptr_t BaseAddress{};

	// Global feature variables
	inline bool bAutoHeal{ false };
	inline int iHealPercentage{ 50 };
	inline int iHealDelay{ 500 };

	inline bool bAutoMana{ false };
	inline int iManaPercentage{ 50 };
	inline int iManaDelay{ 500 };

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

	inline bool IsForegroundWindow()
	{
		HWND hwndWindow = FindWindowA(NULL, "Path of Exile");
		if (hwndWindow == GetForegroundWindow())
			return true;

		return false;
	}

	inline bool IsSecureBootEnabled()
	{
		HKEY hKey{};
		LSTATUS status{ RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\SecureBoot\\State", 0, KEY_READ, &hKey) };
		if (status != ERROR_SUCCESS)
		{
			// The key does not exist, so Secure Boot is disabled.
			return false;
		}

		DWORD dwValue{};
		DWORD dwSize{ sizeof(dwValue) };
		status = RegQueryValueExW(hKey, L"UEFISecureBootEnabled", nullptr, nullptr, (LPBYTE)&dwValue, &dwSize);
		if (status != ERROR_SUCCESS)
		{
			// The registry value does not exist, so Secure Boot is disabled.
			RegCloseKey(hKey);
			return false;
		}

		// Check the Secure Boot state.
		bool secureBootEnabled{ false };
		if (dwValue == 0x01) {
			secureBootEnabled = true;
		}

		// Close the registry key.
		RegCloseKey(hKey);

		return secureBootEnabled;
	}
}