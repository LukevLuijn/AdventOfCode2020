#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Value
{
    unsigned short min, max;
    char key;
    std::string code;
};

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

Value parseLine(std::string line)
{
    Value values;
    unsigned short lastIndex = 0;

    for (std::size_t i = 0; i < line.length(); i++)
    {
        switch (line[i])
        {
        case '-':
            values.min = (unsigned short)std::stoi(line.substr(lastIndex, i - lastIndex));
            lastIndex = (unsigned short)(1 + i);
            continue;
        case ' ':
            values.max = (unsigned short)std::stoi(line.substr(lastIndex, i - lastIndex));
            lastIndex = (unsigned short)(1 + i);
            continue;
        case ':':
            values.key = line[i - 1];
            values.code = line.substr(i + 2, line.length() - i + 1);
            return values;
        }
    }
    std::cout << "[ERROR]\t did not find all values" << std::endl;
    return values;
}

unsigned short checkSolutionOne(std::vector<std::string> lines)
{
    unsigned short counter = 0;

    for (std::string line : lines)
    {
        unsigned short keyCount = 0;
        Value values = parseLine(line);

        for (std::size_t i = 0; i < values.code.length(); ++i)
            if (values.code[i] == values.key)
                keyCount++;

        if (keyCount <= values.max && keyCount >= values.min)
            counter++;
    }
    return counter;
}

unsigned short checkSolutionTwo(std::vector<std::string> lines)
{
    unsigned short counter = 0;

    for (std::string line : lines)
    {
        Value values = parseLine(line);

        bool posOne = values.code[values.min-1] == values.key,
             posTwo = values.code[values.max-1] == values.key;

        

        if ((posOne || posTwo) && !(posOne && posTwo))
        {
            std::cout << "YES\t";
            counter++;
        }
        else 
        {
            std::cout << "NO\t";
        }

        std::cout << values.key << ", " << values.min << ", " << values.max << ":\t" << values.code[values.min-1] << ", " << values.code[values.max-1] << " -> " << values.code << "\n";
    }
    return counter;
}

int main(void)
{
    std::string filePath = "puzzleInput.txt";

    std::vector<std::string> lines;

    if (!readFile(filePath, lines))
        return EXIT_FAILURE;

    std::cout << "1. correct passwords: " << checkSolutionOne(lines) << std::endl;
    std::cout << "2. correct passwords: " << checkSolutionTwo(lines) << std::endl;

    return EXIT_SUCCESS;
}