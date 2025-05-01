#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

#include "appdata/helpers.h"
#include "magic_enum.hpp"
#include "cheat/vars.h"

#include "events/event.hpp"
#include "events/handlers/methodeventhandler.hpp"
#include "events/handlers/functoreventhandler.hpp"
#include "events/joins/handlereventjoin.hpp"
#include "events/joins/eventjoinwrapper.hpp"

#include "methods/Assembly-CSharp.hpp"
#include "methods/mscorlib.hpp"
#include "methods/UnityEngine.CoreModule.hpp"

#include "appdata/Il2CppHelper.h"