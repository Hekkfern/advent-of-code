#include "solutions.hpp"

#include <fstream>
#include <limits>
#include <vector>

namespace aoc_2022_8 {

using Height = uint8_t;
using TreeHeightMatrix = std::vector<std::vector<Height>>;
using TreeHeightLine = std::vector<Height>;
using TreeVisibilityMatrix = std::vector<std::vector<bool>>;
using TreeVisibilityLine = std::vector<bool>;

// ---------- Private Methods ----------

/**
 * @brief      Parses the input data file and generates a 2D matrix with the
 *             height values.
 *
 * @param[in]  filename  Path and name of the file where retrieve the input data
 *                       from.
 *
 * @return     A 2D matrix of tree heights.
 */
TreeHeightMatrix parseInput(const std::string& filename)
{
    std::ifstream inputFile{ filename };
    TreeHeightMatrix heightMatrix;
    std::string line;

    while (std::getline(inputFile, line)) {
        TreeHeightLine heightRow;
        heightRow.reserve(line.size());
        for (const char c : line) {
            heightRow.emplace_back(c - '0');
        }
        heightMatrix.push_back(std::move(heightRow));
    }

    return heightMatrix;
}

/**
 * @brief      Loops over all the forest from the top-left corner to the
 *             bottom-right corner, checking the visibility rules of the trees.
 *
 * @param[in]  forest      The 2D matrix of tree heights.
 * @param[in]  visibility  The 2D matrix of the visible trees from outside the
 *                         forest.
 *
 * @return     The number of newly-detected visible trees from outside the
 *             forest.
 */
uint32_t checkTreeVisibilityFromTopLeft(
    TreeHeightMatrix& forest,
    TreeVisibilityMatrix& visibility)
{
    uint32_t count = 0U;
    TreeHeightLine maxValueInRow(forest.size());
    TreeHeightLine maxValueInColumn(forest[0].size());

    for (uint32_t i = 0U; i < forest.size(); ++i) {
        for (uint32_t j = 0U; j < forest[0].size(); ++j) {
            if ((i == 0) || (j == 0) || (forest[i][j] > maxValueInRow[i])
                || (forest[i][j] > maxValueInColumn[j])) {
                if (!visibility[i][j]) {
                    visibility[i][j] = true;
                    ++count;
                }
            }
            maxValueInRow[i] = std::max(maxValueInRow[i], forest[i][j]);
            maxValueInColumn[j] = std::max(maxValueInColumn[j], forest[i][j]);
        }
    }

    return count;
}

/**
 * @brief      Loops over all the forest from the bottom-right corner to the
 *             top-left corner, checking the visibility rules of the trees.
 *
 * @param[in]  forest      The 2D matrix of tree heights.
 * @param[in]  visibility  The 2D matrix of the visible trees from outside the
 *                         forest.
 *
 * @return     The number of newly-detected visible trees from outside the
 *             forest.
 */
uint32_t checkTreeVisibilityFromBottomRight(
    TreeHeightMatrix& forest,
    TreeVisibilityMatrix& visibility)
{
    uint32_t count = 0U;
    TreeHeightLine maxValueInRow(forest.size());
    TreeHeightLine maxValueInColumn(forest[0].size());
    const uint32_t lastRowIndex{ static_cast<uint32_t>(forest.size()) - 1U };
    const uint32_t lastColumnIndex{ static_cast<uint32_t>(forest[0].size())
                                    - 1U };

    for (uint32_t i = lastRowIndex; i != std::numeric_limits<uint32_t>::max();
         --i) {
        for (uint32_t j = lastColumnIndex;
             j != std::numeric_limits<uint32_t>::max();
             --j) {
            if ((i == lastRowIndex) || (j == lastColumnIndex)
                || (forest[i][j] > maxValueInRow[i])
                || (forest[i][j] > maxValueInColumn[j])) {
                if (!visibility[i][j]) {
                    visibility[i][j] = true;
                    ++count;
                }
            }
            maxValueInRow[i] = std::max(maxValueInRow[i], forest[i][j]);
            maxValueInColumn[j] = std::max(maxValueInColumn[j], forest[i][j]);
        }
    }

    return count;
}

/**
 * @brief      Checks all the trees in the forest and counts how many trees are
 *             visible from outside the forest.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 *
 * @return     Number of trees visible from outside the forest.
 */
uint32_t checkTreeVisibility(TreeHeightMatrix& forest)
{
    TreeVisibilityMatrix visibility(
        forest.size(), TreeVisibilityLine(forest[0].size()));
    uint32_t count = 0U;
    count += checkTreeVisibilityFromTopLeft(forest, visibility);
    count += checkTreeVisibilityFromBottomRight(forest, visibility);
    return count;
}

/**
 * @brief      Calculates the number of trees which can be seen to the left of
 *             the selected tree.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 * @param[in]  row     Index of the row of the selected tree.
 * @param[in]  column  Index of the column of the selected tree.
 *
 * @return     Number of trees which can be seen to the left of the selected
 *             tree.
 */
uint32_t
calculateLeftView(const TreeHeightMatrix& forest, uint32_t row, uint32_t column)
{
    uint32_t visibleTress = 0U;
    if (column > 0) {
        for (uint32_t j = column - 1U;
             j != std::numeric_limits<uint32_t>::max();
             --j) {
            ++visibleTress;
            if (forest[row][j] >= forest[row][column]) {
                break;
            }
        }
    }
    return visibleTress;
}

/**
 * @brief      Calculates the number of trees which can be seen to the right of
 *             the selected tree.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 * @param[in]  row     Index of the row of the selected tree.
 * @param[in]  column  Index of the column of the selected tree.
 *
 * @return     Number of trees which can be seen to the right of the selected
 *             tree.
 */
uint32_t calculateRightView(
    const TreeHeightMatrix& forest,
    uint32_t row,
    uint32_t column)
{
    const uint32_t forestColumns{ static_cast<uint32_t>(forest[0].size()) };
    uint32_t visibleTress = 0U;
    if (column < (forestColumns - 1U)) {
        for (uint32_t j = column + 1U; j < forestColumns; ++j) {
            ++visibleTress;
            if (forest[row][j] >= forest[row][column]) {
                break;
            }
        }
    }
    return visibleTress;
}

/**
 * @brief      Calculates the number of trees which can be seen above the
 *             selected tree.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 * @param[in]  row     Index of the row of the selected tree.
 * @param[in]  column  Index of the column of the selected tree.
 *
 * @return     Number of trees which can be seen above the selected tree.
 */
uint32_t
calculateUpView(const TreeHeightMatrix& forest, uint32_t row, uint32_t column)
{
    uint32_t visibleTress = 0U;
    if (row > 0) {
        for (uint32_t i = row - 1U; i != std::numeric_limits<uint32_t>::max();
             --i) {
            ++visibleTress;
            if (forest[i][column] >= forest[row][column]) {
                break;
            }
        }
    }
    return visibleTress;
}

/**
 * @brief      Calculates the number of trees which can be seen below the
 *             selected tree.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 * @param[in]  row     Index of the row of the selected tree.
 * @param[in]  column  Index of the column of the selected tree.
 *
 * @return     Number of trees which can be seen below the selected tree.
 */
uint32_t
calculateDownView(const TreeHeightMatrix& forest, uint32_t row, uint32_t column)
{
    const uint32_t forestRows{ static_cast<uint32_t>(forest.size()) };
    uint32_t visibleTress = 0U;
    if (row < (forestRows - 1U)) {
        for (uint32_t i = row + 1U; i < forestRows; ++i) {
            ++visibleTress;
            if (forest[i][column] >= forest[row][column]) {
                break;
            }
        }
    }
    return visibleTress;
}

/**
 * @brief      Calculates the scenic score of the selected tree.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 * @param[in]  row     Index of the row of the selected tree.
 * @param[in]  column  Index of the column of the selected tree.
 *
 * @return     The scenic score of the selected tree.
 */
uint32_t calculateScenicScore(
    const TreeHeightMatrix& forest,
    uint32_t row,
    uint32_t column)
{
    const uint32_t visibleTreesLeft = calculateLeftView(forest, row, column);
    const uint32_t visibleTreesRight = calculateRightView(forest, row, column);
    const uint32_t visibleTreesUp = calculateUpView(forest, row, column);
    const uint32_t visibleTreesDown = calculateDownView(forest, row, column);
    return visibleTreesLeft * visibleTreesRight * visibleTreesUp
        * visibleTreesDown;
}

/**
 * @brief      Calculates the maximum scenic score of the whole forest.
 *
 * @param[in]  forest  The 2D matrix of tree heights.
 *
 * @return     The maximum scenic score.
 */
uint32_t calculateMaximumScenicScore(const TreeHeightMatrix& forest)
{
    uint32_t maxScenicScore = 0U;
    for (uint32_t i = 0U; i < forest.size(); ++i) {
        for (uint32_t j = 0U; j < forest[0].size(); ++j) {
            maxScenicScore = std::max(
                maxScenicScore, calculateScenicScore(forest, i, j));
        }
    }
    return maxScenicScore;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    auto forest{ parseInput(filename) };

    return std::to_string(checkTreeVisibility(forest));
}

std::string solvePart2(const std::string& filename)
{
    auto forest{ parseInput(filename) };

    return std::to_string(calculateMaximumScenicScore(forest));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_8
