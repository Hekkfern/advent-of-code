#pragma once

#include <chrono>
#include <functional>

namespace utils::TimeUtils {

std::chrono::milliseconds calculateExecutionTime(std::function<void()>&& action);

}
