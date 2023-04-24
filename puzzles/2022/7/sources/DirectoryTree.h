#pragma once

#include <memory>
#include <string_view>

namespace aoc_2022_7 {

class IDirectory;
class IFile;

class DirectoryTree {
public:
    DirectoryTree();
    DirectoryTree(DirectoryTree const&) = delete;
    DirectoryTree& operator=(DirectoryTree const&) = delete;
    DirectoryTree(DirectoryTree&&) = default;
    DirectoryTree& operator=(DirectoryTree&&) = default;
    IDirectory& getRoot() const;
    IDirectory& getCurrentDirectory() const;
    void changeDirectory(std::string_view dir);

private:
    std::unique_ptr<IDirectory> mRootDir;
    IDirectory* mCurrentDir;
};

} // namespace aoc_2022_7
