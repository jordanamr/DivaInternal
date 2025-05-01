#include "FightAntiAFK.h"
#include "events.h"
#include "HookManager.h"
#include "Utils.h"
#include "game-utils.hpp"

namespace Cheat::Features
{
	FightAntiAFK::FightAntiAFK()
	{
		HookManager::install(app::InputChecker_Update, InputChecker_Update_Hook);
		HookManager::install(app::Input_get_anyKey, Input_get_anyKey_Hook);
	}

	void FightAntiAFK::InputChecker_Update_Hook(app::InputChecker* __this, MethodInfo* method)
	{
		auto& vars = Vars::GetInstance();

		if (!vars.FightAntiAFK.value()) {
			// Cheat is disabled, proceed with real call
			CALL_ORIGIN(InputChecker_Update_Hook, __this, method);
			return;
		}

		// Mark the next Unity input check as valid
		forceInput = true;

		// Force the call now to trick it
		CALL_ORIGIN(InputChecker_Update_Hook, __this, method);

		// Unmark
		forceInput = false;
	}

	bool FightAntiAFK::Input_get_anyKey_Hook(MethodInfo* method)
	{
		if (forceInput) {
			return true;
		}
		else {
			CALL_ORIGIN(Input_get_anyKey_Hook, method);
		}
	}
}