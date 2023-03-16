#pragma once

#include "Item.hpp"
#include <memory>

namespace aoc_2022_13 {

class Packet {
public:
    Packet();
    void setRoot(std::unique_ptr<Item>&& item);
    Item* getRoot() const;
    std::strong_ordering operator<=>(const Packet& other) const;

private:
    std::unique_ptr<Item> mRootItem;
};

} // namespace aoc_2022_13
