#pragma once

#include <cstdint>
#include <string_view>

namespace aoc_2022_7 {

class IDirectory;

class IFile {
public:
    virtual ~IFile() = default;
    virtual std::string_view getName() const = 0;
    virtual const IDirectory& getDir() const = 0;
    virtual uint32_t getSize() const = 0;
};

} // namespace aoc_2022_7
