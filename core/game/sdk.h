#pragma once
#include <cstdint>
#include "../memory/memory.h"
#include "../../dependencies/globals.h"
#include "offsets.h"

class CPlayer
{
private:
public:
	int m_iCurrentHealth{};
	int m_iMaxHealth{};
	int m_iCurrentMana{};
	int m_iMaxMana{};

	void UpdateData()
	{
		globals::BaseAddress = mem.Read<uintptr_t>(globals::BaseModule + offsets::player_base_address);
		this->m_iCurrentHealth = (int)mem.ReadArray(globals::BaseAddress, offsets::m_iHealth, 4);
		this->m_iMaxHealth = (int)mem.ReadArray(globals::BaseAddress, offsets::m_iMaxHealth, 4);
		this->m_iCurrentMana = (int)mem.ReadArray(globals::BaseAddress, offsets::m_iMana, 4);
		this->m_iMaxMana = (int)mem.ReadArray(globals::BaseAddress, offsets::m_iMaxMana, 4);
	}

	bool ValidationCheck()
	{
		constexpr int16_t INVALID_VALUE{ 0x7530 };

		if (!globals::BaseAddress ||
			!this->m_iCurrentHealth || this->m_iCurrentHealth > INVALID_VALUE || this->m_iCurrentHealth < 0 ||
			!this->m_iMaxHealth || this->m_iMaxHealth > INVALID_VALUE || this->m_iMaxHealth < 0 ||
			!this->m_iCurrentMana || this->m_iCurrentMana > INVALID_VALUE || this->m_iCurrentMana < 0 ||
			!this->m_iMaxMana || this->m_iMaxMana > INVALID_VALUE || this->m_iMaxMana < 0)
			return false;

		return true;
	}
};
inline CPlayer player;

class N00000052
{
public:
	char pad_0000[88]; //0x0000
	class Player* PlayerPtr; //0x0058
}; //Size: 0x0060
static_assert(sizeof(N00000052) == 0x60);

class Player
{
public:
	char pad_0000[80]; //0x0000
	class N0000008D* N00000070; //0x0050
	class N00000079* N00000071; //0x0058
}; //Size: 0x0060
static_assert(sizeof(Player) == 0x60);

class N00000079
{
public:
	char pad_0000[72]; //0x0000
	class ManaData* ManaDataPtr; //0x0048
}; //Size: 0x0050
static_assert(sizeof(N00000079) == 0x50);

class N0000008D
{
public:
	char pad_0000[72]; //0x0000
	class HealthData* HealthDataPtr; //0x0048
}; //Size: 0x0050
static_assert(sizeof(N0000008D) == 0x50);

class ManaData
{
public:
	char pad_0000[632]; //0x0000
	int32_t m_iMana; //0x0278
	char pad_027C[4]; //0x027C
	int32_t m_iMaxMana; //0x0280
}; //Size: 0x0284
static_assert(sizeof(ManaData) == 0x284);

class HealthData
{
public:
	char pad_0000[632]; //0x0000
	int32_t m_iHealth; //0x0278
	char pad_027C[4]; //0x027C
	int32_t m_iMaxHealth; //0x0280
}; //Size: 0x0284
static_assert(sizeof(HealthData) == 0x284);