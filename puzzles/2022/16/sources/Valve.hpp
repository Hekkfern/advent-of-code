#pragma once

#include <cstdint>
#include <string>

namespace aoc_2022_16 {

class Valve {
public:
    Valve(std::string_view name, uint32_t flowRate);
    uint32_t getFlowRate() const;
    std::string const& getName() const;
    bool operator==(Valve const& other) const;

private:
    std::string mName;
    uint32_t mFlowRate;
};

} // namespace aoc_2022_16

template <>
struct std::hash<aoc_2022_16::Valve> {
    std::size_t operator()(aoc_2022_16::Valve const& k) const
    {
        return std::hash<std::string>()(k.getName());
    }
};
