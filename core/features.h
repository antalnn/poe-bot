#pragma once

namespace hack
{
	inline CDriver driver;

	std::chrono::steady_clock::time_point healthLastExecutionTime = std::chrono::steady_clock::now();
	inline void AutoHeal()
	{
		if (!globals::bAutoHeal)
			return;

		// Bypass 'Too many actions' check
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		if (!(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - healthLastExecutionTime) >= std::chrono::milliseconds(globals::iHealDelay)))
			return;

		healthLastExecutionTime = currentTime;

		int currentHealth = player.m_iCurrentHealth;
		int maxHealth = player.m_iMaxHealth;

		int potionAt = maxHealth * globals::iHealPercentage / 100;
		if (currentHealth <= potionAt)
		{
			int key = driver.toVK(globals::GetKeybind(globals::iSelectedHealKeybind));

			driver.key(key, 1);
			Sleep(1);
			driver.key(key, 2);
		}
	}

	std::chrono::steady_clock::time_point manaLastExecutionTime = std::chrono::steady_clock::now();
	inline void AutoMana()
	{
		if (!globals::bAutoMana)
			return;

		// Bypass 'Too many actions' check
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		if (!(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - manaLastExecutionTime) >= std::chrono::milliseconds(globals::iManaDelay)))
			return;

		manaLastExecutionTime = currentTime;

		int currentMana = player.m_iCurrentMana;
		int maxMana = player.m_iMaxMana;

		int potionAt = maxMana * globals::iManaPercentage / 100;
		if (currentMana <= potionAt)
		{
			int key = driver.toVK(globals::GetKeybind(globals::iSelectedManaKeybind));

			driver.key(key, 1);
			Sleep(1);
			driver.key(key, 2);
		}
	}

	inline void Zoom()
	{
		if (!globals::bZoom)
			return;

		uintptr_t zoomBaseAddress = mem.Read<uintptr_t>(globals::BaseModule + offsets::zoom_base_address);
		mem.Write<float>(mem.Read<uintptr_t>(zoomBaseAddress + offsets::m_Zoom[0]) + offsets::m_Zoom[1], globals::fZoomValue);
	}
}