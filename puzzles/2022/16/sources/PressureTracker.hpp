#pragma once

#include <cstdint>

namespace aoc_2022_16 {

class PressureTracker {
public:
    /**
     * @param[in] time From 0
     */
    void openValve(uint32_t flowRate, uint32_t time);
    uint32_t getReleasedPressure() const;
    bool operator==(const PressureTracker& other) const;
    bool operator<(const PressureTracker& other) const;

private:
    uint32_t mReleasedPressure{ 0U };
};

} // namespace aoc_2022_16
