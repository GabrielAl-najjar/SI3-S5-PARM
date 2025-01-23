#pragma once 

#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class FileParser
{
    private:
        FILE *file;
        map<string, tuple<string, string>> labelsToAdress;
    public:
        FileParser(FILE *file);
        ~FileParser();
        vector<string> parseImportantLines(); 
        vector<string> trim(vector<string> lines);
        map<string, tuple<string, string>> getLabelsToAdress();
};

#endif