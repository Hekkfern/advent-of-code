#include "DynamicProgramming.hpp"

#include <algorithm>

namespace utils::dp {

std::size_t
longestCommonSubsequence(std::string_view text1, std::string_view text2)
{
    if (text1.empty() || text2.empty()) {
        return 0;
    }
    if (text1.back() == text2.back()) {
        return 1
            + longestCommonSubsequence(
                   text1.substr(0, text1.size() - 1),
                   text2.substr(0, text2.size() - 1));
    } else {
        return std::max(
            longestCommonSubsequence(
                text1.substr(0, text1.size() - 1),
                text2.substr(0, text2.size())),
            longestCommonSubsequence(
                text1.substr(0, text1.size()),
                text2.substr(0, text2.size() - 1)));
    }
}

} // namespace utils::dp
