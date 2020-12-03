#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

unsigned short countTrees(std::vector<std::string> lines, unsigned short rightSteps, unsigned short downSteps)
{
    unsigned short
        lineLength = lines.at(0).length(),
        treeCounter = 0,
        x = 0;

    char tree = '#';

    for (std::size_t y = 0; y < lines.size(); y += downSteps)
    {
        if (lines.at(y)[x] == tree)
            treeCounter++;

        x += rightSteps;
        if (lineLength <= x)
            x = x - lineLength;
    }

    return treeCounter;
}

unsigned short checkSolutionOne(std::vector<std::string> lines)
{
    return countTrees(lines, 3, 1);
}

unsigned long checkSolutionTwo(std::vector<std::string> lines)
{
    std::vector<unsigned short> amountOfTrees =
        {
            countTrees(lines, 1, 1),
            countTrees(lines, 3, 1),
            countTrees(lines, 5, 1),
            countTrees(lines, 7, 1),
            countTrees(lines, 1, 2)};

    unsigned long multi = 1;

    std::cout << "val: ";

    for (unsigned short val : amountOfTrees)
    {
        std::cout << ", " << val;
        multi *= val;
    }

    std::cout << std::endl;

    return multi;
}

int main(void)
{
    std::string filePath = "puzzleInput.txt";

    std::vector<std::string> lines;

    if (!readFile(filePath, lines))
        return EXIT_FAILURE;

    std::cout << "1. amount of trees: " << checkSolutionOne(lines) << std::endl;
    std::cout << "2. amount of trees: " << checkSolutionTwo(lines) << std::endl;

    return EXIT_SUCCESS;
}