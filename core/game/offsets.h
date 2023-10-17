#pragma once

namespace offsets
{

	// Steam; Patch: 3.22.1d
	constexpr uint32_t player_base_address = 0x02E8F068;
	constexpr uint32_t zoom_base_address = player_base_address - 0x88;

	// Netvars
	constexpr uint32_t m_iHealth[4] = { 0x58, 0x50, 0x48, 0x278 };
	constexpr uint32_t m_iMaxHealth[4] = { 0x58, 0x50, 0x48, 0x280 };

	constexpr uint32_t m_iMana[4] = { 0x58, 0x58, 0x48, 0x278 };
	constexpr uint32_t m_iMaxMana[4] = { 0x58, 0x58, 0x48, 0x280 };

	constexpr uint32_t m_Zoom[2] = { 0x78, 0x488 };
}