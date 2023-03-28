#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <string_view>

namespace aoc_2022_16 {

class Valve {
public:
    static constexpr uint32_t TimeToOpenAValve{ 1U };
    static constexpr uint32_t TimeToMoveToNextValve{ 1U };

    Valve(std::string_view name, uint32_t flowRate, std::vector<std::string>&& neighbours);
    bool isOpen() const;
    void open();
    uint32_t getFlowRate() const;

private:
    std::string mName;
    uint32_t mFlowRate;
    std::vector<std::string> mNeighbourValves;
    bool mIsOpen{ false };
};

} // namespace aoc_2022_16
