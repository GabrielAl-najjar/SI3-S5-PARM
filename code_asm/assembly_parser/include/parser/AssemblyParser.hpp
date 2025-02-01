#pragma once

#ifndef ASSEMBLY_PARSER_HPP
#define ASSEMBLY_PARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <functional>

using namespace std;

class AssemblyParser
{
    private:
        map<string, function<string(vector<string>)>> instructions;
        map<string, function<string(vector<string>, map<string, tuple<string, vector<string>>>, int)>> branchInstructions;
    public:
        AssemblyParser(vector<string> lines);
        ~AssemblyParser();
        vector<string> splitExpression(string expression);
        string getBranchInstruction(string instruction, vector<string> expression, map<string, tuple<string, vector<string>>> labels, int index);
        string getInstruction(string instruction, vector<string> expression);        
};

#endif