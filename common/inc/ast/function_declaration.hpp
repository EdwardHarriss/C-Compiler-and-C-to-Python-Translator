#ifndef function_declaration_hpp
#define function_declaration_hpp

#include "ast_node.hpp"

class FunctionDefinition : public Node
{
  private:
    const Node* NodeName;
    const Node* ListOfArguments;
    const Node* ContentsOfFunction;
    const Node* FunctionType;

  public: //initialising the class / constructor
    FunctionDefinition(const Node* Function_Type, const Node* Node_Name, const Node* List_Of_Arguments, const Node* Contents_Of_Function) : NodeName(Node_Name), ListOfArguments(List_Of_Arguments), ContentsOfFunction(Contents_Of_Function), FunctionType(Function_Type)
    {
     type = "FunctionDefinition";  // type is the inherited variable from the node class.
    }

    const Node* getNodeName() const {
     return NodeName;
    }

    const Node* getListOfArguments() const {
     return ListOfArguments;
    }

    const Node* getContentsOfFunction() const {
     return ContentsOfFunction;
    }

    const Node* getFunctionType() const
     {
     return FunctionType;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << FunctionType << std::endl;
     NodeName->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     ListOfArguments->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class FunctionDeclaration : public Node
{
  private:
    const Node* NodeName;
    const Node* ListOfArguments;
    const Node* FunctionType;

  public: //initialising the class / constructor
    FunctionDeclaration(const Node* Function_Type, const Node* Node_Name, const Node* List_Of_Arguments, const Node* Contents_Of_Function) : NodeName(Node_Name), ListOfArguments(List_Of_Arguments), FunctionType(Function_Type)
    {
     type = "FunctionDeclaration";  // type is the inherited variable from the node class.
    }

    const Node* getNodeName() const {
     return NodeName;
    }

    const Node* getListOfArguments() const {
     return ListOfArguments;
    }

    const Node* getFunctionType() const {
     return FunctionType;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << FunctionType << std::endl;
     NodeName->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     ListOfArguments->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};


class StatementListNode : public Node{
  private:
    const Node* statements;
    const Node* next_statements;
  public:
    StatementListNode(const Node* statement, const Node* next_statement): statements(statement), next_statements(next_statement){
      type = "StatementListNode";
    }

    const Node* getStatement() const
    {
      return statements;
    }

    const Node* getNextStatement() const
    {
      return next_statements;
    }

    bool hasStatement() const
    {
      if (statements != nullptr) 
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    bool hasNextStatement() const
    {
      if (next_statements != nullptr)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     statements->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     if(next_statements != nullptr){
       next_statements->print(outputstream, IndentationLevel + "  ");
       outputstream << std::endl << IndentationLevel << "]";
     }
     return outputstream;
    }
};



#endif
