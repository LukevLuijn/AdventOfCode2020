#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Passport
{
    std::string
        hairColor = "n/a",
        eyeColor = "n/a",
        countryID = "n/a",
        passportID = "n/a";
    unsigned short
        birthYear = 0,
        issueYear = 0,
        expirYear = 0;
    std::pair<unsigned short, std::string>
        height = {0, "n/a"};
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

std::vector<std::string> formatPassport(std::vector<std::string> passportLines)
{
    std::vector<std::string> formatted;

    for (std::string line : passportLines)
    {
        unsigned short lastIndex = 0;
        for (std::size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                formatted.emplace_back(line.substr(lastIndex, i - lastIndex));
                lastIndex = (unsigned short)(i + 1);
            }
            else if (i == line.length() - 1)
                formatted.emplace_back(line.substr(lastIndex, i - lastIndex + 1));
        }
    }
    return formatted;
}

Passport parsePassport(std::vector<std::string> passportLines)
{
    Passport thisPassport;

    for (std::string line : passportLines)
    {
        std::string key = line.substr(0, 3);

        if (key.compare("hgt") == 0)
        {
            thisPassport.height.second = line.substr(line.length() - 2, 2);
            if (thisPassport.height.second.compare("in") == 0 || thisPassport.height.second.compare("cm") == 0)
                thisPassport.height.first = (unsigned short)std::stoi(line.substr(4, line.length() - 6));
            else
            {
                thisPassport.height.second = "n/a";
                thisPassport.height.first = (unsigned short)std::stoi(line.substr(4, line.length() - 3));
            }
        }
        else if (key.compare("byr") == 0)
            thisPassport.birthYear = (unsigned short)std::stoi(line.substr(4, line.length() - 3));
        else if (key.compare("iyr") == 0)
            thisPassport.issueYear = (unsigned short)std::stoi(line.substr(4, line.length() - 3));
        else if (key.compare("eyr") == 0)
            thisPassport.expirYear = (unsigned short)std::stoi(line.substr(4, line.length() - 3));
        else if (key.compare("hcl") == 0)
            thisPassport.hairColor = line.substr(4, line.length() - 3);
        else if (key.compare("ecl") == 0)
            thisPassport.eyeColor = line.substr(4, line.length() - 3);
        else if (key.compare("pid") == 0)
            thisPassport.passportID = line.substr(4, line.length() - 3);
        else if (key.compare("cid") == 0)
            thisPassport.countryID = line.substr(4, line.length() - 3);
    }
    return thisPassport;
}

std::vector<Passport> extractPassports(std::vector<std::string> lines)
{
    std::vector<Passport> passports;
    unsigned short lastIndex = 0;

    for (std::size_t i = 0; i < lines.size(); i++)
    {
        if (lines.at(i).length() <= 0)
        {
            std::vector<std::string> thisPassportLines =
                formatPassport(std::vector<std::string>(&lines[lastIndex], &lines[i]));
            passports.emplace_back(parsePassport(thisPassportLines));

            lastIndex = (unsigned short)(i + 1);
        }

        if (i == lines.size() - 1)
        {
            std::vector<std::string> thisPassportLines =
                formatPassport(std::vector<std::string>(&lines[lastIndex], &lines[i + 1]));
            passports.emplace_back(parsePassport(thisPassportLines));
        }
    }
    return passports;
}

unsigned short checkSolutionOne(std::vector<std::string> lines)
{
    std::vector<Passport> passports = extractPassports(lines);
    unsigned short counter = 0;

    for (Passport passport : passports)
    {
        bool hairColor = passport.hairColor.compare("n/a") != 0;
        bool eyeColor = passport.eyeColor.compare("n/a") != 0;
        bool passportID = passport.passportID.compare("n/a") != 0;

        bool birthYear = passport.birthYear > 0;
        bool isseuYear = passport.issueYear > 0;
        bool expirYear = passport.expirYear > 0;

        bool height = passport.height.first > 0;

        if (hairColor && eyeColor && passportID && birthYear && isseuYear && expirYear && height)
            counter++;
    }
    return counter;
}

bool checkValues(Passport passport)
{
    bool birthYear = passport.birthYear >= 1920 && passport.birthYear <= 2002;
    bool isseuYear = passport.issueYear >= 2010 && passport.issueYear <= 2020;
    bool expirYear = passport.expirYear >= 2020 && passport.expirYear <= 2030;

    bool hairColor = passport.hairColor[0] == '#' && passport.hairColor.length() == 7;
    
    if (hairColor)
    {
        for (std::size_t i = 1; i < passport.hairColor.length(); i++)
        {
            bool isNumber = passport.hairColor[i] > 47 && passport.hairColor[i] < 58;
            bool isChar = passport.hairColor[i] > 96 && passport.hairColor[i] < 103;

            if (!isNumber && !isChar)
                hairColor = false;
        }
    }

    bool eyeColor = false;
    std::vector<std::string> eyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for (std::string color : eyeColors)
    {
        if (passport.eyeColor.compare(color) == 0)
        {
            eyeColor = true;
            break;
        }
    }

    bool passportID = passport.passportID.length() == 9;
    if (passportID)
    {
        for (std::size_t i = 0; i < 9; i++)
        {
            if (passport.passportID[i] < 48 || passport.passportID[i] > 57)
            {
                passportID = false;
                break;
            }
        }
    }

    bool height = !passport.height.second.compare("n/a") == 0;

    if (height)
    {
        if (passport.height.second.compare("cm") == 0)
            height = passport.height.first > 149 && passport.height.first < 194;
        else if (passport.height.second.compare("in") == 0)
            height = passport.height.first > 58 && passport.height.first < 77;
    }

    return hairColor && eyeColor && passportID && birthYear && isseuYear && expirYear && height;
}

unsigned short checkSolutionTwo(std::vector<std::string> lines)
{
    std::vector<Passport> passports = extractPassports(lines);
    unsigned short counter = 0;

    for (Passport ps : passports)
        if (checkValues(ps))
            counter++;

    return counter;
}

int main(void)
{
    std::string filePath = "puzzleInput.txt";

    std::vector<std::string> lines;

    if (!readFile(filePath, lines))
        return EXIT_FAILURE;

    std::cout << "1. valid passports: " << checkSolutionOne(lines) << std::endl;
    std::cout << "2. valid passports: " << checkSolutionTwo(lines) << std::endl;

    return EXIT_SUCCESS;
}