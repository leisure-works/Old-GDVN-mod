#include "PvpChatButton.hpp"

#include "../../../services/pvp/PvpOverlayService.hpp"
#include <Geode/binding/ButtonSprite.hpp>

CCMenuItemSpriteExtra* PvpChatButton::create() {
    auto chatSprite = ButtonSprite::create("Chat", "goldFont.fnt", "GJ_button_01.png", 0.8f);
    chatSprite->setScale(0.55f);

    auto chatButton = CCMenuItemExt::createSpriteExtra(chatSprite, [=](auto*) {
        if (auto overlay = PvpOverlayService::getActive()) {
            overlay->openChat();
        }
    });
    chatButton->setID("gdvn-pvp-chat-button"_spr);
    return chatButton;
}
