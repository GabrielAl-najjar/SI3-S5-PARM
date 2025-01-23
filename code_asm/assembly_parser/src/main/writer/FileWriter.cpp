#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <writer/FileWriter.hpp>

using namespace std;

FileWriter::FileWriter(string path)
{
    this->path = path;
}

FileWriter::~FileWriter()
{
    // Vector is declared on stack, automatically deleted
}

void FileWriter::writeToFile(vector<string> linesToWrite)
{
    ofstream file(this->path);
    if(file.is_open())
    {
        string header = "V2.0 raw\n";
        file << header;
        string concat = "";
        for (string line : linesToWrite)
        {
            concat += line + " ";
        }
        
        if(!concat.empty() && concat.back() == ' ')
        {
            concat.pop_back();
        }
        file << concat << endl;
        file.close();
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}