#pragma once

#include "IFile.h"
#include <string>

namespace aoc_2022_7 {

class File : public IFile {
public:
    File(const IDirectory& dir, std::string_view name, uint32_t size);
    ~File() override = default;
    uint32_t getSize() const override;
    std::string_view getName() const override;
    const IDirectory& getDir() const override;

private:
    const IDirectory& mCurrentDir;
    const uint32_t mSize;
    const std::string mName;
};

} // namespace aoc_2022_7
