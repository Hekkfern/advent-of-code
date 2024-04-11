#include "Lens.hpp"

#include "HashHelper.hpp"

namespace aoc_2023_15 {

Lens::Lens(std::string_view const label, uint8_t const focalLength) noexcept
    : mLabel{label}
    , mFocalLength{focalLength}
{
}

bool Lens::operator==(Lens const& other) const noexcept
{
    return mLabel == other.mLabel && mFocalLength == other.mFocalLength;
}

} // namespace aoc_2023_15
