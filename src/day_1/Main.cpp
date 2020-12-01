
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>

bool readFile(std::string filePath, std::vector<std::string> &lines)
{
    std::string line;

    std::ifstream thisFile;
    thisFile.open(filePath);

    if (!thisFile)
    {
        std::cout << "[ERROR]\tunable to open file: " << filePath << std::endl;
        return false;
    }

    while (std::getline(thisFile, line))
        lines.emplace_back(line);
    
    thisFile.close();
    return true;
}

bool parseInput(std::vector<std::string> lines, std::vector<unsigned short> &values)
{
    unsigned short
        maxValue = std::numeric_limits<unsigned short>::max(),
        minValue = std::numeric_limits<unsigned short>::min();

    for (std::string line : lines)
    {
        int value = std::stoi(line);
        if (value < minValue || value > maxValue)
        {
            std::cout << "[ERROR]\tconversion error; value out of bounds" << std::endl;
            return false;            
        }
        values.emplace_back(value);
    }
    return true;
}

int findSolution_first(std::vector<unsigned short> values)
{
    for (std::size_t i = 0; i < values.size(); i++)
    {
        for (std::size_t j = i; j < values.size(); j++)
        {
            if (values.at(i) + values.at(j) == 2020)
                return values.at(i) * values.at(j);
        }
    }
    std::cout << "[ERROR]\tsolution not found" << std::endl;
    return -1;
}

int findSolution_second(std::vector<unsigned short> values)
{
    for (std::size_t a = 0; a < values.size(); a++)
    {
        for (std::size_t b = a; b < values.size(); b++)
        {
            for (std::size_t c = b; c < values.size(); c++)
            {
                if (values.at(a) + values.at(b) + values.at(c) == 2020)
                    return values.at(a) * values.at(b) * values.at(c);
            }
        }
    }
    std::cout << "[ERROR]\tsolution not found" << std::endl;
    return -1;
}

int main(void)
{
    std::string filePath = "puzzleInput.txt";

    std::vector<std::string> lines;
    std::vector<unsigned short> values;

    if (!readFile(filePath, lines))
        return EXIT_FAILURE;
    if (!parseInput(lines, values))
        return EXIT_FAILURE;

    int firstSolution = findSolution_first(values);
    int secondSolution = findSolution_second(values);

    if (firstSolution == -1 || secondSolution == -1)
        return EXIT_FAILURE;

    std::cout << "solutions:\n" << firstSolution <<  "\n" << secondSolution << std::endl;
    return EXIT_SUCCESS;
}