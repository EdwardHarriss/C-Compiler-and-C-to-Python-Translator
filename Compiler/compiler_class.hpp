#ifndef compiler_class_hpp
#define compiler_class_hpp

#include "../common/inc/ast.hpp"

#include <vector>
#include <string>
#include <cstdint>

struct functions{
  const std::string* funcs_name;
  int no_args;
};

class FunctionDeclarations{
  private:
    std::vector<functions> list_of_functions_declarations;
    std::vector<functions> list_of_functions;
  public:
    bool CheckDeclarations(const std::string* func_name){
      bool tmp = false;
      for(int i=0; i<list_of_functions_declarations.size(); i++){
        if(list_of_functions_declarations[i].funcs_name == func_name){
          tmp = true;
        }
      }
      return tmp;
    }

    bool CheckDefinitions(const std::string* func_name){
      bool tmp = false;
      for(int i=0; i<list_of_functions.size(); i++){
        if(list_of_functions[i].funcs_name == func_name){
          tmp = true;
        }
      }
      return tmp;
    }

    void AddFunctionDec(const std::string* func_name){
      functions tmp;
      tmp.funcs_name = func_name;
      list_of_functions_declarations.push_back(tmp);
    }

    void AddFunction(const std::string* func_name, int arguments){
      functions tmp;
      tmp.funcs_name = func_name;
      tmp.no_args = arguments;
      list_of_functions.push_back(tmp);
    }

    void AddFunctionName(const std::string* func_name){
      functions tmp;
      tmp.funcs_name = func_name;
      list_of_functions.push_back(tmp);
    }

    void AddFunctionArgs(const std::string* func_name, int no_args_in){
      for(int i =0; i<list_of_functions.size(); i++){
        if(list_of_functions[i].funcs_name == func_name){
          list_of_functions[i].no_args == no_args_in;
          return;
        }
      }
      functions tmp;
      tmp.funcs_name = func_name;
      tmp.no_args = no_args_in;
      list_of_functions.push_back(tmp);
      return;
    }

    functions GetFunctionName() const{
      return list_of_functions.back();
    }
};

struct regi{
  std::string var;
  int value;
};

struct memlocation{
  std::string var;
  int location;
};

struct variablesstruct{
  std::string names;
  long long int values;
};

class RegisterDeclarations{
  private:
    std::vector <regi> registers;
  public:
    RegisterDeclarations(){
      registers.resize(32);
    }

    const std::string getRegister(int n){
      if(n>31){
        exit(1);
      }
      return registers[n].var;
    }

    void AddVariable(const std::string name, int index){
      registers[index].var = name;
    }

    int FindRegNumber(const std::string name){
      for(int i=0; i<registers.size(); i++){
        if(registers[i].var == name){
          return i;
        }
      }
      return -1;
    }

    int GetRegValue(const std::string name){
      for(int i=0; i<registers.size(); i++){
        if(registers[i].var == name){
          return registers[i].value;
        }
      }
    }

};

class MemoryDeclaration{
  private:
    std::vector<memlocation> memory_;
  public:
    MemoryDeclaration(){ ; }

    void AddValue(const std::string varin, int locationin){
      memlocation tmp;
      tmp.var = varin;
      tmp.location = locationin;
      memory_.push_back(tmp);
    }

    int FindVariable(const std::string varin){
      for(int i=0; i<memory_.size(); i++){
        if(memory_[i].var == varin){
          return memory_[i].location;
        }
      }
    }

    std::vector<memlocation> getMemory(){
      return memory_;
    }

    bool InMemory(const std::string name_in){
      for(int i=0; i<memory_.size(); i++){
        if(memory_[i].var == name_in){
          return true;
        }
      }
      return false;
    }
};

class LocalVariables{
private:
  std::vector<variablesstruct> variables;
public:
  LocalVariables(){;}

  void addVariable(const std::string name){
    variablesstruct tmp;
    tmp.names = name;
    variables.push_back(tmp);
  }

  void addValue(const std::string name, long long int value){
    variablesstruct tmp;
    bool found = false;
    for(int i=0; i<variables.size(); i++){
      if(variables[i].names == name){
        found = true;
        tmp.names = name;
        tmp.values = value;
        variables[i] = tmp;
      }
    }
    if(!found){
      tmp.names = name;
      tmp.values = value;
      variables.push_back(tmp);
    }
  }

  bool DefinedVariable(const std::string name) const{
    for(int i = 0; i<variables.size(); i++){
      if(variables[i].names == name){
        return true;
      }
    }
    return false;
  }

  long long int getValue(const std::string name) const{
    for(int i = 0; i<variables.size(); i++){
      if(variables[i].names == name){
        return variables[i].values;
      }
    }
  }

  std::vector<variablesstruct> getLocalVariables(){
    return variables;
  }
};

class GlobalVariables{
private:
  std::vector<std::vector<int>> var_name;
public:
  void addVariable(std::vector<int> var_name_in){
    var_name.push_back(var_name_in);
  }
};

struct EnumDef{
  std::string name;
  long long int value;
};

class EnumDeclarationCompiler{
private:
  std::vector<EnumDef> enums_declared;
public:
  void AddEnum(std::string name_in,long long int value_in){
    EnumDef tmp;
    tmp.name = name_in;
    tmp.value = value_in;
    enums_declared.push_back(tmp);
  }

  void AddEnum(std::string name_in){
    EnumDef tmp;
    tmp.name = name_in;
    tmp.value = 0;
    enums_declared.push_back(tmp);
  }

  long long int GetEnum(std::string name_in){
    for(int i=0; i<enums_declared.size(); i++){
      if(enums_declared[i].name == name_in){
        return enums_declared[i].value;
      }
    }
  }

  bool CheckEnum(std::string name_in){
    for(int i =0; i<enums_declared.size(); i++){
      if(enums_declared[i].name == name_in){
        return true;
      }
    }
    return false;
  }

};


#endif
