#pragma once

#include "StringHash.h"
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace utils::extensions {

using UnorderedStringSet = std::
    unordered_set<std::string, StringHash, std::equal_to<>>;
template <typename T>
using UnorderedStringMap = std::
    unordered_map<std::string, T, StringHash, std::equal_to<>>;

using StringSet = std::set<std::string, std::less<>>;
template <typename T>
using StringMap = std::map<std::string, T, std::less<>>;

template <typename T>
using StringMultimap = std::multimap<std::string, T, std::less<>>;

} // namespace utils::extensions