#include "solutions.hpp"

#include "Packet.hpp"
#include <fstream>
#include <range/v3/all.hpp>
#include <sstream>

namespace aoc_2022_13 {

// ---------- Private Methods ----------

Packet parsePacket(const std::string& line)
{
    std::stringstream lineStream{ line };
    Packet packet;
    Item* currentItem{ nullptr };
    while (lineStream) {
        if (std::isdigit(lineStream.peek()) != 0) { // New value node
            uint32_t value{ 0U };
            lineStream >> value;
            currentItem->addIntegerItem(value);
        } else if (lineStream.peek() == '[') { // New list node
            lineStream.get(); // get '[' char
            if (packet.getRoot() == nullptr) { // check for root Item
                packet.setRoot(
                    std::make_unique<Item>(Item::createListItem(nullptr)));
                currentItem = packet.getRoot();
            } else {
                Item& nextItem{ currentItem->addListItem() };
                currentItem = &nextItem;
            }
        } else if (lineStream.peek() == ']') { // End of list node
            lineStream.get();
            // Closing bracket for the outer node == end of packet.
            if (currentItem->getParent() == nullptr) {
                return packet;
            }
            currentItem = currentItem->getParent();
        } else { // Whitespace or comma
            lineStream.get();
        }
    }
    return packet;
}

Packet createKeyPacket(uint32_t value)
{
    Packet packet;
    packet.setRoot(std::make_unique<Item>(Item::createListItem(nullptr)));
    auto currentItem = packet.getRoot();
    currentItem = &currentItem->addListItem();
    currentItem->addIntegerItem(value);
    return packet;
}

uint32_t findDecoderKey(std::vector<Packet>& packets)
{
    ranges::sort(packets, std::less<>());

    auto keyPacket1{ createKeyPacket(2U) };
    auto keyPacket2{ createKeyPacket(6U) };

    auto first{ ranges::lower_bound(packets, keyPacket1, std::less<>()) };
    auto second{ ranges::upper_bound(packets, keyPacket2, std::less<>()) };

    // lower_bound returns the first element not less than the lookup
    // 1-based index
    uint32_t key = ranges::distance(packets.begin(), first) + 1;
    // upper_bound returns the first element greater than the lookup
    // 1-based index and offset for Packet(2)
    key *= ranges::distance(packets.begin(), second) + 2;
    return key;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t index{ 1U };
    uint32_t sum{ 0U };
    while (std::getline(fileStream, line)) {
        if (line.empty()) {
            continue;
        }
        auto packet1{ parsePacket(line) };
        std::getline(fileStream, line);
        auto packet2{ parsePacket(line) };
        if (packet1 < packet2) {
            sum += index;
        }
        ++index;
    }
    return std::to_string(sum);
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    std::vector<Packet> packets;
    while (std::getline(fileStream, line)) {
        if (line.empty()) {
            continue;
        }
        packets.emplace_back(parsePacket(line));
        std::getline(fileStream, line);
        packets.emplace_back(parsePacket(line));
    }
    return std::to_string(findDecoderKey(packets));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_13