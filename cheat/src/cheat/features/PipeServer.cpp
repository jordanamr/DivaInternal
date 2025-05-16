#include "PipeServer.h"
#include "events.h"
#include "HookManager.h"
#include "Utils.h"
#include "game-utils.hpp"

namespace Cheat::Features
{
    PipeServer::PipeServer()
    {
        HookManager::install(app::InteractiveCellManager_moc, InteractiveCellManager_moc_Hook);
        HookManager::install(app::dnm_rmo, dnm_rmo_Hook);
        CreateThread(nullptr, 0, PipeServerThread, nullptr, 0, nullptr);
    }

    void PipeServer::InteractiveCellManager_moc_Hook(app::InteractiveCellManager* __this, bool a, MethodInfo* method)
    {
        if (icmInstancePtr == nullptr) {
            // Capture a pointer to the InteractiveCellManager instance
            icmInstancePtr = __this;
        }
        LOG("InteractiveCellManager_moc_Hook called with a: %d", a);
        CALL_ORIGIN(InteractiveCellManager_moc_Hook, __this, a, method);
    }

    void PipeServer::dnm_rmo_Hook(app::dnm* __this, int64_t a, MethodInfo* method)
    {
        if (dnmInstancePtr == nullptr) {
            // Capture a pointer to the dnm instance
            dnmInstancePtr = __this;
        }
        CALL_ORIGIN(dnm_rmo_Hook, __this, a, method);
    }

    DWORD WINAPI PipeServer::PipeServerThread(LPVOID lpParam) {
        il2cpp_thread_attach(il2cpp_domain_get());
        auto& vars = Vars::GetInstance();

        HANDLE hPipe;
        char buffer[256];
        DWORD bytesRead;

        std::string fullPipeName = R"(\\.\pipe\)" + vars.PipeServerName.value();
        hPipe = CreateNamedPipeA(
            fullPipeName.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
            1, 256, 256, 0, nullptr);

        if (hPipe == INVALID_HANDLE_VALUE) {
            LOG(xorstr("Failed to create named pipe. Error: %lu"), GetLastError());
            return 1;
        }

        while (true) {
            if (!vars.PipeServer.value()) continue;
            if (ConnectNamedPipe(hPipe, nullptr) || GetLastError() == ERROR_PIPE_CONNECTED) {
                while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) != FALSE) {
                    buffer[bytesRead] = '\0';
                    LOG(xorstr("Received command: %s"), buffer);

                    // Parse command (expected format: "autopilot <mapId>" or "clickcell <cellId>")
                    int64_t mapId;
                    int32_t cellId;
                    if (sscanf_s(buffer, xorstr("autopilot %lld"), &mapId) == 1) {
                        if (dnmInstancePtr == nullptr) {
                            LOG_ERROR(xorstr("dnm instance pointer is null!"));
                        }
                        else {
                            app::dnm_rml(dnmInstancePtr, mapId, true, nullptr);
                        }
                    }
                    else if (sscanf_s(buffer, xorstr("clickcell %d"), &cellId) == 1) {
                        if (icmInstancePtr == nullptr) {
                            LOG_ERROR(xorstr("icm instance pointer is null!"));
                        }
                        else {
                            app::InteractiveCellManager_mnr(icmInstancePtr, cellId, nullptr);
                        }
                    }
                    else {
                        LOG(xorstr("Invalid command format!"));
                    }
                }

                DisconnectNamedPipe(hPipe);
            }
        }

        CloseHandle(hPipe);
        return 0;
    }
}