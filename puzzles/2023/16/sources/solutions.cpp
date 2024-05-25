#include "solutions.hpp"

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <utils/File.hpp>
#include <utils/Hash.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>
#include <vector>

namespace aoc_2023_16 {

// ---------- Private Methods ----------

enum class TileType {
    EmptySpace,
    MirrorSlash,
    MirrorBackslash,
    SplitterVertical,
    SplitterHorizontal
};

/**
 * @brief      Converts the character of a tile to its corresponding enum value.
 *
 * @param[in]  c     Character to analyse.
 *
 * @return     The tile type.
 */
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

/**
 * @brief      Map defining how an input beam behaves for each one of the
 *             existing tile types.
 */
static std::unordered_map<
    std::pair<TileType, utils::geometry2d::Direction2D>,
    std::vector<utils::geometry2d::Direction2D>> const BeamBehaviours{
    // EmptySpace
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Left}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::EmptySpace, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Up}},
    // Mirror "/"
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Left}},
    {{TileType::MirrorSlash, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Right}},
    // Mirror "\"
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Up}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::MirrorBackslash, utils::geometry2d::Direction2D::Up},
     {utils::geometry2d::Direction2D::Left}},
    // Horizontal splitter
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Left},
     {utils::geometry2d::Direction2D::Right}},
    {{TileType::SplitterHorizontal, utils::geometry2d::Direction2D::Right},
     {utils::geometry2d::Direction2D::Left}},
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
     {utils::geometry2d::Direction2D::Down}},
    {{TileType::SplitterVertical, utils::geometry2d::Direction2D::Down},
     {utils::geometry2d::Direction2D::Up}},
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

/**
 * @brief      Given a position in the grid, reads the type of beam modifier in
 *             it and returns the directions of the output beams.
 *
 * @param[in]  grid            The grid
 * @param[in]  coords          The coordinates of the tile
 * @param[in]  inputDirection  The input direction
 *
 * @return     One or more output beams.
 */
std::vector<utils::geometry2d::Direction2D> processPosition(
    utils::geometry2d::Grid2D<char> const& grid,
    utils::geometry2d::Coordinate2D<std::size_t> const& coords,
    utils::geometry2d::Direction2D const& inputDirection)
{
    auto const tileType{convertToTileType(grid.at(coords))};
    return BeamBehaviours.at(std::make_pair(tileType, inputDirection));
}

/**
 * @brief      Returns the new position after moving the selected tile one
 *             position in the selected direction.
 *
 * @param      grid       The grid
 * @param      coords     The coordinates of the tile
 * @param      direction  The direction of movement
 *
 * @return     New position after moving, or std::nullopt otherwise.
 */
std::optional<utils::geometry2d::Coordinate2D<std::size_t>> moveAround(
    utils::geometry2d::Grid2D<char> const& grid,
    utils::geometry2d::Coordinate2D<std::size_t> const& coords,
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

using AnalyzedBeamList = std::unordered_set<std::pair<
    utils::geometry2d::Coordinate2D<std::size_t>,
    utils::geometry2d::Direction2D>>;

/**
 * @brief      Recursively analyses all the tiles in the path of the beam.
 *
 * @param      grid       The grid
 * @param      coords     The coordinates
 * @param      direction  The direction
 * @param      cache      The cache
 */
void processRecursiveForPart1(
    utils::geometry2d::Grid2D<char> const& grid,
    utils::geometry2d::Coordinate2D<std::size_t> const& coords,
    utils::geometry2d::Direction2D const& direction,
    std::unordered_set<utils::geometry2d::Coordinate2D<std::size_t>>&
        energizedTiles,
    AnalyzedBeamList& analyzedBeamList)
{
    auto const outputBeams{processPosition(grid, coords, direction)};
    for (auto const outputBeam : outputBeams) {
        auto const moveResult{moveAround(grid, coords, outputBeam)};
        if (!moveResult) {
            continue;
        }
        if (!analyzedBeamList.contains(
                std::make_pair(*moveResult, outputBeam))) {
            energizedTiles.emplace(*moveResult);
            analyzedBeamList.emplace(std::make_pair(*moveResult, outputBeam));
            processRecursiveForPart1(
                grid,
                *moveResult,
                outputBeam.invert(),
                energizedTiles,
                analyzedBeamList);
        }
    }
}

std::vector<std::pair<
    utils::geometry2d::Coordinate2D<std::size_t>,
    utils::geometry2d::Direction2D>>
getListOfStartingBeams(utils::geometry2d::Grid2D<char> const& grid)
{
    std::vector<std::pair<
        utils::geometry2d::Coordinate2D<std::size_t>,
        utils::geometry2d::Direction2D>>
        list;

    /* left */
    for (std::size_t i{0ULL}; i < grid.getHeight(); ++i) {
        list.emplace_back(
            utils::geometry2d::Coordinate2D<std::size_t>{0ULL, i},
            utils::geometry2d::Direction2D::Left);
    }
    /* down */
    for (std::size_t i{0ULL}; i < grid.getWidth(); ++i) {
        list.emplace_back(
            utils::geometry2d::Coordinate2D<std::size_t>{
                i, grid.getHeight() - 1ULL},
            utils::geometry2d::Direction2D::Up);
    }
    /* right */
    for (std::size_t i{0ULL}; i < grid.getHeight(); ++i) {
        list.emplace_back(
            utils::geometry2d::Coordinate2D<std::size_t>{
                grid.getWidth() - 1ULL, i},
            utils::geometry2d::Direction2D::Right);
    }
    /* up */
    for (std::size_t i{0ULL}; i < grid.getWidth(); ++i) {
        list.emplace_back(
            utils::geometry2d::Coordinate2D<std::size_t>{i, 0ULL},
            utils::geometry2d::Direction2D::Down);
    }

    return list;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const grid{parseInput(filePath)};
    utils::geometry2d::Coordinate2D<std::size_t> initialCoords{0, 0};
    utils::geometry2d::Direction2D initialDirection{
        utils::geometry2d::Direction2D::Left};
    AnalyzedBeamList analyzedBeamList{{initialCoords, initialDirection}};
    std::unordered_set<utils::geometry2d::Coordinate2D<std::size_t>>
        energizedTiles{initialCoords};
    processRecursiveForPart1(
        grid,
        initialCoords,
        initialDirection,
        energizedTiles,
        analyzedBeamList);
    return std::to_string(energizedTiles.size());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const grid{parseInput(filePath)};
    uint64_t maxNumber{0};
    for (auto const& startingBeam : getListOfStartingBeams(grid)) {
        // TODO
        AnalyzedBeamList analyzedBeamList{{initialCoords, initialDirection}};
    }
    return std::to_string(maxNumber);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_16
