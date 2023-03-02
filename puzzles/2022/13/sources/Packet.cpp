#include "Packet.hpp"

namespace aoc_2022_13 {

Packet::Packet()
    : mRootItem{ std::make_unique<Item>(nullptr) }
{
}

auto Packet::operator<=>(const Packet& other) const
{
    return *mRootItem <=> *other.mRootItem;
}

Item& Packet::getRootItem() const { return *mRootItem; }

} // namespace aoc_2022_13
