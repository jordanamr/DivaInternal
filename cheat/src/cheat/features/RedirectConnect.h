#pragma once
#include "Singleton.h"
#include "global.h"

namespace Cheat::Features
{
    class RedirectConnect : public Singleton<RedirectConnect>
    {
    public:
        RedirectConnect();

    private:
        static int WSAAPI ConnectHook(SOCKET s, const sockaddr* name, int namelen);
        inline static int (WSAAPI* RealConnect)(SOCKET, const sockaddr*, int) = connect;
    };
}
