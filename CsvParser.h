#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
namespace caf
{
class CsvParser
{
  private:
    std::string inFile;
    std::ifstream inStream;

    std::vector<std::string> GetFileLines(int);

    std::vector<std::vector<std::string>>
        TokenizeFileLines(std::vector<std::string>);

  public:
    CsvParser(std::string);
    ~CsvParser();
    std::vector<std::vector<std::string>> ParseCsv(int);
    void CloseParser();
    void SetInputFile(std::string);
    bool MoreLinesToParse();
};

CsvParser::CsvParser(std::string inFile)
{
    this->inStream = std::ifstream(inFile);
}

CsvParser::~CsvParser()
{
    if (this->inStream.is_open())
        this->inStream.close();
}

bool CsvParser::MoreLinesToParse()
{
    if (this->inStream.good() && !this->inStream.eof())
    {
        return true;
    }
    return false;
}

void CsvParser::CloseParser()
{
    this->inFile = "";
    this->inStream.close();
}

// Close the old stream if it's open, then create a new input stream using the
//  passed file name and reassign the tracked file name.
void CsvParser::SetInputFile(std::string fileName)
{
    if (this->inStream.is_open())
    {
        this->inStream.close();
    }

    this->inFile = fileName;
    this->inStream = std::ifstream(fileName);
}

std::vector<std::string>
CsvParser::GetFileLines(int numLines)
{
    // Read numLines lines from the input stream into the vector.
    std::string currLine;
    std::vector<std::string> allLines;
    for (int i = 0; std::getline(this->inStream, currLine) && i < numLines; ++i)
    {
        allLines.push_back(currLine);
    }

    return allLines;
}

std::vector<std::vector<std::string>>
CsvParser::TokenizeFileLines(std::vector<std::string> fileLines)
{
    std::vector<std::vector<std::string>> rows;

    // Parse each line into a row containing an index for each column.
    std::string token;
    for (int i = 0; i < fileLines.size(); ++i)
    {
        // Add a new row to hold tokens.
        rows.push_back(std::vector<std::string>());

        // Use std::getline to parse the line by commas.
        std::string line = fileLines[i];
        auto lineStream = std::stringstream(line);
        while (std::getline(lineStream, token, ','))
        {
            rows[i].push_back(token);
        }
    }

    return rows;
}

// Parse up to 1000 lines at a time and return a vector with the lines.
// By default, parse up to 100 lines.
std::vector<std::vector<std::string>> CsvParser::ParseCsv(int numLines = 100)
{
    // Handle input checking.
    if (numLines > 1000 || numLines < 0)
    {
        numLines = 100;
    }

    std::vector<std::string> fileLines = this->GetFileLines(numLines);
    return this->TokenizeFileLines(fileLines);
}
};
