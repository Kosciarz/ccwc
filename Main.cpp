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

size_t CountBytes(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Can't open a file with path: " / filePath);

    size_t bytesCount{};
    char ch{};
    while (file.get(ch))
    {
        bytesCount++;
    }

    file.close();
    return bytesCount;
}

size_t CountLines(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Can't open a file with path: " / filePath);

    size_t linesCount{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        linesCount++;
    }

    file.close();
    return linesCount;
}

size_t CountWords(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Can't open a file with path: " / filePath);

    size_t wordsCount{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        std::stringstream sstream(fileLine);
        std::string word{};
        while (sstream >> word)
        {
            wordsCount++;
        }
    }

    file.close();
    return wordsCount;
}

size_t CountCharacters(const std::filesystem::path& filePath)
{
    std::wifstream file(filePath);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open())
        throw std::runtime_error("Can't open a file with path: " / filePath);

    size_t characterCount{};
    wchar_t ch{};
    while (file.get(ch))
    {
        characterCount++;
    }

    file.close();
    return characterCount;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args = ConvertArgvToString(argc, argv);

    if (argc == 3)
    {
        std::string operation          = args[1];
        std::filesystem::path filePath = args[2];

        try
        {
            if (operation == "-c")
                CountBytes(filePath);
            if (operation == "-l")
                CountLines(filePath);
            if (operation == "-w")
                CountWords(filePath);
            if (operation == "-m")
                CountCharacters(filePath);
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    if (argc == 2)
    {
        std::filesystem::path filePath = args[1];
        try
        {
            size_t lineCount  = CountLines(filePath);
            size_t wordCount  = CountWords(filePath);
            size_t bytesCount = CountBytes(filePath);
            std::cout << '\t' << lineCount << '\t' << wordCount << '\t' << bytesCount << '\t' << filePath.string() << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}