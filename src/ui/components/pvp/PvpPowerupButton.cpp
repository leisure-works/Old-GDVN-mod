#include "PvpPowerupButton.hpp"

#include "../../../services/pvp/PvpOverlayService.hpp"
#include <Geode/binding/ButtonSprite.hpp>

CCMenuItemSpriteExtra* PvpPowerupButton::create() {
    auto skillSprite = ButtonSprite::create("Skills", "goldFont.fnt", "GJ_button_01.png", 0.8f);
    skillSprite->setScale(0.55f);

    auto skillButton = CCMenuItemExt::createSpriteExtra(skillSprite, [=](auto*) {
        if (auto overlay = PvpOverlayService::getActive()) {
            overlay->openPowerups();
        }
    });
    skillButton->setID("gdvn-pvp-powerup-button"_spr);
    return skillButton;
}
