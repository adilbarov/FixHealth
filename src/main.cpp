#include "main.h"

void CTimer__Update(const decltype(CTimerHook)& hook) {
    static bool init{};
    if (!init && samp::RefNetGame() && rakhook::initialize()) {

        StringCompressor::AddReference();

        rakhook::on_receive_rpc += [](unsigned char &id, RakNet::BitStream *bs) -> bool {
            if (id == 14)
            {
                float health;
                bs->Read(health);

                health = float(int(health) % 256);

                if (health == 0.0f)
                    health = 0.1f;

                bs->Reset();
                bs->Write(health);

                return true;
            }
            return true;
        };

        init = { true };
    }

    hook.get_trampoline()();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CTimerHook.set_dest(0x561B10);
        CTimerHook.set_cb(&CTimer__Update);
        CTimerHook.install();
        break;
    case DLL_PROCESS_DETACH:
        CTimerHook.remove();
        break;
    }
    return TRUE;
}