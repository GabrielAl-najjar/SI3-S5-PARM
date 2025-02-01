#pragma once

#ifndef ASSEMBLY_FUNCTIONS_HPP
#define ASSEMBLY_FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class AssemblyFunctions
{
    public:
        // Register functions
        static string lsls_imm5(vector<string>);
        static string lsrs_imm5(vector<string>);
        static string asrs_imm5(vector<string>);
        static string adds_register(vector<string>);
        static string subs_register(vector<string>);
        static string adds_imm3(vector<string>);
        static string subs_imm3(vector<string>);
        static string movs_imm8(vector<string>);
        static string cmp_imm8(vector<string>);
        static string adds_imm8(vector<string>);
        static string subs_imm8(vector<string>);
       
        // Data processing functions
        static string ands_register(vector<string>);
        static string eors_register(vector<string>);
        static string lsls_register(vector<string>);
        static string lsrs_register(vector<string>);
        static string asrs_register(vector<string>);
        static string adcs_register(vector<string>);
        static string sbcs_register(vector<string>);
        static string rors_register(vector<string>);
        static string tst_register(vector<string>);
        static string rsbs_register(vector<string>);
        static string cmp_register(vector<string>);
        static string cmn_register(vector<string>);
        static string orrs_register(vector<string>);
        static string muls_register(vector<string>);
        static string bics_register(vector<string>);
        static string mvns_register(vector<string>);

        // Load/store functions
        static string str_reg(vector<string>);
        static string ldr_reg(vector<string>);

        // Miscellaneous functions
        static string add_sp(vector<string>);
        static string sub_sp(vector<string>);

        // Branch functions
        static string bc(vector<string>, map<string, tuple<string, vector<string>>>, int);
        static string b(vector<string>, map<string, tuple<string, vector<string>>>, int);



};

#endif