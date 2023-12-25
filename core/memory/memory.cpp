#include "memory.h"
#include <iostream>

bool CMemory::GetProcessID(const char* process_name)
{
	HANDLE hSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) }; // Creating a snapshot of the current running processes
	if (hSnapshot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32 pe32{}; // Process structure
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Looping through all processes, looking for the one with identical process_name
	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			if (_stricmp(pe32.szExeFile, process_name) == 0)
			{
				this->m_dwPid = static_cast<DWORD>(pe32.th32ProcessID);
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));
	}

	CloseHandle(hSnapshot);
	return this->m_dwPid ? true : false;
}

bool CMemory::GetProcessHandle()
{
	if (!this->m_dwPid)
	{
		std::cout << "[-] Unable to get HANDLE without a valid process" << "\n";
		return false;
	}

	this->m_hGame = OpenProcess(PROCESS_ALL_ACCESS, NULL, this->m_dwPid); // Getting the HANDLE of our window with desired permissions
	return (this->m_hGame != INVALID_HANDLE_VALUE) ? true : false;
}

MODULEENTRY32 CMemory::GetModuleEntry(const char* module_name)
{
	MODULEENTRY32 mod{}; // Module structure

	HANDLE hSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->m_dwPid) }; // Creating a snapshot of modules of the process
	if (hSnapshot == INVALID_HANDLE_VALUE) return MODULEENTRY32{};

	MODULEENTRY32 me32{}; // Module structure
	me32.dwSize = sizeof(MODULEENTRY32);

	// Looping through all modules, looking for the one with identical module_name
	if (Module32First(hSnapshot, &me32))
	{
		do
		{
			if (_stricmp(me32.szModule, module_name) == 0)
			{
				mod = me32;
				break;
			}
		} while (Module32Next(hSnapshot, &me32));
	}
	CloseHandle(hSnapshot);
	return mod;
}

uintptr_t CMemory::ReadArray(const uintptr_t ptr, const uint32_t address_array[], const uint8_t size)
{
	uintptr_t address = ptr;
	for (uint8_t i = 0; i < size; ++i)
	{
		address += address_array[i];
		address = Read<uintptr_t>(address);
	}
	return address;
}