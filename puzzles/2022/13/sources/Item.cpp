#include "Item.hpp"

#include <compare>

namespace aoc_2022_13 {

Item::Item(Item* const parent)
    : mParent(parent)
{
}

std::strong_ordering Item::compare(uint32_t value1, uint32_t value2) const
{
    return value1 <=> value2;
}

std::strong_ordering Item::compare(
    uint32_t value,
    const std::vector<Item>& list) const
{
    // Comparing value against and empty list.
    if (list.empty()) {
        return std::strong_ordering::greater;
    }
    // Comparing a value against a list, recurse.
    std::strong_ordering cmp{ std::strong_ordering::equal };
    if (list[0].mType == Type::Integer) {
        cmp = compare(value, *list[0].mValue);
    } else {
        cmp = compare(value, list[0].mContent);
    }
    if (cmp == 0) {
        // X <=> [X,...]
        if (list.size() == 1) {
            return std::strong_ordering::equal;
        }
        return std::strong_ordering::less;
    }
    return cmp;
}

std::strong_ordering Item::compare(
    const std::vector<Item>& list,
    uint32_t value) const
{
    // reverse because we permuted the parameters to fit into the same
    // method
    return 0 <=> compare(value, list);
}

std::strong_ordering Item::compare(
    const std::vector<Item>& list1,
    const std::vector<Item>& list2) const
{
    auto list1It = list1.cbegin();
    auto list2It = list2.cbegin();
    while (true) {
        // Terminal states end of list(s)
        if (list1It == list1.cend() && list2It == list2.cend()) {
            return std::strong_ordering::equal;
        }
        if (list1It == list1.cend()) {
            return std::strong_ordering::less;
        }
        if (list2It == list2.cend()) {
            return std::strong_ordering::greater;
        }

        auto cmp = *list1It <=> *list2It;
        if (cmp != 0) {
            return cmp;
        }
        list1It++;
        list2It++;
    }
}

std::strong_ordering Item::operator<=>(const Item& other) const
{
    if (mType == Type::Integer && other.mType == Type::Integer) {
        return compare(*mValue, *other.mValue);
    } else if (mType == Type::Integer && other.mType == Type::List) {
        return compare(*mValue, other.mContent);
    } else if (mType == Type::List && other.mType == Type::Integer) {
        return compare(mContent, *other.mValue);
    } else if (mType == Type::List && other.mType == Type::List) {
        return compare(mContent, other.mContent);
    } else {
        /* Error */
        throw std::logic_error("Invalid item types");
    }
}

std::optional<std::reference_wrapper<Item>> Item::addItemToList()
{
    if (mType == Type::Integer) {
        return std::nullopt;
    }
    mType = Type::List;
    auto newItem{ mContent.emplace_back(*this) };
    return std::make_optional(std::ref(newItem));
}

std::optional<uint32_t> Item::setInteger(uint32_t value)
{
    if (mType == Type::List) {
        return std::nullopt;
    }
    mType = Type::Integer;
    mValue = std::make_optional(value);
    return mValue;
}

} // namespace aoc_2022_13
