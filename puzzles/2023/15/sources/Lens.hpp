#pragma once

#include "HashHelper.hpp"
#include <cstdint>
#include <string>
#include <string_view>

namespace aoc_2023_15 {

class Lens {
public:
    Lens(std::string_view label, uint8_t focalLength) noexcept;
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(Lens const& other) const noexcept;
    /**
     * @brief ???
     * @return ???
     */
    [[nodiscard]] std::string_view getLabel() const noexcept;
    /**
     * @brief ???
     * @return ???
     */
    [[nodiscard]] uint8_t getFocalLength() const noexcept;
    /**
     * @brief
     * @param value
     */
    void setFocalLength(uint8_t value) noexcept;

private:
    std::string mLabel;
    uint8_t mFocalLength;

    friend struct std::hash<Lens>;
};

} // namespace aoc_2023_15

template <>
struct std::hash<aoc_2023_15::Lens> {
    std::size_t operator()(aoc_2023_15::Lens const& lens) const noexcept
    {
        return std::hash<std::string>{}(lens.mLabel)
            ^ (std::hash<uint8_t>{}(lens.mFocalLength) << 1);
    }
};
