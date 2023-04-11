#pragma once

#include <chrono>
#include <functional>

namespace utils::time {

/**
 * @brief      Calculates the execution time of the provided action.
 *
 * @param      action  The action.
 *
 * @return     The execution time, expressed in microseconds.
 */
[[nodiscard]] std::chrono::microseconds calculateExecutionTime(
    std::function<void()>&& action);

}
