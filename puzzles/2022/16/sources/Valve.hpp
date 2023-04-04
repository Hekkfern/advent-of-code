#pragma once

#include <cstdint>
#include <string>

namespace aoc_2022_16 {

class Valve {
public:
    Valve(std::string_view name, uint32_t flowRate);
    bool isOpen() const;
    void open();
    uint32_t getFlowRate() const;
    const std::string& getName() const;
    bool operator==(const Valve& other) const;

private:
    std::string mName;
    uint32_t mFlowRate;
    bool mIsOpen{false};
};

} // namespace aoc_2022_16

template <>
struct std::hash<aoc_2022_16::Valve> {
    std::size_t operator()(const aoc_2022_16::Valve& k) const
    {
        return std::hash<std::string>()(k.getName());
    }
};
