#include <fstream>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> ReadLinesFromFile(const char* filename) {
	std::ifstream stream(filename);

	std::vector<std::string> all_lines;
	std::string line;
	while (std::getline(stream, line)) {
		all_lines.emplace_back(std::move(line));
	}
	stream.close();
	return all_lines;
}

int main()
{
	const auto inputValues = ReadLinesFromFile("input.csv");
	int counter = 0;
	for (int i = 1; i < inputValues.size(); ++i)
	{
		if (inputValues[i] > inputValues[i-1])
		{
			++counter;
		}
	}
	std::cout << counter << std::endl;

	return 0;
}
