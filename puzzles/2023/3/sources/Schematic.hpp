#pragma once

#include <cstdint>
#include <utils/geometry2d/Line2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2023_3 {

struct Part {
    uint32_t partNumber{0U};
    utils::geometry2d::Line2D<> line;

    Part(uint32_t pn, utils::geometry2d::Line2D<> const& line);
};

struct Symbol {
    char character{0};
    utils::geometry2d::Point2D<> position;

    Symbol(char c, utils::geometry2d::Point2D<> const& pos);

    bool operator==(Symbol const& rhs) const;
};

struct Schematic {
    std::vector<Part> parts{};
    std::vector<Symbol> symbols{};

    Schematic() = default;

    void merge(Schematic&& other) noexcept;
};

} // namespace aoc_2023_3
