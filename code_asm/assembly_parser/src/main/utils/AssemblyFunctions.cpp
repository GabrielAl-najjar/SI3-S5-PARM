#include <utils/AssemblyFunctions.hpp>
#include <utils/AssemblyUtils.hpp>
#include <string>
#include <map>
#include <tuple>

using namespace std;

map<string, tuple<string, string>> AssemblyFunctions::labelsToAdress;

map<string, tuple<string, string>> AssemblyFunctions::getLabelsToAdress()
{
    return AssemblyFunctions::labelsToAdress;
}

void AssemblyFunctions::setLabelsToAdress(map<string, tuple<string, string>> labels)
{
    AssemblyFunctions::labelsToAdress = labels;
}

string AssemblyFunctions::lsls_imm5(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string imm5 = AssemblyUtils::getImmediate(expression[3], 5);
    return "00000" + imm5 + rn + rd;
}

string AssemblyFunctions::lsrs_imm5(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string imm5 = AssemblyUtils::getImmediate(expression[3], 5);
    return "00001" + imm5 + rn + rd;
}

string AssemblyFunctions::asrs_imm5(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string imm5 = AssemblyUtils::getImmediate(expression[3], 5);
    return "00010" + imm5 + rn + rd;
}

string AssemblyFunctions::adds_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string rm = AssemblyUtils::getRegister(expression[3]);
    return "0001100" + rm + rn + rd;
}

string AssemblyFunctions::subs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string rm = AssemblyUtils::getRegister(expression[3]);
    return "0001101" + rm + rn + rd;
}

string AssemblyFunctions::adds_imm3(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string imm3 = AssemblyUtils::getImmediate(expression[3], 3);
    return "0001110" + imm3 + rn + rd;
}

string AssemblyFunctions::subs_imm3(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    string imm3 = AssemblyUtils::getImmediate(expression[3], 3);
    return "0001111" + imm3 + rn + rd;
}

string AssemblyFunctions::movs_imm8(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(expression[2], 8);
    return "00100" + rd + imm8;
}

string AssemblyFunctions::cmp_imm8(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(expression[2], 8);
    return "00101" + rd + imm8;
}

string AssemblyFunctions::adds_imm8(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(expression[2], 8);
    return "00110" + rd + imm8;
}

string AssemblyFunctions::subs_imm8(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(expression[2], 8);
    return "00111" + rd + imm8;
}

string AssemblyFunctions::ands_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000000" + rm + rd;
}

string AssemblyFunctions::eors_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000001" + rm + rd;
}

string AssemblyFunctions::lsls_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000010" + rm + rd;
}

string AssemblyFunctions::lsrs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000011" + rm + rd;
}

string AssemblyFunctions::asrs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000100" + rm + rd;
}

string AssemblyFunctions::adcs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000101" + rm + rd;
}

string AssemblyFunctions::sbcs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000110" + rm + rd;
}

string AssemblyFunctions::rors_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100000111" + rm + rd;
}

string AssemblyFunctions::tst_register(vector<string> expression)
{
    string rn = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001000" + rm + rn;
}

string AssemblyFunctions::rsbs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rn = AssemblyUtils::getRegister(expression[2]);
    return "0100001001" + rn + rd;
}

string AssemblyFunctions::cmp_register(vector<string> expression)
{
    string rn = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001010" + rm + rn;
}

string AssemblyFunctions::cmn_register(vector<string> expression)
{
    string rn = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001011" + rm + rn;
}

string AssemblyFunctions::orrs_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001100" + rm + rd;
}

string AssemblyFunctions::muls_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001101" + rm + rd;
}

string AssemblyFunctions::bics_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001110" + rm + rd;
}

string AssemblyFunctions::mvns_register(vector<string> expression)
{
    string rd = AssemblyUtils::getRegister(expression[1]);
    string rm = AssemblyUtils::getRegister(expression[2]);
    return "0100001111" + rm + rd;
}

string AssemblyFunctions::str_reg(vector<string> expression)
{
    int offset = stoi(expression[3].substr(1,1)) / 4;
    string rt = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(to_string(offset), 8);
    return "10010" + rt + imm8;
}

string AssemblyFunctions::ldr_reg(vector<string> expression)
{
    int offset = stoi(expression[3].substr(1,1)) / 4;
    string rt = AssemblyUtils::getRegister(expression[1]);
    string imm8 = AssemblyUtils::getImmediate(to_string(offset), 8);
    return "10011" + rt + imm8;
}

string AssemblyFunctions::add_sp(vector<string> expression)
{
    int offset = stoi(expression[2].substr(1,3)) / 4;
    string imm7 = AssemblyUtils::getImmediate(to_string(offset), 7);
    return "101100000" + imm7;
}

string AssemblyFunctions::sub_sp(vector<string> expression)
{
    int offset = stoi(expression[2].substr(1,3)) / 4;
    string imm7 = AssemblyUtils::getImmediate(to_string(offset), 7);
    return "101100001" + imm7;
}

string AssemblyFunctions::bc(vector<string> expression)
{
    string condition = AssemblyUtils::getCondition(expression[0]);
    string imm8 = AssemblyUtils::getLabelAdress(expression[1], AssemblyFunctions::getLabelsToAdress(), 8);
    cout << imm8 << endl;
    return "1101" + condition + imm8;
}

string AssemblyFunctions::b(vector<string> expression)
{
    string imm11 = AssemblyUtils::getLabelAdress(expression[1], AssemblyFunctions::getLabelsToAdress(), 11);
    return "11100" + imm11;
}