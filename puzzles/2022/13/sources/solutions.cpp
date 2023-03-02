#include "solutions.hpp"

#include "Packet.hpp"
#include <fstream>
#include <sstream>

namespace aoc_2022_13 {

// ---------- Private Methods ----------

std::pair<Packet, Packet> parsePacket(std::ifstream& fileStream)
{
    std::string line;
    std::getline(fileStream, line);
    std::stringstream lineStream{line};
    while (lineStream) {
        // New value node
        if (std::isdigit(lineStream.peek()) != 0) {
            int value;
            lineStream >> value;
            signal.new_value_node(current, v);
            // New list node
        } else if (s.peek() == '[') {
            s.get();
            Node *next = signal.new_list_node(current);
            if (current == nullptr) signal.root = next;
            current = next;
            // End of list node
        } else if (s.peek() == ']') {
            s.get();
            current = current->parent;
            // Closing bracket for the outer node == end of packet.
            if (current == nullptr) return s;
            // Whitespace
        } else {
            s.get();
        }
    }

}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_13