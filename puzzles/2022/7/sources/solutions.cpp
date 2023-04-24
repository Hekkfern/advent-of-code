#include "solutions.hpp"

#include "Directory.h"
#include "DirectoryTree.h"
#include <fstream>
#include <functional>
#include <range/v3/all.hpp>
#include <sstream>

namespace aoc_2022_7 {

// ---------- Private constants ----------

constexpr auto StartCommandChar{'$'};
constexpr auto CdCommand{"cd"};
constexpr auto LsCommand{"ls"};

// ---------- End of Private constants ----------

// ---------- Private Methods ----------

/**
 * @brief
 *
 * @param[in,out] currentDir
 * @param[in] destinationDir
 */
void executeCdCommand(DirectoryTree& tree, std::string_view destinationDir)
{
    tree.changeDirectory(destinationDir);
}

/**
 * @brief
 *
 * @param[in,out] currentDir
 * @param[in] fileStream
 */
void executeLsCommand(DirectoryTree& tree, std::ifstream& fileStream)
{
    do {
        if (std::isdigit(fileStream.peek()) != 0) {
            // it is a line describing a file
            std::string line;
            std::getline(fileStream, line);
            std::stringstream lineStream{line};
            uint32_t fileSize = 0;
            std::string fileName;
            lineStream >> fileSize >> fileName;
            tree.getCurrentDirectory().addFile(fileName, fileSize);
        } else {
            // it is a line describing a dir
            std::string line;
            std::getline(fileStream, line);
            std::stringstream lineStream{line};
            std::string dirWord;
            std::string dirName;
            lineStream >> dirWord >> dirName;
            tree.getCurrentDirectory().addDirectory(dirName);
        }
    } while (fileStream.peek() != StartCommandChar && fileStream);
}

/**
 * @brief
 *
 * @param[in] fileStream
 * @param[in,out] currentDir
 */
void readCommand(std::ifstream& fileStream, DirectoryTree& tree)
{
    // Read until the next "$ ls" or "$ cd" or end of input
    do {
        // read whole line from input file
        std::string line;
        std::getline(fileStream, line);
        std::stringstream lineStream{line};
        // read command
        char dollarChar = 0;
        std::string command;
        lineStream >> dollarChar >> command;
        if (command == CdCommand) {
            std::string destinationDir;
            lineStream >> destinationDir;
            executeCdCommand(tree, destinationDir);
        } else if (command == LsCommand) {
            executeLsCommand(tree, fileStream);
        }
    } while (fileStream.peek() == StartCommandChar && fileStream);
}

/**
 * @brief
 *
 * @param[in] fileStream
 *
 * @return DirectoryTree
 */
DirectoryTree parseInput(std::ifstream& fileStream)
{
    DirectoryTree tree;

    // Read each command
    while (fileStream.peek() == StartCommandChar) {
        readCommand(fileStream, tree);
    }

    return tree;
}

uint32_t calculateSumOfChildDirSizes(
    IDirectory const& dir, std::function<bool(uint32_t)> condition)
{
    uint32_t totalSum = 0U;
    for (auto childDir : dir.getChildDirectories()) {
        const uint32_t childSize = childDir->getSize();
        if (condition(childSize)) {
            totalSum += childSize;
        }
        if (!childDir->getChildDirectories().empty()) {
            totalSum += calculateSumOfChildDirSizes(*childDir, condition);
        }
    }
    return totalSum;
}

uint32_t getSmallestChildDirSize(
    IDirectory const& dir, std::function<bool(uint32_t)> condition)
{
    uint32_t minSize = std::numeric_limits<uint32_t>::max();
    for (auto childDir : dir.getChildDirectories()) {
        auto const dirSize = childDir->getSize();
        if (condition(dirSize)) {
            minSize = std::min(minSize, dirSize);
        }
        if (!childDir->getChildDirectories().empty()) {
            const uint32_t minChildSize = getSmallestChildDirSize(
                *childDir, condition);
            if (condition(minChildSize)) {
                minSize = std::min(minSize, minChildSize);
            }
        }
    }
    return minSize;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    constexpr uint32_t MaxSumSize{100000U};

    std::ifstream fileStream{filename};

    DirectoryTree tree{parseInput(fileStream)};

    constexpr auto MaxSumSizeCondition = [](const uint32_t size) {
        return size <= MaxSumSize;
    };
    uint32_t sumSizes{0U};
    if (MaxSumSizeCondition(tree.getRoot().getSize())) {
        sumSizes += tree.getRoot().getSize();
    }
    sumSizes += calculateSumOfChildDirSizes(
        tree.getRoot(), MaxSumSizeCondition);

    return std::to_string(sumSizes);
}

std::string solvePart2(std::string const& filename)
{
    constexpr uint32_t TotalDiskCapacity{70000000U};
    constexpr uint32_t MinimalUnusedDiskSpace{30000000U};
    constexpr uint32_t MaxRootSize{TotalDiskCapacity - MinimalUnusedDiskSpace};

    std::ifstream fileStream{filename};

    DirectoryTree tree{parseInput(fileStream)};

    const uint32_t currentRootSize = tree.getRoot().getSize();
    const uint32_t diskSpaceToFree = currentRootSize - MaxRootSize;
    auto minSizeCondition = [diskSpaceToFree](const uint32_t size) {
        return size >= diskSpaceToFree;
    };
    uint32_t minSize{currentRootSize};
    const uint32_t minChildSize{
        getSmallestChildDirSize(tree.getRoot(), minSizeCondition)};
    minSize = (minChildSize < minSize) ? (minChildSize) : minSize;

    return std::to_string(minSize);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_7
