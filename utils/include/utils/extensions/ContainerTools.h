// (C) king.com Ltd 2023
#pragma once

#include <cassert>
#include <optional>
#include <queue>
#include <utility>

/**
 * @file
 * @brief Provides helper functions for conveniently dealing with STL
 * containers.
 */

namespace utils::extensions {

/** @brief Erases the element at @p it inside @p container and returns it. @p it
 * _must_ refer to a valid element. */
template <typename ContT>
[[nodiscard]] typename ContT::value_type
take(ContT& container, typename ContT::iterator it)
{
    assert(it != container.end());
    auto val = std::move(*it);
    container.erase(it);
    return val;
}

/** @brief Erases the element at @p it inside map @p container and returns its
 * mapped value. @p it _must_ refer to a valid element. */
template <typename ContT>
[[nodiscard]] typename ContT::mapped_type
take_mapped(ContT& container, typename ContT::iterator it)
{
    assert(it != container.end());
    auto val = std::move(it->second);
    container.erase(it);
    return val;
}

/** @brief Erases the element at @p it inside @p container and returns it, or
 * returns nullopt if @p it equals `container.end()`. */
template <typename ContT>
[[nodiscard]] std::optional<typename ContT::value_type>
try_take(ContT& container, typename ContT::iterator it)
{
    if (it == container.end()) {
        return std::nullopt;
    }
    return take(container, it);
}

/** @brief Erases the element at @p it inside map @p container and returns its
 * mapped value, or returns nullopt if @p it equals `container.end()`. */
template <typename ContT>
[[nodiscard]] std::optional<typename ContT::mapped_type>
try_take_mapped(ContT& container, typename ContT::iterator it)
{
    if (it == container.end()) {
        return std::nullopt;
    }
    return take_mapped(container, it);
}

/** @brief Erases the element at @p it if valid, returning true if erase was
 * successful or false if `it == container.end()`. */
template <typename ContT>
[[nodiscard]] bool
try_erase(ContT& container, typename ContT::const_iterator it)
{
    if (it == container.end()) {
        return false;
    }
    container.erase(it);
    return true;
}

/** @brief Erases the last element inside @p container and returns it. @p
 * container _must not_ be empty. */
template <typename ContT>
[[nodiscard]] typename ContT::value_type take_back(ContT& container)
{
    assert(!container.empty());
    auto val = std::move(container.back());
    container.pop_back();
    return val;
}

/** @brief Erases the first element inside @p container and returns it. @p
 * container _must not_ be empty. */
template <typename ContT>
[[nodiscard]] typename ContT::value_type take_front(ContT& container)
{
    assert(!container.empty());
    auto val = std::move(container.front());
    container.pop_front();
    return val;
}

/** @brief Erases the front element inside @p queue and returns it. @p
 * container _must not_ be empty. */
template <typename T, typename ContT>
[[nodiscard]] typename ContT::value_type take_front(std::queue<T, ContT>& queue)
{
    assert(!queue.empty());
    auto val = std::move(queue.front());
    queue.pop();
    return val;
}

/** @brief Erases the last element inside @p container and returns it, or
 * returns nullopt if @p container is empty. */
template <typename ContT>
[[nodiscard]] std::optional<typename ContT::value_type>
try_take_back(ContT& container)
{
    if (container.empty()) {
        return std::nullopt;
    }
    return take_back(container);
}

/** @brief Erases the first element inside @p container and returns it, or
 * returns nullopt if @p container is empty. */
template <typename ContT>
[[nodiscard]] std::optional<typename ContT::value_type>
try_take_front(ContT& container)
{
    if (container.empty()) {
        return std::nullopt;
    }
    return take_front(container);
}

} // namespace utils::extensions