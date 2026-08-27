#include "PvpProgressClient.hpp"

#include "../../consts/ConfigConst.hpp"
#include <algorithm>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> PvpProgressClient::s_postHolders;

void PvpProgressClient::postHeatmap(size_t count, Callback callback) {
    web::WebRequest req;
    std::string url = gdvn::config::API_URL + "/players/heatmap/" + std::to_string(count);

    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    PvpProgressClient::s_postHolders.push_back(holder);
    holder->spawn(req.post(url), [callback, holder](web::WebResponse res) {
        auto& holders = PvpProgressClient::s_postHolders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}

void PvpProgressClient::postDeathCount(int levelID, std::string const& count, bool completed, Callback callback) {
    web::WebRequest req;
    std::string url = gdvn::config::API_URL + "/deathCount/" + std::to_string(levelID) + "/" + count;

    if (completed) {
        url += "?completed";
    }

    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    PvpProgressClient::s_postHolders.push_back(holder);
    holder->spawn(req.post(url), [callback, holder](web::WebResponse res) {
        auto& holders = PvpProgressClient::s_postHolders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}
