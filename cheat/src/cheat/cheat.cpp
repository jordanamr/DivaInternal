#include "cheat.h"
#include "global.h"
#include "HookManager.h"
#include "events.h"
#include "HotkeyManager.hpp"

// include features
#include "features/PipeServer.h"
#include "features/RedirectConnect.h"
#include "features/FightAntiAFK.h"

using namespace Cheat::Features;

static void AudioManagerListenerPositionProvider_Update_Hook(void* __this, MethodInfo* method);

void init_cheat()
{
#define INIT_FEATURE(feature) feature::GetInstance()
	INIT_FEATURE(PipeServer);
	INIT_FEATURE(RedirectConnect);
	INIT_FEATURE(FightAntiAFK);
#undef INIT_FEATURE

	HookManager::install(app::AudioManagerListenerPositionProvider_Update, AudioManagerListenerPositionProvider_Update_Hook);

	LOG("All cheat features successfully loaded.");
}

void AudioManagerListenerPositionProvider_Update_Hook(void* __this, MethodInfo* method)
{
	SAFE_BEGIN();
	events::GameUpdateEvent();
	HotkeyManager::GetInstance().CheckForKeyPress();
	SAFE_EEND();
	CALL_ORIGIN(AudioManagerListenerPositionProvider_Update_Hook, __this, method);
}