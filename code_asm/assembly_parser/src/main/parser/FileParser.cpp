#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <string>
#include <cstdio>
#include <algorithm>
#include <regex>

#include "parser/FileParser.hpp"

using namespace std;

FileParser::FileParser(FILE *file)
{
    this->file = file;
}

FileParser::~FileParser()
{
    fclose(this->file);
}

vector<string> FileParser::parseImportantLines()
{
    vector<string> lines;
    char line[256];
    int lineIndex = 0;
    int instructionIndex = 1;

    while (fgets(line, sizeof(line), this->file))
    {
        string strLine = line;
        strLine = regex_replace(strLine, regex("^\\s+"), "");
        
        if(strLine.find(".") != string::npos && strLine.at(0) != 'b' && strLine.find(":") == string::npos)
        {
            continue;
        }
        if(strLine.find("run:") != string::npos || strLine.find("data:") != string::npos || strLine.find("text") != string::npos)
        {
            continue;
        }

        // Remove new line character
        strLine.erase(remove(strLine.begin(), strLine.end(), '\n'), strLine.end());
        // Check if the line contains a label
        if (regex_search(strLine, regex(":")))
        {
            lines.push_back(strLine);
            string key = strLine.substr(0, strLine.find(":"));
            key.erase(remove(key.begin(), key.end(), '\r'), key.end());
            
            if(labelsToAdress.find(key) == labelsToAdress.end())
            {
                // Left is the declaration address, right is the vector of call addresses
                labelsToAdress[key] = make_tuple(to_string(instructionIndex), vector<string>{});
            }
            else
            {
                get<0>(labelsToAdress[key]) = to_string(instructionIndex);
            }
        }
        // Check if the line contains an instruction (not a label)
        else if (regex_search(strLine, regex("\\s+"))  // space is for instructions
            && !regex_search(strLine, regex("push"))// we don't need push
            && !regex_search(strLine, regex("pop"))// we don't need pop
            && !regex_search(strLine, regex("@"))) // @ is for comments, they often contain spaces too                                              
        {                                  // so we need to filter them out
            lines.push_back(strLine);

            if(strLine.find(".") != string::npos && strLine.find(":") == string::npos)
            {
                string key = strLine.substr(strLine.find("."), strLine.find(" ") - strLine.find("."));
                key.erase(remove(key.begin(), key.end(), '\r'), key.end());
                if(labelsToAdress.find(key) == labelsToAdress.end())
                {
                    // Left is the declaration address, right is the vector of call addresses
                    labelsToAdress[key] = make_tuple("", vector<string>{to_string(instructionIndex)});
                }
                else
                {
                    get<1>(labelsToAdress[key]).push_back(to_string(instructionIndex));
                }
            }
            instructionIndex++;
        }
        lineIndex++;
    }
    return lines;
}

vector<string> FileParser::trim(vector<string> lines)
{
    vector<string> trimmedLines;
    for(string &line : lines)
    {        
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");

        line = regex_replace(line, regex(",(?=\\[)"), " ");
        line = regex_replace(line, regex(","), "");

        line = regex_replace(line, regex("[\\[\\]]"), "");

        line = regex_replace(line, regex("\\s+"), " ");
        if(!line.empty())
            trimmedLines.push_back(line);
    }
    return trimmedLines;
}

map<string, tuple<string, vector<string>>> FileParser::getLabelsToAdress()
{
    return this->labelsToAdress;
}