#pragma once

#include <chrono>
#include <functional>
#include <string>

namespace utils::TimeUtils {

std::chrono::nanoseconds  calculateExecutionTime(std::function<std::string()>&& action);

}
