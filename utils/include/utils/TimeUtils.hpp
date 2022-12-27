#pragma once

#include <chrono>
#include <functional>

namespace utils::TimeUtils {

std::chrono::duration<std::chrono::seconds> calculateExecutionTime(std::function<std::string()>);

}
