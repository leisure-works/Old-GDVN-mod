#include "EventClient.hpp"

#include "../../consts/ConfigConst.hpp"
#include <algorithm>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> EventClient::s_holders;

void EventClient::getEventLevel(int levelID, std::string const& type, Callback callback) {
    web::WebRequest req;
    std::string url = gdvn::config::API_URL + "/levels/" + std::to_string(levelID) + "/inEvent";

    if (!type.empty()) {
        url += "?type=" + type;
    }

    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    EventClient::s_holders.push_back(holder);
    holder->spawn(req.get(url), [callback, holder](web::WebResponse res) {
        auto& holders = EventClient::s_holders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}

void EventClient::putLevel(int levelID, float progress, Callback callback) {
    web::WebRequest req;
    std::string url = gdvn::config::API_URL + "/events/submitLevel/" + std::to_string(levelID) +
                      "?progress=" + std::to_string(progress) + "&password=" + gdvn::config::EVENT_PASSWORD;

    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    EventClient::s_holders.push_back(holder);
    holder->spawn(req.put(url), [callback, holder](web::WebResponse res) {
        auto& holders = EventClient::s_holders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}
