#pragma once

#include <atomic>
#include <memory>

class TournamentContestSubmitterService {
    struct State {
        int levelID = 0;
        float best = 0;
        std::atomic<bool> active{false};

        explicit State(int levelID = 0) : levelID(levelID) {
        }
    };

    std::shared_ptr<State> m_state;

    void submit();

  public:
    TournamentContestSubmitterService();
    ~TournamentContestSubmitterService();
    explicit TournamentContestSubmitterService(int levelID);

    void record(float progress);
};
