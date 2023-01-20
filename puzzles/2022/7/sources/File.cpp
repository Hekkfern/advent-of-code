#include "File.h"

namespace aoc_2022_7 {

File::File(const IDirectory& dir, std::string_view name, uint32_t size)
    : mCurrentDir{ dir }
    , mSize{ size }
    , mName{ name }
{
}

uint32_t File::getSize() const { return mSize; }

std::string_view File::getName() const { return mName; }

const IDirectory& File::getDir() const { return mCurrentDir; }

} // namespace aoc_2022_7
