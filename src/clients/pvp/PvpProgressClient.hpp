#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../../dtos/common/EmptyResponseDto.hpp"

using namespace geode::prelude;

class PvpProgressClient {
  public:
    using Callback = std::function<void(EmptyResponseDto const&, web::WebResponse&)>;

    static void postHeatmap(size_t count, Callback callback);
    static void postDeathCount(int levelID, std::string const& count, bool completed, Callback callback);

  private:
    static std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>> s_postHolders;
};
