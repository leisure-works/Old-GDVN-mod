#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "../../dtos/common/EmptyResponseDto.hpp"

using namespace geode::prelude;

class TournamentContestClient {
  public:
    using Callback = std::function<void(EmptyResponseDto const&, web::WebResponse&)>;

    static void getActiveLevel(int levelID, Callback callback);
    static void putProgress(int levelID, float progress, Callback callback);

  private:
    static std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> s_holders;
};
