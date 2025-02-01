#include <iostream>

#include <parser/FileParser.hpp>
#include <parser/AssemblyParser.hpp>
#include <writer/FileWriter.hpp>
#include <utils/AssemblyUtils.hpp>
#include <utils/AssemblyFunctions.hpp>

using namespace std;
string getWhichImmediate(vector<string> expression);
int main(int argc, char **argv) 
{
    if(argc < 2) 
    {
        cout << "Usage: " << argv[0] << " <file>" << endl;
        return 1;
    }
    string filename = argv[1];
    if(FILE *file = fopen(filename.c_str(), "r")) 
    {
        FileParser *parser = new FileParser(file);
        filename = filename.substr(filename.find_last_of("/") + 1, 
            filename.find_last_of(".") - filename.find_last_of("/") - 1);     
        
        FileWriter *writer = new FileWriter("./"+ filename + ".bin");

        
        vector<string> lines = parser->parseImportantLines();
        lines = parser->trim(lines);
        
        AssemblyUtils::populateOrderedList();
        AssemblyParser *assemblyParser = new AssemblyParser(lines);
        
        vector<vector<string>> instructions;
        for(int i = 0; i < lines.size(); i++)
        {
            vector<string> expression = assemblyParser->splitExpression(lines.at(i));
            if(!AssemblyUtils::isLabel(expression))
                instructions.push_back(expression);
        }
        vector<string> linesToWrite;
        for(auto &label : parser->getLabelsToAdress())
        {
            string key = label.first;
            string adress = get<0>(label.second);
            vector<string> calls = get<1>(label.second);
        }
        map<string, int> labelsAdresses;
        for(int i = 0; i < instructions.size(); i++)
        {
            vector<string> expression = instructions.at(i);
            string instruction = expression.at(0);
            if(AssemblyUtils::isConditionnal(expression))
            {
                if(instruction == "b")
                {
                    instruction = "b";
                }
                else
                {
                    instruction = "bc";
                }
            }
            else if(AssemblyUtils::isSP(expression))
            {
                instruction += "_sp";
            }
            else if(AssemblyUtils::isLoadStore(expression))
            {
                instruction += "_reg";
            }
            else if(AssemblyUtils::isImmediate(expression))
            {
                instruction += "_imm" + getWhichImmediate(expression);
            }
            else
            {
                instruction += "_register";
            }
            if(instruction == "b" || instruction == "bc")
            {
                if(labelsAdresses.find(expression.at(1)) == labelsAdresses.end())
                {
                    labelsAdresses[expression.at(1)] = 0;
                }
                else
                {
                    labelsAdresses[expression.at(1)]++;
                }
                string binary = assemblyParser->getBranchInstruction(instruction, expression, parser->getLabelsToAdress(), labelsAdresses[expression.at(1)]);
                string hex = AssemblyUtils::binaryToHex(binary);
                linesToWrite.push_back(hex);
                continue;
            }
            string binary = assemblyParser->getInstruction(instruction, expression);
            string hex = AssemblyUtils::binaryToHex(binary);
            linesToWrite.push_back(hex);
        }

        writer->writeToFile(linesToWrite);

        delete parser;
        delete writer;
        delete assemblyParser;
    } 
    else 
    {
        cout << "Error opening file" << endl;
    }

    return 0;
}

string getWhichImmediate(vector<string> expression)
{
    if(expression.at(0) == "lsls" || expression.at(0) == "lsrs" || expression.at(0) == "asrs")
    {
        return "5";
    }
    else if(expression.at(0) == "adds" || expression.at(0) == "subs")
    {
        if(expression.size() == 4)
        {
            return "3";
        }
        else if(expression.size() == 3)
        {
            return "8";
        }
    }
    return "8";
}