#include "QolModAntiCheatService.hpp"

#include <Geode/Geode.hpp>

#include <array>
#include <string>

namespace {

bool isModuleEnabled(geode::Mod* mod, std::string const& id, bool defaultValue = false) {
    return mod->getSavedValue<bool>(id + "_enabled", defaultValue);
}

} // namespace

void QolModAntiCheatService::reset(PlayLayer*) {
}

void QolModAntiCheatService::onUpdate(float) {
}

bool QolModAntiCheatService::isCheated() const {
    auto mod = geode::Loader::get()->getLoadedMod("thesillydoggo.qolmod");

    if (!mod) {
        return false;
    }

    if (isModuleEnabled(mod, "safe-mode")) {
        return true;
    }

    bool disablesCheatsInUi = isModuleEnabled(mod, "safe-mode/disable-cheats-ui");

    static constexpr std::array levelLoadModules = {
        "force-plat",
        "accurate-spike-hitboxes",
        "show-triggers",
        "show-layout",
    };

    static constexpr std::array attemptModules = {
        "instant",
        "no-reverse",
        "instant-reverse",
        "no-static",
        "show-hitboxes",
        "coin-tracers",
        "show-trajectory",
        "rand-seed",
        "jump-hack",
        "tps-bypass",
        "auto-coins",
        "autoclicker",
        "auto-clicker",
        "frame-stepper",
        "hitbox-multiplier",
        "legacy-upside-down",
        "no-invisible-objects",
        "gravity-arrow",
        "hide-player",
        "show-player",
        "noclip",
    };

    if (!disablesCheatsInUi) {
        for (auto id : levelLoadModules) {
            if (isModuleEnabled(mod, id)) {
                return true;
            }
        }

        for (auto id : attemptModules) {
            if (isModuleEnabled(mod, id)) {
                return true;
            }
        }
    }

    return false;
}

std::string_view QolModAntiCheatService::getCheatReason() const {
    return "QOLMod config";
}
