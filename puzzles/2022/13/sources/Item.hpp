#pragma once

#include <compare>
#include <optional>
#include <vector>

namespace aoc_2022_13 {

enum class Type { List, Integer };

class Item {
public:
    [[nodiscard]] static Item createIntegerItem(
        Item* const parent,
        uint32_t value);
    [[nodiscard]] static Item createListItem(Item* const parent);
    Item& addListItem();
    Item& addIntegerItem(uint32_t value);
    Item* getParent() const;
    std::strong_ordering operator<=>(const Item& other) const;

private:
    Item(Item* const parent);
    std::strong_ordering compare(uint32_t value1, uint32_t value2) const;
    std::strong_ordering compare(uint32_t value, const std::vector<Item>& list)
        const;
    std::strong_ordering compare(const std::vector<Item>& list, uint32_t value)
        const;
    std::strong_ordering compare(
        const std::vector<Item>& list1,
        const std::vector<Item>& list2) const;

    Item* const mParent;
    Type mType{ Type::List };
    // Each node is either a list (!content.empty())
    std::vector<Item> mContent;
    // or a value (value != std::nullopt)
    std::optional<uint32_t> mValue;
};

} // namespace aoc_2022_13
