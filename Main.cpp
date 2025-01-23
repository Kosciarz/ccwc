#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> ConvertArgvToString(int argc, char** argv)
{
    std::vector<std::string> args{};
    for (int i = 0; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }
    return args;
}

void CountBytes(std::filesystem::path filePath)
{
    std::ifstream file(filePath);

    char ch;
    int numberOfBytes{};
    while (file.get(ch))
    {
        numberOfBytes++;
    }
    std::cout << numberOfBytes << '\n';

    file.close();
}

void CountLines(std::filesystem::path filePath)
{
    std::ifstream file(filePath);

    int numberOfLines{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        numberOfLines++;
    }
    std::cout << numberOfLines << '\n';

    file.close();
}

void CountWords(std::filesystem::path filePath)
{
    std::ifstream file(filePath);

    int numberOfWords{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        std::stringstream sstream(fileLine);
        std::string word{};
        while(sstream >> word)
        {
            numberOfWords++;
        }
    }
    std::cout << numberOfWords << '\n';

    file.close();
}

int main(int argc, char** argv)
{
    std::vector<std::string> args = ConvertArgvToString(argc, argv);

    std::string operation          = args[1];
    std::filesystem::path filePath = args[2];

    if (operation == "-c")
        CountBytes(filePath);
    if (operation == "-l")
        CountLines(filePath);
    if (operation == "-w")
        CountWords(filePath);
}