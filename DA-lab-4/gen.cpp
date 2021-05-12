#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <exception>

    // Chance of adding key
const unsigned int KEY_ADD_CHANCE = 5;
    // Chance of adding newline
const unsigned int NEWLINE_ADD_CHANCE = 30;

void ToLower(std::string& str) {
    for (char& c : str) {
        c = std::tolower(c);
    }
}

std::vector<std::string> LineToVec()
{
    std::string line;
    std::getline(std::cin, line);    

    std::vector<std::string> vec;
    std::istringstream sstream(line);
    while(sstream >> line)
    {
        ToLower(line);
        vec.push_back(line);
    }

    return vec;
}

int main(int argc, char* argv[])
{
    std::srand(255034);

    std::cout << "Key: ";
    const std::vector<std::string> key = LineToVec();
    std::cout << "Filler words: ";
    std::vector<std::string> words = LineToVec();
    std::cout << "Text size: ";
    unsigned int textSize;
    std::cin  >> textSize;
    
        // Add key words to filler words
    for (int i = 0; i < key.size() - 1; ++i)
    {
        words.push_back(key[i]);
    }
        // Don't include the last word for more control
    
        // Open files
    std::fstream text, lineNums;
    switch (argc)
    {
    case 1:
        text.open("Text.txt", std::fstream::out);
        lineNums.open("LineNums.txt", std::fstream::out);
        break;
    case 2:
        text.open(argv[1], std::fstream::out);
        lineNums.open("LineNums.txt", std::fstream::out);
        break;
    case 3:
        text.open(argv[1], std::fstream::out);
        lineNums.open(argv[2], std::fstream::out);
        break;

    default:
        throw std::runtime_error("Wrong number of arguments");
        break;
    }

    if (!text.is_open() || !lineNums.is_open()) throw std::runtime_error("Failed to open file");

        // Add key in the first line
    for (int i = 0; i < key.size(); ++i)
    {
        text << key[i] << ' ';
    }
    text << '\n';

        // Generate text
    unsigned int wordNum = 0, lineNum = 1;
    // std::string lastWord ("___");
    // int shortLived;
    for (int wordsPrinted = 0; wordsPrinted < textSize; )
    {
        if ((std::rand() % 100 + 1) > KEY_ADD_CHANCE)
        { // Add random word
            while ((std::rand() % 100 + 1) <= NEWLINE_ADD_CHANCE)
            {
                text << '\n';
                ++lineNum;
                wordNum = 0;
            }
            ++wordNum;
            ++wordsPrinted;
            text << words[std::rand() % words.size()] << ' ';
        }
        else
        {
            ++wordNum;
            ++wordsPrinted;
            lineNums << lineNum << ", " << wordNum << '\n';
            text << key[0] << ' ';

            for (int i = 1; i < key.size(); ++i)
            {
                while ((std::rand() % 100 + 1) <= NEWLINE_ADD_CHANCE)
                {
                    text << '\n';
                    ++lineNum;
                    wordNum = 0;
                }
 
                ++wordNum;
                ++wordsPrinted;
                text << key[i] << ' ';
            }
        }
        
    }    

    text.close();
    lineNums.close();
}