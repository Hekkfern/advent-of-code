#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>

namespace utils::extensions {

struct StringHash {
    using is_transparent = void;
    [[nodiscard]] size_t operator()(char const* str) const
    {
        return std::hash<std::string_view>{}(str);
    }
    [[nodiscard]] size_t operator()(std::string_view str) const
    {
        return std::hash<std::string_view>{}(str);
    }
    [[nodiscard]] size_t operator()(std::string const& str) const
    {
        return std::hash<std::string_view>{}(str);
    }
};

} // namespace utils::extensions
