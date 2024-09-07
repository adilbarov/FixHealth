#include <Windows.h>
#include <kthook/kthook.hpp>
#include "sampapi/CNetGame.h"
#include <RakHook/rakhook.hpp>
#include <RakNet/StringCompressor.h>

using CTimer__UpdateSignature = void(__cdecl*)();
kthook::kthook_simple<CTimer__UpdateSignature> CTimerHook{};
