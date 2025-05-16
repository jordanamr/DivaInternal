#pragma once
#include "Singleton.h"
#include "global.h"

namespace Cheat::Features
{
	class PipeServer : public Singleton<PipeServer>
	{
	public:
		PipeServer();

	private:
		inline static app::InteractiveCellManager* icmInstancePtr;
		static void InteractiveCellManager_moc_Hook(app::InteractiveCellManager* __this, bool a, MethodInfo* method);

		inline static app::dnm* dnmInstancePtr;
		static void dnm_rmo_Hook(app::dnm* __this, int64_t a, MethodInfo* method);

		static DWORD WINAPI PipeServerThread(LPVOID lpParam);
	};
}