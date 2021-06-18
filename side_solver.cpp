#include<vector>
#include<fstream>
#include<string>
#include<unordered_map>
#include"z3++.h"

using namespace z3;

context c;
solver s(c);
std::unordered_map<std::string, unsigned> var_map;

bool ReadFromFile(std::vector<std::string> &vecOfStrs, const std::string &file_name)
{
    std::ifstream in(file_name);
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<file_name<<std::endl;
        return false;
    }
    std::string str;
    while(std::getline(in, str))
    {
        if(str.size() > 0)
            vecOfStrs.push_back(str);

    }
    in.close();
    return true;
}

void Initialize_var(std::string &var)
{
    std::istringstream iss(var);
    std::string var_name;
    std::string var_type;
    iss >> var_name;
    iss >> var_type;

    if(var_type == "bool")
        var_map[var_name] = Z3_get_ast_id(c, c.bool_const(var_name.c_str()));
    else if (var_type == "int")
        var_map[var_name] = Z3_get_ast_id(c, c.int_const(var_name.c_str()));
    else if (var_type == "real")
        var_map[var_name] = Z3_get_ast_id(c, c.real_const(var_name.c_str()));
}

int main()
{
        std::vector<std::string> vecOfStrs;
        bool result = ReadFromFile(vecOfStrs, "cpp_files/var.txt");
        if (result)
        {
            for (std::vector<std::string>::iterator it=vecOfStrs.begin(); it!=vecOfStrs.end(); ++it)
            {
                Initialize_var(*it);
            }
        }
        std::cout << std::to_string(var_map["a_13 int"]) << std::endl;
}