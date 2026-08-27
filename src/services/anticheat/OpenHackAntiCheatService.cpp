#include "OpenHackAntiCheatService.hpp"

#include <Geode/Geode.hpp>

#ifdef GEODE_IS_WINDOWS
#include <Geode/platform/windows.hpp>
#endif

void OpenHackAntiCheatService::reset(PlayLayer*) {
}

void OpenHackAntiCheatService::onUpdate(float) {
}

bool OpenHackAntiCheatService::isCheated() const {
    if (!geode::Loader::get()->getLoadedMod("prevter.openhack")) {
        return false;
    }

#ifdef GEODE_IS_WINDOWS
    auto library = GetModuleHandleA("prevter.openhack.dll");
    if (!library) {
        return false;
    }

    using IsCheating = bool (*)();
    auto isCheating = reinterpret_cast<IsCheating>(GetProcAddress(library, "?isCheating@openhack@@YA_NXZ"));
    return isCheating && isCheating();
#else
    return false;
#endif
}

std::string_view OpenHackAntiCheatService::getCheatReason() const {
    return "OpenHack runtime state";
}
