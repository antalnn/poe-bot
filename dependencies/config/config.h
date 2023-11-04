#pragma once

#include "../globals.h"
#include "simpleini.h"
#include <vector>
#include <filesystem>

namespace config {
	inline CSimpleIniA cfg;
	inline const char* config_name = "config.ini";

	inline void saveConfig()
	{
		cfg.SetBoolValue("auto-heal", "enabled", globals::bAutoHeal);
		cfg.SetLongValue("auto-heal", "key", globals::iSelectedHealKeybind);
		cfg.SetLongValue("auto-heal", "percentage", globals::iHealPercentage);
		cfg.SetLongValue("auto-heal", "delay", globals::iHealDelay);

		cfg.SetBoolValue("auto-mana", "enabled", globals::bAutoMana);
		cfg.SetLongValue("auto-mana", "key", globals::iSelectedManaKeybind);
		cfg.SetLongValue("auto-mana", "percentage", globals::iManaPercentage);
		cfg.SetLongValue("auto-mana", "delay", globals::iManaDelay);

		cfg.SetBoolValue("zoom", "enabled", globals::bZoom);
		cfg.SetDoubleValue("zoom", "value", globals::fZoomValue);

		cfg.SaveFile(config_name);
	}

	inline void loadConfig()
	{
		cfg.LoadFile(config_name);

		globals::bAutoHeal = cfg.GetBoolValue("auto-heal", "enabled", false);
		globals::iSelectedHealKeybind = cfg.GetLongValue("auto-heal", "key", 0);
		globals::iHealPercentage = cfg.GetLongValue("auto-heal", "percentage", 50);
		globals::iHealDelay = cfg.GetLongValue("auto-heal", "delay", 500);

		globals::bAutoMana = cfg.GetBoolValue("auto-mana", "enabled", false);
		globals::iSelectedManaKeybind = cfg.GetLongValue("auto-mana", "key", 0);
		globals::iManaPercentage = cfg.GetLongValue("auto-mana", "percentage", 50);
		globals::iManaDelay = cfg.GetLongValue("auto-mana", "delay", 500);

		globals::bZoom = cfg.GetBoolValue("zoom", "enabled", false);
		globals::fZoomValue = cfg.GetDoubleValue("zoom", "value", 1.5f);
	}
}