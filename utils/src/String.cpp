#include "String.hpp"

#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/unique.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>

namespace {
constexpr auto TrimmableChars{" \f\n\r\t\v"};
}

namespace utils::string {

bool contains(std::string_view const str, std::string_view const match)
{
    return str.find(match) != std::string::npos;
}

std::string ltrim(std::string_view s)
{
    s.remove_prefix(std::min(s.find_first_not_of(TrimmableChars), s.size()));
    return std::string{s};
}

std::string rtrim(std::string_view s)
{
    s.remove_suffix(
        s.size() - std::max(s.find_last_not_of(TrimmableChars), std::size_t{0})
        - 1);
    return std::string{s};
}

std::string trim(std::string_view s)
{
    s.remove_prefix(std::min(s.find_first_not_of(TrimmableChars), s.size()));
    s.remove_suffix(
        s.size() - std::max(s.find_last_not_of(TrimmableChars), std::size_t{0})
        - 1);
    return std::string{s};
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

std::string join(std::vector<std::vector<char>> const& input)
{
    std::vector<std::string> lines;
    for (auto const& item : input) {
        lines.emplace_back(item.begin(), item.end());
    }
    return join(lines, "\n");
}

std::vector<std::string> split(std::string_view str, std::string_view separator)
{
    return str | ranges::views::split(separator)
        | ranges::views::transform([](auto&& rng) {
               return std::string(
                   &*rng.begin(),
                   static_cast<std::size_t>(ranges::distance(rng)));
           })
        | ranges::to<std::vector>();
}

std::string remove_excess_whitespace(std::string s)
{
    static constexpr auto space_space =
        [](unsigned char a, unsigned char b) -> bool {
        return std::isspace(a) && std::isspace(b);
    };

    s.erase(ranges::unique(s, space_space), s.end());

    // trim final space
    if (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) {
        s.pop_back();
    }

    return s;
}

} // namespace utils::string
