#include "solutions.hpp"

#include <utils/FileUtils.hpp>

namespace aoc_2021_01 {

std::string solvePart1() {
    const auto inputList = utils::FileUtils::readListOfNumbers("input.txt");
    int64_t counter = 0;
    for (size_t i = 1; i < inputList.size() ; ++i) {
        if (inputList[i] > inputList[i-1])
        {
            ++counter;
        }
    }
    return std::to_string(counter);;
}

std::string solvePart2(){
    return "";
}

}
