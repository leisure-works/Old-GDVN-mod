#include <Geode/Geode.hpp>
#include <Geode/binding/CCMenuItemToggler.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/modify/PauseLayer.hpp> // DO NOT REMOVE

#include "../services/pvp/PvpOverlayService.hpp"
#include "../ui/components/pvp/PvpChatButton.hpp"
#include "../ui/components/pvp/PvpPowerupButton.hpp"

using namespace geode::prelude;

namespace {
constexpr float MUTE_CHAT_TOGGLE_SCALE = 0.65f;
constexpr float MUTE_CHAT_LABEL_SCALE = 0.32f;
constexpr float MUTE_CHAT_LABEL_GAP = 6.0f;
} // namespace

$on_mod(Loaded) {
    listenForKeybindSettingPresses("open-pvp-chat", [=](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) {
            return false;
        }

        auto overlay = PvpOverlayService::getActive();
        return overlay && overlay->openChat();
    });
}

class $modify(GDVNPauseLayer, PauseLayer) {
    void customSetup() override {
        PauseLayer::customSetup();

        auto overlay = PvpOverlayService::getActive();
        if (!overlay || !overlay->hasPvpMatch()) {
            return;
        }

        auto menu = typeinfo_cast<CCMenu*>(this->getChildByIDRecursive("right-button-menu"));
        if (!menu) {
            log::warn("Could not find PauseLayer right-button-menu for GDVN controls");
            return;
        }

        if (overlay->isPowerupMode()) {
            menu->addChild(PvpPowerupButton::create());
        }

        menu->addChild(PvpChatButton::create());

        auto muteToggle = CCMenuItemToggler::createWithStandardSprites(
            this, menu_selector(GDVNPauseLayer::onGDVNMuteChat), MUTE_CHAT_TOGGLE_SCALE);
        muteToggle->setID("gdvn-pvp-mute-chat-toggle"_spr);
        muteToggle->toggle(overlay->isChatMuted());

        auto muteLabel = CCLabelBMFont::create("Mute Chat", "bigFont.fnt");
        muteLabel->setID("gdvn-pvp-mute-chat-label"_spr);
        muteLabel->setScale(MUTE_CHAT_LABEL_SCALE);
        muteLabel->setAnchorPoint({1.0f, 0.5f});
        muteLabel->setPosition({-MUTE_CHAT_LABEL_GAP, muteToggle->getContentSize().height / 2.0f});
        muteToggle->addChild(muteLabel);

        menu->addChild(muteToggle);

        menu->updateLayout();
    }

    void onGDVNMuteChat(CCObject*) {
        auto overlay = PvpOverlayService::getActive();
        if (!overlay) {
            auto muted = !Mod::get()->getSavedValue<bool>("pvp-chat-muted", false);
            Mod::get()->setSavedValue<bool>("pvp-chat-muted", muted);
            return;
        }

        overlay->setChatMuted(!overlay->isChatMuted());
    }
};
