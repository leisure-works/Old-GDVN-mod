#include "TournamentContestSubmitterService.hpp"

#include "../../clients/tournament/TournamentContestClient.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

TournamentContestSubmitterService::TournamentContestSubmitterService()
    : m_state(std::make_shared<State>()) {
}

TournamentContestSubmitterService::~TournamentContestSubmitterService() = default;

TournamentContestSubmitterService::TournamentContestSubmitterService(int levelID)
    : m_state(std::make_shared<State>(levelID)) {
    std::weak_ptr<State> state = m_state;
    TournamentContestClient::getActiveLevel(
        levelID, [state](EmptyResponseDto const&, web::WebResponse& res) {
            if (auto locked = state.lock()) {
                locked->active.store(res.ok());

                if (res.ok() && locked->best > 0) {
                    TournamentContestClient::putProgress(
                        locked->levelID, locked->best,
                        [](EmptyResponseDto const&, web::WebResponse&) {});
                }
            }
        });
}

void TournamentContestSubmitterService::submit() {
    if (!m_state || !m_state->active.load()) {
        return;
    }

    TournamentContestClient::putProgress(
        m_state->levelID, m_state->best,
        [](EmptyResponseDto const&, web::WebResponse& res) {
            if (!res.ok()) {
                log::warn("Failed to submit tournament contest progress: HTTP {}", res.code());
            }
        });
}

void TournamentContestSubmitterService::record(float progress) {
    if (!m_state || progress <= m_state->best) {
        return;
    }

    m_state->best = progress;
    submit();
}
