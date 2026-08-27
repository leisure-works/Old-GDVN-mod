#include "LevelClient.hpp"

#include "../../adapters/ActivePvpMatchResponseAdapter.hpp"
#include "../../adapters/LevelInfoResponseAdapter.hpp"
#include "../../consts/ConfigConst.hpp"
#include <algorithm>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> LevelClient::s_getHolders;

void LevelClient::getLevel(int id, GetLevelCallback callback) {
    web::WebRequest req;
    auto token = gdvn::config::getToken();

    if (!token.empty()) {
        req.header("Authorization", "Bearer " + token);
    }

    auto url = gdvn::config::API_URL + "/lists/levels/" + std::to_string(id) + "/starred";

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    LevelClient::s_getHolders.push_back(holder);
    holder->spawn(req.get(url), [callback, holder](web::WebResponse res) {
        auto& holders = LevelClient::s_getHolders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        LevelInfoResponseDto dto;

        if (res.ok()) {
            auto jsonResult = res.json();
            if (jsonResult) {
                dto = LevelInfoResponseAdapter::fromJson(jsonResult.unwrap());
            }
        }

        callback(dto, res);
    });
}

void LevelClient::getActivePvpMatch(int levelID, GetActivePvpMatchCallback callback) {
    web::WebRequest req;
    std::string url = gdvn::config::API_URL + "/levels/" + std::to_string(levelID) + "/inPvp";

    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    LevelClient::s_getHolders.push_back(holder);
    holder->spawn(req.get(url), [callback, holder](web::WebResponse res) {
        auto& holders = LevelClient::s_getHolders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        ActivePvpMatchResponseDto dto;

        if (res.ok()) {
            auto jsonResult = res.json();
            if (jsonResult) {
                dto = ActivePvpMatchResponseAdapter::fromJson(jsonResult.unwrap());
            }
        }

        callback(dto, res);
    });
}
