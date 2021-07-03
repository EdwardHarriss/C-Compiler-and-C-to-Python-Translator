#ifndef translate_variables_hpp
#define translate_variables_hpp

#include "ast_node.hpp"
#include <string>
#include <iostream>

class Variable : public Node
{
 private:
  const Node* Variable_Identifier; //this determines the type of variable we got as described in our parser.
  const char*  Variable_Information; // The info of the variable.
  const Node* Array_Information; // determines the array description, i.e size.

 public:
  Variable(const Node* Variable_Identifier_Insertion, const char* Variable_Information_Insertion,
           const Node* Array_Information_Insertion)
    : Variable_Identifier(Variable_Identifier_Insertion), Variable_Information(Variable_Information_Insertion), Array_Information(Array_Information_Insertion) {
    type = "Variable";
  }

  const Node* getVariable_Identifier() const {
    return Variable_Identifier;
  }

  std::string getVariable_Information() const {
    std::string str(Variable_Information);
    return str;
  }

   bool hasArray_Information() const
   {
      return Array_Information != nullptr;
    }

  const Node* getArray_Information() const
  {
    return Array_Information;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
  {
    outputstream << IndentationLevel << type << " [ " << Variable_Identifier << " (" << Variable_Information << ")";
    if ((Variable_Information == "array") && (Array_Information != nullptr))
    {
      outputstream << std::endl << IndentationLevel << "index or size:" << std::endl;
      Array_Information->print(outputstream, IndentationLevel + "  ");
    }
    outputstream << std::endl << IndentationLevel << "]";
    return outputstream;
  }
};

class VariableNorm: public Node{
  private:
    const std::string* VarName;
  public:
    VariableNorm(const std::string* VarNameIn): VarName(VarNameIn){
      type = "VariableNorm";
    }

    const std::string* getVarName() const{
      return VarName;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
    {
      outputstream << IndentationLevel << type << " [ " << VarName;
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class VariableNormNode: public Node{
  private:
    const Node* PrevName;
    const std::string* VarName;
  public:
    VariableNormNode(const Node* PrevNameIn, const std::string* VarNameIn): PrevName(PrevNameIn), VarName(VarNameIn){
      type = "VariableNorm";
    }

    const Node* getPrevName() const{
      return PrevName;
    }

    const std::string* getVarName() const{
      return VarName;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
    {
      outputstream << IndentationLevel << type << " [ " << VarName;
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

#endif
