#define _WINSOCK_DEPRECATED_NO_WARNINGS  // Ignore deprecation warnings

#include "RedirectConnect.h"
#include "HookManager.h"
#include "Utils.h"
#include <detours.h>
#include <iostream>
#include <windows.h>  // For GetTempPathA
#include <fstream>    // For file writing (ofstream)
#include <string>     // For easier string manipulation (optional but helpful)
#include <vector>     // For GetTempPathA buffer (safer alternative)

namespace Cheat::Features
{
    RedirectConnect::RedirectConnect()
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)RealConnect, ConnectHook);

        if (DetourTransactionCommit() != NO_ERROR)
        {
            LOG_ERROR(xorstr("Error: Failed to install hook!"));
        }
    }

    int WSAAPI RedirectConnect::ConnectHook(SOCKET s, const sockaddr* name, int namelen)
    {
        if (!RealConnect) {
            LOG_ERROR(xorstr("Error: RealConnect is NULL!"));
            return SOCKET_ERROR;
        }

        auto& vars = Vars::GetInstance();
        if (!vars.RedirectConnect.value()) {
            return RealConnect(s, name, namelen);
        }

        std::string address = vars.RedirectConnectAddress.value();

        size_t pos = address.find(':');
        if (pos == std::string::npos) {
            LOG_ERROR(xorstr("Invalid format: No ':' found in string"));
            return SOCKET_ERROR;
        }

        std::string ip = address.substr(0, pos);
        unsigned short newPort = static_cast<unsigned short>(std::stoi(address.substr(pos + 1)));

        char ipStr[INET6_ADDRSTRLEN] = { 0 };
        int origPort = 0;

        if (name->sa_family == AF_INET) {
            struct sockaddr_in copyAddr = *reinterpret_cast<const sockaddr_in*>(name);
            inet_ntop(AF_INET, &copyAddr.sin_addr, ipStr, sizeof(ipStr));
            origPort = ntohs(copyAddr.sin_port);

            if (origPort == 5555) {
                copyAddr.sin_addr.s_addr = inet_addr(ip.c_str());
                copyAddr.sin_port = htons(newPort);
                return RealConnect(s, (sockaddr*)&copyAddr, namelen);
            }
        }
        else if (name->sa_family == AF_INET6) {
            struct sockaddr_in6 copyAddr = *reinterpret_cast<const sockaddr_in6*>(name);
            inet_ntop(AF_INET6, &copyAddr.sin6_addr, ipStr, sizeof(ipStr));
            origPort = ntohs(copyAddr.sin6_port);

            if (origPort == 5555 && strncmp(ipStr, "::ffff:", 7) == 0) {
                struct in_addr newAddr;
                newAddr.s_addr = inet_addr(ip.c_str());
                const char* ipv4Part = ipStr + 7;

                // 3. Save the stripped IP to a temp file
                try
                {
                    // Define the filename (adjust "d3_mapped_ip.txt" if needed)
                    const char* fileName = "mapped_ip.txt";

                    // Get the temp path
                    char tempPath[MAX_PATH];
                    DWORD pathLen = GetTempPathA(MAX_PATH, tempPath);

                    if (pathLen > 0 && pathLen < MAX_PATH)
                    {
                        // Combine path and filename
                        std::string fullPath = std::string(tempPath) + fileName;

                        // Open the file and write the IP
                        std::ofstream outfile(fullPath);
                        if (outfile.is_open())
                        {
                            outfile << ipv4Part; // Write only the IP
                            outfile.close();
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        LOG_ERROR(xorstr("Failed to get temporary path."));
                    }
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR(xorstr("Exception while saving IP: %s"), e.what());
                }
                catch (...)
                {
                    LOG_ERROR(xorstr("Unknown exception while saving IP."));
                }


                memset(&copyAddr.sin6_addr, 0, sizeof(copyAddr.sin6_addr));
                copyAddr.sin6_addr.s6_addr[10] = 0xFF;
                copyAddr.sin6_addr.s6_addr[11] = 0xFF;
                memcpy(&copyAddr.sin6_addr.s6_addr[12], &newAddr.s_addr, sizeof(newAddr.s_addr));

                copyAddr.sin6_port = htons(newPort);
                return RealConnect(s, (sockaddr*)&copyAddr, namelen);
            }
        }

        return RealConnect(s, name, namelen);
    }
}
