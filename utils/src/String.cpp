#include "String.hpp"

#include <range/v3/all.hpp>

namespace utils::string {

bool contains(std::string const& str, std::string const& match)
{
    return str.find(match) != std::string::npos;
}

std::string trim(std::string const& s)
{
    auto first = s.find_first_not_of(" \f\n\r\t\v");
    auto last = s.find_last_not_of(" \f\n\r\t\v");
    return first == std::string::npos ? "" : s.substr(first, last + 1);
}

std::string
join(std::vector<std::string> const& strings, std::string_view delimiter)
{
    if (strings.empty()) {
        return {};
    }

    return ranges::fold_left(
        strings.begin() + 1,
        strings.end(),
        strings[0],
        [&delimiter](std::string const& x, std::string const& y)
            -> std::string { return x + std::string{delimiter} + y; });
}

std::string convertFrom(std::vector<std::vector<char>> const& input)
{
    std::vector<std::string> lines;
    for (auto const& item : input) {
        lines.emplace_back(item.begin(), item.end());
    }
    return join(lines, "\n");
}

std::vector<std::string> split(std::string_view str, std::string_view separator)
{
    auto list{
        str | ranges::views::split(separator)
        | ranges::views::transform([](auto&& rng) {
              return std::string(
                  &*rng.begin(),
                  static_cast<std::size_t>(ranges::distance(rng)));
          })};
    return ranges::to<std::vector>(list);
}

} // namespace utils::string
