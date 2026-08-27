#include "TournamentContestClient.hpp"

#include "../../consts/ConfigConst.hpp"
#include <algorithm>

std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> TournamentContestClient::s_holders;

void TournamentContestClient::getActiveLevel(int levelID, Callback callback) {
    web::WebRequest req;
    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    const auto url =
        gdvn::config::API_URL + "/tournaments/contest/levels/" + std::to_string(levelID);
    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    s_holders.push_back(holder);
    holder->spawn(req.get(url), [callback, holder](web::WebResponse res) {
        auto& holders = TournamentContestClient::s_holders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}

void TournamentContestClient::putProgress(int levelID, float progress, Callback callback) {
    web::WebRequest req;
    req.header("Authorization", "Bearer " + gdvn::config::getToken());

    const auto url = gdvn::config::API_URL + "/tournaments/contest/levels/" + std::to_string(levelID) +
                     "?progress=" + std::to_string(progress);
    auto holder = std::make_shared<async::TaskHolder<web::WebResponse>>();
    s_holders.push_back(holder);
    holder->spawn(req.put(url), [callback, holder](web::WebResponse res) {
        auto& holders = TournamentContestClient::s_holders;
        holders.erase(std::remove(holders.begin(), holders.end(), holder), holders.end());

        EmptyResponseDto dto;
        callback(dto, res);
    });
}
