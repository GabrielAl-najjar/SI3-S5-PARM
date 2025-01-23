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

        if(strLine.find("run:") != string::npos || strLine.find("data:") != string::npos || strLine.find("text:") != string::npos)
        {
            break;
        }

        // Remove new line character
        strLine.erase(remove(strLine.begin(), strLine.end(), '\n'), strLine.end());

        // Check if the line contains a label
        if (strLine.find(':') != string::npos)
        {
            lines.push_back(strLine);
            string key = strLine.substr(0, strLine.find(":"));
            key.erase(remove(key.begin(), key.end(), '\r'), key.end());
            
            if(labelsToAdress.find(key) == labelsToAdress.end())
            {
                // Left is the declaration adress, right is the declaration adress
                labelsToAdress[key] = make_tuple("", to_string(instructionIndex));
            }
            else
            {
                get<1>(labelsToAdress[key]) = to_string(instructionIndex);
            }
        }
        // Check if the line contains an instruction (not a label)
        else if (strLine.find(' ') != string::npos  // space is for instructions
            && strLine.find("push") == string::npos // we don't need push
            && strLine.find("pop") == string::npos // we don't need pop
            && strLine.find('@') == string::npos) // @ is for comments, they often contain spaces too                                              
        {                                            // so we need to filter them out
            lines.push_back(strLine);

            if(strLine.find(".") != string::npos && strLine.find(":") == string::npos)
            {
                string key = strLine.substr(strLine.find("."), strLine.find(" ") - strLine.find("."));
                key.erase(remove(key.begin(), key.end(), '\r'), key.end());
                
                if(labelsToAdress.find(key) == labelsToAdress.end())
                {
                    // Left is the declaration adress, right is the call adress
                    labelsToAdress[key] = make_tuple(to_string(instructionIndex), "");
                }
                else
                {
                    get<0>(labelsToAdress[key]) = to_string(instructionIndex);
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
        size_t start = line.find_first_not_of(" \t\n\r");
        if(start == string::npos)
        {
            continue;
        }

        size_t last = line.find_last_not_of(" \t\n\r");
        string trimmedLine = line.substr(start, last - start + 1);

        // The case of brackets being next to commas    
        size_t pos = 0;
        while ((pos = trimmedLine.find(',', pos)) != string::npos)
        {
            if (trimmedLine.find('[', pos) != string::npos)
            {
                trimmedLine.replace(pos, 1, " ");
                pos += 1;
            }
            else
            {
                trimmedLine.replace(pos, 1, "");
            }
        }

        trimmedLine.erase(remove(trimmedLine.begin(), trimmedLine.end(), '['), trimmedLine.end());
        trimmedLine.erase(remove(trimmedLine.begin(), trimmedLine.end(), ']'), trimmedLine.end());
        trimmedLine = regex_replace(trimmedLine, regex(" +"), " ");

        trimmedLines.push_back(trimmedLine);
    }
    return trimmedLines;
}

map<string, tuple<string, string>> FileParser::getLabelsToAdress()
{
    return this->labelsToAdress;
}
