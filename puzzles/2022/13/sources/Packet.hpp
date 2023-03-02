#pragma once

#include "Item.hpp"

namespace aoc_2022_13 {

class Packet {
public:
    Packet();
    Item& getRootItem() const;
    auto operator<=>(const Packet& other) const;

private:
    std::unique_ptr<Item> mRootItem;
};

} // namespace aoc_2022_13
