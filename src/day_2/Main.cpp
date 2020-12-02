#include <iostream>

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



int main (void ) 
{
    std::cout << "Hello world!" << std::endl;
}