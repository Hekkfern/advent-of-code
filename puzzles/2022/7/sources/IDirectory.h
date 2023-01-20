#pragma once

#include <string_view>
#include <vector>

namespace aoc_2022_7 {

class IFile;

class IDirectory {
public:
    virtual ~IDirectory() = default;
    virtual std::string_view getName() const = 0;
    virtual IDirectory& addDirectory(std::string_view name) = 0;
    virtual IFile& addFile(std::string_view name, uint32_t size) = 0;
    virtual IDirectory* getParentDirectory() const = 0;
    virtual std::vector<IDirectory*> getChildDirectories() const = 0;
    virtual uint32_t getSize() = 0;
};

} // namespace aoc_2022_7
