#pragma once

#include "IFile.h"
#include <string>

namespace aoc_2022_7 {

class File : public IFile {
public:
    File(IDirectory const& dir, std::string_view name, uint32_t size);
    ~File() override = default;
    uint32_t getSize() const override;
    std::string_view getName() const override;
    IDirectory const& getDir() const override;

private:
    IDirectory const& mCurrentDir;
    uint32_t const mSize;
    std::string const mName;
};

} // namespace aoc_2022_7
