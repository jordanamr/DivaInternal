#pragma once
#include "Singleton.h"
#include "global.h"

namespace Cheat::Features
{
	class FightAntiAFK : public Singleton<FightAntiAFK>
	{
	public:
		FightAntiAFK();

	private:
		static void InputChecker_Update_Hook(app::InputChecker* __this, MethodInfo* method);
		inline static bool forceInput = false;
		static bool Input_get_anyKey_Hook(MethodInfo* method);
	};
}