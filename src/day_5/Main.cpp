#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <array>

struct Seat
{
    unsigned short row;
    unsigned short col;
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

unsigned short getLocation(std::string line, unsigned short min, unsigned short max, char upper, char lower)
{
    for (std::size_t i = 0; i < line.length() - 1; i++)
    {
        if (line[i] == lower) // minnus half of the difference
            max = (unsigned short)(max - std::ceil((max - min) / 2));

        if (line[i] == upper) // plus half of the difference
            min = (unsigned short)(min + std::ceil((max - min) / 2));
    }
    return (line[line.length() - 1] == lower) ? min : (unsigned short)(max - 1);
}

Seat getSeatLocation(std::string line)
{
    std::string rowLine = line.substr(0, line.length() - 3);
    std::string colLine = line.substr(line.length() - 3, 3);

    Seat seat = {0, 0};
    seat.row = getLocation(rowLine, 0, 128, 'B', 'F');
    seat.col = getLocation(colLine, 0, 8, 'R', 'L');
    return seat;
}

unsigned short checkSolutionOne(std::vector<std::string> lines)
{
    unsigned short highestID = 0;
    for (std::string line : lines)
    {
        Seat seat = getSeatLocation(line);
        unsigned short seatID = (unsigned short)(seat.row * 8 + seat.col);
        highestID = (seatID > highestID) ? seatID : highestID;
    }
    return highestID;
}

unsigned short checkSolutionTwo(std::vector<std::string> lines)
{
    std::vector<unsigned short> seatNumbers;
    for (std::string line : lines)
    {
        Seat seat = getSeatLocation(line);
        seatNumbers.emplace_back(seat.row * 8 + seat.col);
    }
    std::sort(seatNumbers.begin(), seatNumbers.end());

    for (std::size_t i = 1; i < seatNumbers.size() - 1; i++)
        if (seatNumbers.at(i - 1) == seatNumbers.at(i) - 2)
            return (unsigned short)(seatNumbers.at(i) -1);
    return 0;
}


int main(void)
{
    std::string filePath = "puzzleInput.txt";

    std::vector<std::string> lines;

    if (!readFile(filePath, lines))
        return EXIT_FAILURE;

    std::cout << "1. highest seatID: " << checkSolutionOne(lines) << std::endl;
    std::cout << "2. claimed seatID: " << checkSolutionTwo(lines) << std::endl;

    return EXIT_SUCCESS;
}