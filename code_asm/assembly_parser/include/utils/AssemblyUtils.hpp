#pragma once

#ifndef ASSEMBLY_UTILS_HPP
#define ASSEMBLY_UTILS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class AssemblyUtils
{
    private:
        static vector<string> orderedList;
    public:
        static void populateOrderedList();
        static string getImmediate(string number, int bits);
        // The key is the label, the tuple contains its adress and the instruction adress
        static string getLabelAdress(string label, int index, map<string, tuple<string, vector<string>>> labels, int bits);
        static string getRegister(string reg);
        static string getCondition(string condition);
        static bool isSP(vector<string> expression);
        static bool isLoadStore(vector<string> expression);
        static bool isImmediate(vector<string> expression);
        static bool isConditionnal(vector<string> expression); 
        static bool isLabel(vector<string> expression);       
        static string binaryToHex(string binary);
        static string getComplementTo2(int number, int bits);
};

#endif