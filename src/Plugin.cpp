#include "Plugin.h"
#include <RakHook/rakhook.hpp>
#include <RakNet/StringCompressor.h>

Plugin::Plugin(HMODULE hndl) : hModule(hndl) {
    using namespace std::placeholders;
    hookCTimerUpdate.set_cb(std::bind(&Plugin::mainloop, this, _1));
    hookCTimerUpdate.install();
}

void Plugin::mainloop(const decltype(hookCTimerUpdate)& hook) {
    static bool inited = false;
    if (!inited && rakhook::initialize()) {
        StringCompressor::AddReference();
        
        rakhook::on_receive_rpc += [](unsigned char &id, RakNet::BitStream *bs) -> bool {
            if (id == 14)
            {
                float health;
                bs->Read(health);

                health = float(int(health) % 256);

                bs->Reset();
                bs->Write(health);

                return true;
            }
            return true;
        };

        inited = true;
    }
    return hook.get_trampoline()();
}
