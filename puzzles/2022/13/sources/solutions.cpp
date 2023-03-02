#include "solutions.hpp"

#include "Packet.hpp"
#include <fstream>
#include <sstream>

namespace aoc_2022_13 {

// ---------- Private Methods ----------

Packet parsePacket(const std::string& line)
{
    std::stringstream lineStream{ line };
    Packet packet;
    Item* currentItem{ &packet.getRootItem() };
    while (lineStream) {
        if (std::isdigit(lineStream.peek()) != 0) { // New value node
            uint32_t value{ 0U };
            lineStream >> value;
            currentItem->setInteger(value);
        } else if (lineStream.peek() == '[') { // New list node
            lineStream.get();
            if (currentItem != nullptr) {
                Item& nextItem{ currentItem->addItemToList() };
                currentItem = &nextItem;
            }
        } else if (lineStream.peek() == ']') { // End of list node
            lineStream.get();
            currentItem = currentItem->getParent();
            // Closing bracket for the outer node == end of packet.
            if (currentItem == nullptr) {
                return packet;
            }
        } else { // Whitespace
            lineStream.get();
        }
    }
    return packet;
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
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_13