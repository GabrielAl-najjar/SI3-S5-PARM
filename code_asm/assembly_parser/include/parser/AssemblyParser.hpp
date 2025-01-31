#pragma once

#ifndef ASSEMBLY_PARSER_HPP
#define ASSEMBLY_PARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>

using namespace std;

class AssemblyParser
{
    private:
        map<string, function<string(vector<string>)>> instructions;
        map<string, function<string(vector<string>, int)>> branchInstructions;
        map<string, tuple<string, string>> labelsToAdress;
        void parseLabels(vector<string> lines, vector<string> startLabelsAdresses,vector<string> instructionsAdresses);
    public:
        AssemblyParser(vector<string> lines);
        ~AssemblyParser();
        vector<string> splitExpression(string expression);
        map<string, tuple<string, string>> getLabelsToAdress();
        string getBranchInstruction(string instruction, vector<string> expression, int index);
        string getInstruction(string instruction, vector<string> expression);
        
};

#endif