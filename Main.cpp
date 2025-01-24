#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

size_t CountBytes(const std::filesystem::path& filePath) { return std::filesystem::file_size(filePath); }

size_t CountLines(std::wifstream& file)
{
    size_t lineCount{};
    std::wstring fileLine{};
    file.clear();
    file.seekg(0, std::ios::beg);
    while (std::getline(file, fileLine))
    {
        lineCount++;
    }
    return lineCount;
}

size_t CountWords(std::wifstream& file)
{
    size_t wordCount{};
    std::wstring fileLine{};
    file.clear();
    file.seekg(0, std::ios::beg);
    while (std::getline(file, fileLine))
    {
        std::wstringstream sstream(fileLine);
        std::wstring word{};
        while (sstream >> word)
        {
            wordCount++;
        }
    }
    return wordCount;
}

size_t CountCharacters(std::wifstream& file)
{
    size_t characterCount{};
    wchar_t ch{};
    file.clear();
    file.seekg(0, std::ios::beg);
    while (file.get(ch))
    {
        characterCount++;
    }
    return characterCount;
}

void DisplayHelp()
{
    std::cout << "Usage: ccwc [OPTION]... [FILE]..." << '\n'
              << '\n'
              << "The options are:" << '\n'
              << "  -c\tprint the byte counts" << '\n'
              << "  -m\tprint the character counts" << '\n'
              << "  -l\tprint the newline counts" << '\n'
              << "  -w\tprint the word counts" << '\n'
              << "  --help\tdisplay this help and exit" << '\n';
}

bool IsValidOption(const std::string& op) { return (op.length() == 2 && op[0] == '-') ? true : false; }

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        DisplayHelp();
        return 1;
    }

    if (std::string(argv[1]) == "--help")
    {
        DisplayHelp();
        return 0;
    }

    if (argc == 2 && std::filesystem::exists(argv[1]))
    {
        std::filesystem::path inputFilePath = argv[1];
        std::wifstream inputFile(inputFilePath);
        inputFile.imbue(std::locale(inputFile.getloc(), new std::codecvt_utf8<wchar_t>));

        if (!inputFile.is_open())
            std::cerr << "Could not open file " << inputFilePath.string() << '\n';

        size_t lineCount = CountLines(inputFile);
        size_t wordCount = CountWords(inputFile);

        std::cout << lineCount << "  " << wordCount << "  " << CountBytes(inputFilePath) << '\n';
        inputFile.close();
    }
    else if (argc == 2 && std::cin.peek() != std::istream::traits_type::eof())
    {
        if (!IsValidOption(argv[1]))
        {
            DisplayHelp();
            return 1;
        }

        std::filesystem::path outputFilePath = "outputFile.txt";
        std::ofstream outputFile(outputFilePath);
        if (!outputFile.is_open())
            std::cerr << "Could not open file " << outputFilePath.string() << '\n';

        std::string line;
        while (std::getline(std::cin, line))
        {
            outputFile << line << '\n';
        }
        outputFile.close();

        std::wifstream inputFile(outputFilePath);
        inputFile.imbue(std::locale(inputFile.getloc(), new std::codecvt_utf8<wchar_t>));
        if (!inputFile.is_open())
            std::cerr << "Could not open file " << outputFilePath.string() << '\n';

        std::string option = argv[1];
        switch (option.at(1))
        {
        case 'c':
            std::cout << CountBytes(outputFilePath) << '\n';
            break;
        case 'l':
            std::cout << CountLines(inputFile) << '\n';
            break;
        case 'w':
            std::cout << CountWords(inputFile) << '\n';
            break;
        case 'm':
            std::cout << CountCharacters(inputFile) << '\n';
            break;
        default:
            std::cerr << "Invalid option. Use -c, -l, -w or -m." << '\n';
        }
        std::filesystem::remove(outputFilePath);
    }
    else if (argc == 3)
    {
        if (!IsValidOption(argv[1]))
        {
            DisplayHelp();
            return 1;
        }

        std::filesystem::path inputFilePath = argv[2];
        std::wifstream inputFile(inputFilePath);
        inputFile.imbue(std::locale(inputFile.getloc(), new std::codecvt_utf8<wchar_t>));

        if (!inputFile.is_open())
            std::cerr << "Could not open file " << inputFilePath.string() << '\n';

        std::string option = argv[1];
        switch (option.at(1))
        {
        case 'c':
            std::cout << CountBytes(inputFilePath) << '\n';
            break;
        case 'l':
            std::cout << CountLines(inputFile) << '\n';
            break;
        case 'w':
            std::cout << CountWords(inputFile) << '\n';
            break;
        case 'm':
            std::cout << CountCharacters(inputFile) << '\n';
            break;
        default:
            std::cerr << "Invalid option. Use -c, -l, -w or -m." << '\n';
        }
        inputFile.close();
    }
    else
    {
        DisplayHelp();
        return 1;
    }
}