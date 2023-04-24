#include "Packet.hpp"

namespace aoc_2022_13 {

Packet::Packet()
    : mRootItem{nullptr}
{
}

std::strong_ordering Packet::operator<=>(Packet const& other) const
{
    return *mRootItem <=> *other.mRootItem;
}

Item* Packet::getRoot() const { return mRootItem.get(); }

void Packet::setRoot(std::unique_ptr<Item>&& item)
{
    mRootItem = std::move(item);
}

} // namespace aoc_2022_13
