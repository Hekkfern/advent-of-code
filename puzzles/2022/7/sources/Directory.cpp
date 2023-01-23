#include "Directory.h"

#include "File.h"
#include <range/v3/all.hpp>

namespace aoc_2022_7 {

uint32_t Directory::calculateSize() const
{
    return ranges::accumulate(
               mDirs | ranges::views::values,
               0U,
               [](uint32_t value, const std::unique_ptr<IDirectory>& p) {
                   return value + p->getSize();
               })
        + ranges::accumulate(
               mFiles | ranges::views::values,
               0U,
               [](uint32_t value, const std::unique_ptr<IFile>& p) {
                   return value + p->getSize();
               });
}

Directory::Directory(std::string_view name, IDirectory* parentDir)
    : mParentDir{ parentDir }
    , mName{ name }
{
}

uint32_t Directory::getSize()
{
    if (!mCachedSize) {
        // Calculate size
        mCachedSize = std::make_optional<uint32_t>(calculateSize());
    }

    return *mCachedSize;
}

std::string_view Directory::getName() const { return mName; }

IDirectory& Directory::addDirectory(std::string_view name)
{
    mDirs.emplace(name, std::make_unique<Directory>(name, this));
    return *mDirs[std::string{ name }];
}

IFile& Directory::addFile(std::string_view name, uint32_t size)
{
    mFiles.emplace(name, std::make_unique<File>(*this, name, size));
    return *mFiles[std::string{ name }];
}

IDirectory* Directory::getParentDirectory() const { return mParentDir; }

std::vector<IDirectory*> Directory::getChildDirectories() const
{
    std::vector<IDirectory*> dirs;
    for (const auto& [name, dir] : mDirs) {
        dirs.emplace_back(dir.get());
    }
    return dirs;
}

} // namespace aoc_2022_7
