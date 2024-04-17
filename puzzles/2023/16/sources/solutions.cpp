#include "solutions.hpp"

#include <unordered_map>
#include <utils/File.hpp>
#include <utils/cache/LRUCache.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>

namespace aoc_2023_16 {

// ---------- Private Methods ----------

enum class TileType {
    EmptySpace,
    MirrorSlash,
    MirrorBackslash,
    SplitterVertical,
    SplitterHorizontal
};

TileType convertToTileType(char const c)
{
    switch (c) {
    case '.':
    default:
        return TileType::EmptySpace;
    case '\\':
        return TileType::MirrorBackslash;
    case '/':
        return TileType::MirrorSlash;
    case '|':
        return TileType::SplitterVertical;
    case '-':
        return TileType::SplitterHorizontal;
    }
}
struct HashPair {
    template <class T1, class T2>
    std::size_t operator()(std::pair<T1, T2> const& p) const
    {
        auto hash1{std::hash<T1>{}(p.first)};
        auto hash2{std::hash<T2>{}(p.second)};

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

static std::unordered_map<
    std::pair<TileType, utils::geometry2d::Direction2D>,
    std::vector<utils::geometry2d::Direction2D>,
    HashPair> const BeamBehaviours{
    // EmptySpace
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Left}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Down}},
    // Mirror "/"
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Left}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Right}},
    // Mirror "\"
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Left}},
    // Horizontal splitter
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Left}},
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Left,
      utils::geometry2d::Direction2D::Right}},
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Left,
      utils::geometry2d::Direction2D::Right}},
    // Vertical splitter
    {{TileType::SplitterVertical, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Up,
      utils::geometry2d::Direction2D::Down}},
    {{TileType::SplitterVertical, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Up,
      utils::geometry2d::Direction2D::Down}},
    {{TileType::SplitterVertical, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::SplitterVertical, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Down}},
};

/**
 * @brief      Parses the whole input file and generates a flatten grid.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     Parsed data.
 */
utils::geometry2d::Grid2D<char>
parseInput(std::filesystem::path const& filePath)
{
    auto const data{*utils::file::readMatrixOfChars(filePath)};
    return utils::geometry2d::Grid2D<char>{data};
}

std::vector<utils::geometry2d::Direction2D> processPosition(
    utils::geometry2d::Grid2D<char> const& grid,
    utils::geometry2d::Coord2D<std::size_t> const& coords,
    utils::geometry2d::Direction2D const& inputDirection)
{
    auto const tileType{convertToTileType(grid.at(coords))};
    return BeamBehaviours.at(std::make_pair(tileType, inputDirection));
}

std::optional<utils::geometry2d::Coord2D<std::size_t>> moveInGrid(
    utils::geometry2d::Grid2D<char> const& grid,
    utils::geometry2d::Coord2D<std::size_t> const& coords,
    utils::geometry2d::Direction2D const& direction)
{
    auto const nextCoord{coords.move(direction)};
    if (!nextCoord
        || grid.where(*nextCoord)
            == utils::geometry2d::PositionStatus::Outside) {
        return {};
    }
    return *nextCoord;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const grid{parseInput(filePath)};

    return "1";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_16
