#include "parser/AssemblyParser.hpp"
#include "utils/AssemblyFunctions.hpp"

AssemblyParser::AssemblyParser(vector<string> lines)
{
    instructions["lsls_imm5"] = bind(&AssemblyFunctions::lsls_imm5, placeholders::_1);
    instructions["lsrs_imm5"] = bind(&AssemblyFunctions::lsrs_imm5, placeholders::_1);
    instructions["asrs_imm5"] = bind(&AssemblyFunctions::asrs_imm5, placeholders::_1);
    instructions["adds_register"] = bind(&AssemblyFunctions::adds_register, placeholders::_1);
    instructions["subs_register"] = bind(&AssemblyFunctions::subs_register, placeholders::_1);
    instructions["adds_imm3"] = bind(&AssemblyFunctions::adds_imm3, placeholders::_1);
    instructions["subs_imm3"] = bind(&AssemblyFunctions::subs_imm3, placeholders::_1);
    instructions["movs_imm8"] = bind(&AssemblyFunctions::movs_imm8, placeholders::_1);
    instructions["cmp_imm8"] = bind(&AssemblyFunctions::cmp_imm8, placeholders::_1);
    instructions["adds_imm8"] = bind(&AssemblyFunctions::adds_imm8, placeholders::_1);
    instructions["subs_imm8"] = bind(&AssemblyFunctions::subs_imm8, placeholders::_1);
    instructions["ands_register"] = bind(&AssemblyFunctions::ands_register, placeholders::_1);
    instructions["eors_register"] = bind(&AssemblyFunctions::eors_register, placeholders::_1);
    instructions["lsls_register"] = bind(&AssemblyFunctions::lsls_register, placeholders::_1);
    instructions["lsrs_register"] = bind(&AssemblyFunctions::lsrs_register, placeholders::_1);
    instructions["asrs_register"] = bind(&AssemblyFunctions::asrs_register, placeholders::_1);
    instructions["adcs_register"] = bind(&AssemblyFunctions::adcs_register, placeholders::_1);
    instructions["sbcs_register"] = bind(&AssemblyFunctions::sbcs_register, placeholders::_1);
    instructions["rors_register"] = bind(&AssemblyFunctions::rors_register, placeholders::_1);
    instructions["tst_register"] = bind(&AssemblyFunctions::tst_register, placeholders::_1);
    instructions["rsbs_register"] = bind(&AssemblyFunctions::rsbs_register, placeholders::_1);
    instructions["cmp_register"] = bind(&AssemblyFunctions::cmp_register, placeholders::_1);
    instructions["cmn_register"] = bind(&AssemblyFunctions::cmn_register, placeholders::_1);
    instructions["orrs_register"] = bind(&AssemblyFunctions::orrs_register, placeholders::_1);
    instructions["muls_register"] = bind(&AssemblyFunctions::muls_register, placeholders::_1);
    instructions["bics_register"] = bind(&AssemblyFunctions::bics_register, placeholders::_1);
    instructions["mvns_register"] = bind(&AssemblyFunctions::mvns_register, placeholders::_1);
    instructions["str_reg"] = bind(&AssemblyFunctions::str_reg, placeholders::_1);
    instructions["ldr_reg"] = bind(&AssemblyFunctions::ldr_reg, placeholders::_1);
    instructions["add_sp"] = bind(&AssemblyFunctions::add_sp, placeholders::_1);
    instructions["sub_sp"] = bind(&AssemblyFunctions::sub_sp, placeholders::_1);
    branchInstructions["bc"] = bind(&AssemblyFunctions::bc, placeholders::_1, placeholders::_2);
    branchInstructions["b"] = bind(&AssemblyFunctions::b, placeholders::_1, placeholders::_2);
}

AssemblyParser::~AssemblyParser()
{
}


vector<string> AssemblyParser::splitExpression(string expression)
{
    vector<string> result;
    string delimiter = " ";
    size_t pos = 0;
    string token;
    while ((pos = expression.find(delimiter)) != string::npos) {
        token = expression.substr(0, pos);
        result.push_back(token);
        expression.erase(0, pos + delimiter.length());
    }
    result.push_back(expression);
    return result;
}

map<string, tuple<string, string>> AssemblyParser::getLabelsToAdress()
{
    return labelsToAdress;
}
string AssemblyParser::getBranchInstruction(string instruction, vector<string> expression, int index)
{
    if(branchInstructions.find(instruction) == branchInstructions.end())
    {
        cerr << "Error : instruction " << instruction << " not found" << endl;
        throw runtime_error("Instruction not found");
    }
    return branchInstructions[instruction](expression, index);
}

string AssemblyParser::getInstruction(string instruction, vector<string> expression)
{
    if(instructions.find(instruction) == instructions.end())
    {
        cerr << "Error : instruction " << instruction << " not found" << endl;
        throw runtime_error("Instruction not found");
    }
    return instructions[instruction](expression);
}