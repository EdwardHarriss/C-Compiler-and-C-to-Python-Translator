#ifndef ast_Constant_Expression_hpp
#define ast_Constant_Expression_hpp

#include "ast_node.hpp"

class constant_expression : public Node{
  private:
    const Node* Node_Name;
    const Node* List_Of_Arguments;
    std::string Function_Type;

  public: //initialising the class / constructor
    constant_expression(const Node* Node_Name_Insert, const Node* List_Of_Arguments_Insert, const std::string& Function_Type_Insert) : Node_Name(Node_Name_Insert), Function_Type(Function_Type_Insert), List_Of_Arguments(List_Of_Arguments_Insert)
    {
     type = "FunctionDeclaration";  // type is the inherited variable from the node class.
    }

    const Node* getNodeName() const
    {
     return Node_Name;
    }

    const Node* getListOfArguments() const
    {
     return List_Of_Arguments;
    }

    const std::string& getFunctionType() const
    {
     return Function_Type;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ "  << std::endl;
     Node_Name->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     List_Of_Arguments->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }

};



#endif
