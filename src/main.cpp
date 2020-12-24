#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

#include "imaging.h"

enum class Commands
{
    Unknown,
    Load,
    Stor,
    Blur,
    Resize,
    Help,
    Quit,
};

const std::unordered_map<std::string, std::pair<Commands, size_t>> g_commands {
    { "load",    { Commands::Load, 2 } },
    { "ld",      { Commands::Load, 2 } },
    { "stor",    { Commands::Stor, 2 } },
    { "s",       { Commands::Stor, 2 } },
    { "blur",    { Commands::Blur, 3 } },
    { "resize",  { Commands::Resize, 4 } },
    { "help",    { Commands::Help, 0 } },
    { "h",       { Commands::Help, 0 } },
    { "exit",    { Commands::Quit, 0 } },
    { "quit",    { Commands::Quit, 0 } },
    { "q",       { Commands::Quit, 0 } }
};

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    result.reserve(5);

    std::istringstream stream(s);
    std::string w;
    while (std::getline(stream, w, delim)) {
        if (!w.empty())
            result.push_back(w);
    }

    return result;
}

std::string getCommand()
{
    std::cout << "> ";
    std::string command;
    std::getline(std::cin, command);

    return command;
}

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); }
    );
    return s;
}

void printHelp()
{
    std::cout << "load, ld <name> <file_name>\tLoading of the JPG image.\n"
              << "stor, s  <name> <file_name>\tStorage of the JPG image.\n"
              << "blur     <from_name> <to_name> <size>\n\t\t\t\tImage smooting.\n"
              << "resize   <from_name> <to_name> <new_width> <new_height>\n"
              << "\t\t\t\tChange of the image size.\n"
              << "help, h\t\t\t\tDisplay this help screen.\n"
              << "exit, quit, q\t\t\tExit.\n";
}

bool checkCommand(Imaging &img, const std::string &command)
{
    std::vector<std::string> words = split(command, ' ');
    if (words.size() < 1)
        return false;

    auto res = g_commands.find(str_tolower(words.front()));
    if (res != std::end(g_commands)) {
        switch (res->second.first) {
            case Commands::Load: {
                if (words.size() - 1 >= res->second.second)
                    return img.load(words[1], words[2]);

                break;
            }
            case Commands::Stor: {
                if (words.size() - 1 >= res->second.second)
                    return img.stor(words[1], words[2]);

                break;
            }
            case Commands::Blur: {
                if (words.size() - 1 >= res->second.second)
                    return img.blur(words[1], words[2], std::stoi(words[3]));

                break;
            }
            case Commands::Resize: {
                if (words.size() - 1 >= res->second.second)
                    return img.resize(words[1],
                                      words[2],
                                      std::stoi(words[3]),
                                      std::stoi(words[4]));

                break;
            }
            case Commands::Help: { printHelp(); return true; }
            case Commands::Quit: exit(0);
            default: break;
        }
    }

    return false;
}

void unitTest();

int main()
{
    //unitTest(); return 0;

    Imaging img;
    while (true)
        checkCommand(img, getCommand());

    return 0;
}

// Для теста нужен файл image1.jpg рядом с исполняемым файлом
void unitTest()
{
    Imaging img;

    if (checkCommand(img, "load img1.jpg")) // Не все параметры
        std::cout << "Test 1 failed\n";
    else
        std::cout << "Test 1 successful\n";

    if (checkCommand(img, "load img imgjpg")) // Не найден файл
        std::cout << "Test 2 failed\n";
    else
        std::cout << "Test 2 successful\n";

    if (!checkCommand(img, "load img1 image1.jpg"))
        std::cout << "Test 3 failed\n";
    else
        std::cout << "Test 3 successful\n";

    if (!checkCommand(img, "blur img1 img2 5"))
        std::cout << "Test 4 failed\n";
    else
        std::cout << "Test 4 successful\n";

    if (!checkCommand(img, "stor img1 image2.jpg"))
        std::cout << "Test 5 failed\n";
    else
        std::cout << "Test 5 successful\n";

    if (!checkCommand(img, "ld img2 image2.jpg"))
        std::cout << "Test 6 failed\n";
    else
        std::cout << "Test 6 successful\n";

    if (!checkCommand(img, "resize img2 img3 1000 800"))
        std::cout << "Test 7 failed\n";
    else
        std::cout << "Test 7 successful\n";

    if (!checkCommand(img, "s img3 image3.jpg"))
        std::cout << "Test 8 failed\n";
    else
        std::cout << "Test 8 successful\n";

    if (!checkCommand(img, "load   img4   image3.jpg")) // Лишние пробелы
        std::cout << "Test 9 failed\n";
    else
        std::cout << "Test 9 successful\n";
}
