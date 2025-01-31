#include <utils/AssemblyUtils.hpp>
#include <string>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

vector<string> AssemblyUtils::orderedList;
void lowerCase(string&);
string getComplementTo2(string);

void AssemblyUtils::populateOrderedList()
{
    orderedList.push_back("eq");
    orderedList.push_back("ne");
    orderedList.push_back("cs");
    orderedList.push_back("cc");
    orderedList.push_back("mi");
    orderedList.push_back("pl");
    orderedList.push_back("vs");
    orderedList.push_back("vc");
    orderedList.push_back("hi");
    orderedList.push_back("ls");
    orderedList.push_back("ge");
    orderedList.push_back("lt");
    orderedList.push_back("gt");
    orderedList.push_back("le");
    orderedList.push_back("al");
}

string trim(string str)
{
    string result = "";
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ' && str[i] != '\t')
        {
            result += str[i];
        }
    }
    return result;
}

string AssemblyUtils::getImmediate(string number, int bits)
{
    string result = "";
    if(number[0] == '#')
    {
        number = number.substr(1, number.length() - 1);
    }
    int nb = atoi(number.c_str());
    while(nb > 0)
    {
        result = to_string(nb%2) + result;
        nb = nb/2;
    }
    while(result.length() < bits)
    {
        result = "0" + result;
    }
    return result;
}

string AssemblyUtils::getCondition(string condition)
{
    string c = condition.substr(1, condition.length() - 1);
    lowerCase(c);
    for(int i = 0; i < orderedList.size(); i++)
    {
        if(orderedList.at(i) == c)
        {
            return getImmediate(to_string(i), 4);
        }
    }
    throw new runtime_error("Condition not found");
}

string AssemblyUtils::getLabelAdress(string label, int index, map<string, tuple<string, vector<string>>> labelsToAdress, int bits)
{
    // Procedure : 
    // 1. Get the label adress from the map
    // 2. Subract the current instruction adress
    // 3. Substract 3
    // 4. Convert the result to BINARY COMPLEMENT TWO
    string labelAdress = get<0>(labelsToAdress[label]);
    string instructionAdress = get<1>(labelsToAdress[label]).at(index);
    int labelAdressInt = atoi(labelAdress.c_str());
    int instructionAdressInt = atoi(instructionAdress.c_str());
    int result = labelAdressInt - instructionAdressInt - 3;
    return getComplementTo2(result, bits);
}

string AssemblyUtils::getRegister(string reg)
{
    if(reg[0] == 'r' && reg.length() == 2)
    {
        if(reg[1] >= '0' && reg[1] <= '7')
        {
            return getImmediate(reg.substr(1, 1), 3);
        }
    }
    return "000";
}

bool AssemblyUtils::isSP(vector<string> expression)
{
    return expression.at(1) == "sp";
}

bool AssemblyUtils::isLoadStore(vector<string> expression)
{
    return expression.at(0) == "ldr" || expression.at(0) == "str";
}

bool AssemblyUtils::isImmediate(vector<string> expression)
{
    if (!expression.empty() && expression[0] == "rsbs") {
        return false;
    }

    for (const string& token : expression) {
        if (token.substr(0, 1) == "#") {
            return true;
        }
    }
    return false;
}

bool AssemblyUtils::isConditionnal(vector<string> expression)
{
    return expression.at(0).at(0) == 'b' && expression.at(0) != "bics";
}

bool AssemblyUtils::isLabel(vector<string> expression)
{
    return expression.at(0).at(expression.at(0).length() - 1) == ':';
}

string AssemblyUtils::binaryToHex(string binary)
{
    binary = trim(binary);
    string result = "";
    vector<string> splitString;
    for(int i = 0; i < binary.length(); i+=4)
    {
        splitString.push_back(binary.substr(i, 4));
    }
    for(int i = 0; i < splitString.size(); i++)
    {
        int value = 0;
        for(int j = 0; j < splitString[i].length(); j++)
        {
            value += (splitString[i][j] - '0') * pow(2, 3-j);
        }
        if(value < 10)
        {
            result += to_string(value);
        }
        else
        {
            result += (char)('a' + value - 10);
        }
    }
    return result;
}

void lowerCase(string &str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

string AssemblyUtils::getComplementTo2(int number, int bits)
{
    if(number < 0)
    {
        string result = "1";
        string binary = getImmediate(to_string(abs(number)), bits);

        // Complement to 1
       
        for(int i = 1; i < binary.length(); i++)
        {
            if(binary[i] == '0')
            {
                result += "1";
            }
            else
            {
                result += "0";
            }
        }

        // Complement to 2
        int carry = 1;
        for(int i = result.length() - 1; i >= 0; i--)
        {
            if(result[i] == '1' && carry == 1)
            {
                result[i] = '0';
            }
            else if(result[i] == '0' && carry == 1)
            {
                result[i] = '1';
                carry = 0;
            }
        }
        return result;

    }
    else
    {
        return getImmediate(to_string(number), bits);
    }
}