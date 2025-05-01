#pragma once

#include "ConfigEntry.hpp"
#include "Hotkey.h"

class Vars final : public Singleton<Vars>
{
public:
	Vars() = default;

	// Features
	CONFIG_ENTRY_HOTKEY(bool, PipeServer, true, Hotkey());
	CONFIG_ENTRY(std::string, PipeServerName, "DivaInternal");
	CONFIG_ENTRY_HOTKEY(bool, RedirectConnect, true, Hotkey());
	CONFIG_ENTRY(std::string, RedirectConnectAddress, "127.0.0.1:5555");
	CONFIG_ENTRY_HOTKEY(bool, FightAntiAFK, true, Hotkey());
};
