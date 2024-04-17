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

static std::unordered_map<
    std::pair<TileType, utils::geometry2d::Direction2D>,
    utils::geometry2d::Direction2D> const BeamBehaviours{
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Left},
     utils::geometry2d::Direction2D::Left},
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

std::vector<utils::geometry2d::Direction2D> processPositionWithMirror(
    TileType const tileType,
    utils::geometry2d::Direction2D const& inputDirection)
{
    switch (tileType) {
    case TileType::MirrorSlash:
        switch (inputDirection) {
        case utils::geometry2d::Direction2D::Up:
            return {utils::geometry2d::Direction2D::Right};
        case utils::geometry2d::Direction2D::Down:
            return {utils::geometry2d::Direction2D::Left};
        case utils::geometry2d::Direction2D::Left:
            return {utils::geometry2d::Direction2D::Down};
        case utils::geometry2d::Direction2D::Right:
            return {utils::geometry2d::Direction2D::Up};
        default:
            /* NO STATEMENTS */
            break;
        }
        break;
    case TileType::MirrorBackslash:
        switch (inputDirection) {
        case utils::geometry2d::Direction2D::Up:
            return {utils::geometry2d::Direction2D::Right};
        case utils::geometry2d::Direction2D::Down:
            return {utils::geometry2d::Direction2D::Left};
        case utils::geometry2d::Direction2D::Left:
            return {utils::geometry2d::Direction2D::Down};
        case utils::geometry2d::Direction2D::Right:
            return {utils::geometry2d::Direction2D::Up};
        default:
            /* NO STATEMENTS */
            break;
        }
        break;
    default:
        /* NO STATEMENTS */
        break;
    }
    return {};
}

std::vector<utils::geometry2d::Direction2D> processPositionWithSplitter(
    TileType const tileType,
    utils::geometry2d::Direction2D const& inputDirection)
{
    switch (tileType) {
    case TileType::SplitterHorizontal:
        switch (inputDirection) {
        case utils::geometry2d::Direction2D::Up:
        case utils::geometry2d::Direction2D::Down:
            return {
                utils::geometry2d::Direction2D::Left,
                utils::geometry2d::Direction2D::Right};
        case utils::geometry2d::Direction2D::Left:
            return {utils::geometry2d::Direction2D::Left};
        case utils::geometry2d::Direction2D::Right:
            return {utils::geometry2d::Direction2D::Right};
        default:
            /* NO STATEMENTS */
            break;
        }
        break;
    case TileType::SplitterVertical:
        switch (inputDirection) {
        case utils::geometry2d::Direction2D::Up:
            return {utils::geometry2d::Direction2D::Up};
        case utils::geometry2d::Direction2D::Down:
            return {utils::geometry2d::Direction2D::Down};
        case utils::geometry2d::Direction2D::Left:
        case utils::geometry2d::Direction2D::Right:
            return {
                utils::geometry2d::Direction2D::Down,
                utils::geometry2d::Direction2D::Up};
        default:
            /* NO STATEMENTS */
            break;
        }
        break;
    default:
        /* NO STATEMENTS */
        break;
    }

    return {};
}

std::vector<utils::geometry2d::Direction2D> processPosition(
    utils::geometry2d::Grid2D<char> const& grid,
    std::size_t const row,
    std::size_t const col,
    utils::geometry2d::Direction2D const& inputDirection)
{
    std::vector<utils::geometry2d::Direction2D> output;
    switch (auto const tileType{convertToTileType(grid.at(row, col))}) {
    case TileType::EmptySpace:
        output.push_back(inputDirection);
        break;
    case TileType::MirrorBackslash:
    case TileType::MirrorSlash:
        output = processPositionWithMirror(tileType, inputDirection);
        break;
    case TileType::SplitterVertical:
    case TileType::SplitterHorizontal:
        output = processPositionWithSplitter(tileType, inputDirection);
        break;
    }

    return output;
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
