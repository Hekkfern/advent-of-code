#include "DirectoryTree.h"

#include "Directory.h"
#include <range/v3/all.hpp>

namespace aoc_2022_7 {

constexpr auto CdCommandRoot{ "/" };
constexpr auto CdCommandGoUp{ ".." };

DirectoryTree::DirectoryTree()
    : mRootDir{ std::make_unique<Directory>("") }
    , mCurrentDir{ &getRoot() }
{
}

IDirectory& DirectoryTree::getRoot() const { return *mRootDir; }

void DirectoryTree::changeDirectory(std::string_view dir)
{
    if (dir == CdCommandRoot) {
        mCurrentDir = &getRoot();
    } else if (dir == CdCommandGoUp) {
        mCurrentDir = mCurrentDir->getParentDirectory();
    } else {
        auto childDirs = mCurrentDir->getChildDirectories();
        auto childIt = ranges::find_if(
            childDirs, [dir](const IDirectory* const childDir) {
                return childDir->getName() == dir;
            });
        mCurrentDir = *childIt;
    }
}
IDirectory& DirectoryTree::getCurrentDirectory() const { return *mCurrentDir; }

} // namespace aoc_2022_7
