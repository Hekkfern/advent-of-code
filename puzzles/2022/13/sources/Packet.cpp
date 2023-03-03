#include "Packet.hpp"

namespace aoc_2022_13 {

Packet::Packet()
    : mRootItem{ std::make_unique<Item>(Item::createListItem(nullptr)) }
{
}

std::strong_ordering Packet::operator<=>(const Packet& other) const
{
    return *mRootItem <=> *other.mRootItem;
}

Item& Packet::getRootItem() const { return *mRootItem; }

} // namespace aoc_2022_13
