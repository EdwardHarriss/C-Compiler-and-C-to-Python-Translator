#ifndef ast_Constant_Expression_hpp
#define ast_Constant_Expression_hpp

#include "ast_node.hpp"

class ConstantExpression : public Node{
  private:
    const Node* Node_Name;
    const Node* List_Of_Arguments;

  public: //initialising the class / constructor
    ConstantExpression(const Node* Node_Name_Insert, const Node* List_Of_Arguments_Insert) : Node_Name(Node_Name_Insert), List_Of_Arguments(List_Of_Arguments_Insert)
    {
     type = "ConstantExpression";  // type is the inherited variable from the node class.
    }

    const Node* getNodeName() const
    {
     return Node_Name;
    }

    const Node* getListOfArguments() const
    {
     return List_Of_Arguments;
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
