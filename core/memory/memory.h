#pragma once
#include <Windows.h>
#include <iostream>

#include "../../dependencies/globals.h"

class CMemory
{
private:
	HANDLE m_hGame{};
	DWORD m_dwPid{};
public:
	bool GetProcessID(const char* process_name);
	bool GetProcessHandle();
	uintptr_t GetProcessModule(const char* module_name);

	template <class T>
	T Read(uintptr_t address)
	{
		T buffer;
		ReadProcessMemory(m_hGame, (LPVOID)(address), &buffer, sizeof(T), 0);
		return buffer;
	}

	template <class T>
	void Write(uintptr_t address, T value)
	{
		WriteProcessMemory(m_hGame, (LPVOID)(address), &value, sizeof(T), 0);
	}

	uintptr_t ReadArray(const uintptr_t ptr, const uint32_t address_array[], const uint8_t size);
};
inline CMemory mem;

class CDriver
{
private:
	HMODULE hDll{};

	typedef int(*pButton)(int btn);
	typedef int(*pKey)(int keycode, int flag);
	typedef int(*pToVK)(int vk);
public:
	pButton		button;
	pKey		key;
	pToVK		toVK;

	CDriver()
	{
		this->hDll = LoadLibraryA("driver.dll");
		if (!this->hDll || this->hDll == nullptr)
		{
			LogAndExit("[-] Failed to load the driver\n");
		}

		button = (pButton)GetProcAddress(this->hDll, "DD_btn");
		key = (pKey)GetProcAddress(this->hDll, "DD_key");
		toVK = (pToVK)GetProcAddress(this->hDll, "DD_todc");

		if (!(button && key && toVK))
		{
			LogAndExit("[-] Failed to initialize modules\n");
		}

		int st = button(0);
		if (st != 1)
		{
			LogAndExit("[-] Failed to initialize modules\n");
		}
	}

	~CDriver()
	{
		FreeModule(this->hDll);
	}
};