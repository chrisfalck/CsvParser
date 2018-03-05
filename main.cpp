#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "CsvParser.h"

int main()
{
    caf::CsvParser parser("TestFiles/TestInventorySmall.csv");

    std::vector<std::vector<std::string>> rows = parser.ParseCsv();

    for (std::vector<std::string> row : rows)
    {
        for (std::string token : row)
        {
            std::cout << std::left << std::setw(20);
            std::cout << token;
        }
        std::cout << std::endl;
    }

    parser.CloseParser();
}