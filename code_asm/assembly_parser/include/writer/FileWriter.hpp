#pragma once

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <iostream>
#include <vector>

using namespace std;

class FileWriter
{
    private:
        string path;
    public:
        FileWriter(string path);
        ~FileWriter();
        void writeToFile(vector<string> linesToWrite);
};

#endif