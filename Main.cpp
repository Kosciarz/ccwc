#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

size_t CountBytes(const std::filesystem::path& filePath)
{
    auto byteCount = std::filesystem::file_size(filePath);
    return byteCount;
}

size_t CountLines(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open a file with path: " / filePath);

    size_t lineCount{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        lineCount++;
    }

    file.close();
    return lineCount;
}

size_t CountWords(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open a file with path: " / filePath);

    size_t wordCount{};
    std::string fileLine{};
    while (std::getline(file, fileLine))
    {
        std::stringstream sstream(fileLine);
        std::string word{};
        while (sstream >> word)
        {
            wordCount++;
        }
    }

    file.close();
    return wordCount;
}

size_t CountCharacters(const std::filesystem::path& filePath)
{
    std::wifstream file(filePath);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open())
        throw std::runtime_error("Cannot open a file with path: " / filePath);

    size_t characterCount{};
    wchar_t ch{};
    while (file.get(ch))
    {
        characterCount++;
    }

    file.close();
    return characterCount;
}

void DisplayHelp()
{
    std::cout << "Usage: ccwc [OPTION]... [FILE]..." << '\n'
              << '\n'
              << "The options are as below:" << '\n'
              << "  -c\tprint the byte counts" << '\n'
              << "  -m\tprint the character counts" << '\n'
              << "  -l\tprint the newline counts" << '\n'
              << "  -w\tprint the word counts" << '\n'
              << "      --help\tdisplay this help and exit" << '\n';
}

void PerformOperation(const std::filesystem::path& filePath, char op)
{
    switch (op)
    {
        case 'c':
            std::cout << CountBytes(filePath) << '\n';
            break;
        case 'l':
            std::cout << CountLines(filePath) << '\n';
            break;
        case 'w':
            std::cout << CountWords(filePath) << '\n';
            break;
        case 'm':
            std::cout << CountBytes(filePath) << '\n';
            break;
        default:
            std::cerr << "Invalid option. Use -c, -l, -w or -m." << '\n';
    }
}

bool IsValidOption(const std::string& op)
{
    return (op.length() == 2 && op[0] == '-') ? true : false;
}

int main(int argc, char* argv[])
{
    if (std::string(argv[1])== "--help")
    {
        DisplayHelp();
        return 0;
    }

    if (argc == 2 && std::cin.peek())
    {
        if (!IsValidOption(argv[1]))
        {
            DisplayHelp();
            return 1;
        }

        std::filesystem::path outputPath = "outputFile.txt";
        std::ofstream outputFile(outputPath);
        if (!outputFile.is_open())
            throw std::runtime_error("Could not open file " / outputPath);

        std::string line;            
        while (std::getline(std::cin, line))
        {
            outputFile << line << '\n';
        }

        outputFile.close();        

        PerformOperation(outputPath, argv[1][1]);

        std::filesystem::remove(outputPath);
    }
    else if (argc == 2)
    {
        std::filesystem::path filePath = argv[1];
        try
        {
            size_t lineCount = CountLines(filePath);
            size_t wordCount = CountWords(filePath);
            size_t byteCount = CountBytes(filePath);
            std::cout << lineCount << '\t' << wordCount << '\t' << byteCount << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
    else if (argc == 3)
    {   
        if (!IsValidOption(argv[1]))
        {
            DisplayHelp();
            return 1;
        }

        try
        {
            PerformOperation(argv[2], argv[1][1]);
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
        return 0;
    }

    
}