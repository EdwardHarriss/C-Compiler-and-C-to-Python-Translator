#ifndef ast_unary_hpp
#define ast_unary_hpp
#include "ast_node.hpp"

class UnaryExpression : public Node{
  private:
     const Node* UnaryExpressionVariable;
     const char* UnaryOperand;
     const std::string* UnaryOperand_;

  public: //initialising the class / constructor
    UnaryExpression(const char* Unary_Operand, const Node* Unary_Expression_Insertion) : UnaryOperand(Unary_Operand), UnaryExpressionVariable(Unary_Expression_Insertion)
    {
     type = "UnaryExpression";  // type is the inherited variable from the node class.
    }

    UnaryExpression(const std::string* Unary_Operand_, const Node* Unary_Expression_Insertion) : UnaryOperand_(Unary_Operand_), UnaryExpressionVariable(Unary_Expression_Insertion)
    {
     type = "UnaryExpression";  // type is the inherited variable from the node class.
    }

    const Node* getUnaryExpression() const  // GETTER for LHS
    {
     return UnaryExpressionVariable;
    }

    const std::string getUnaryOperand() const // GETTER for RHS
    {
      std::string str(UnaryOperand);
     return str;
    }

    bool hasString() const{
      return UnaryOperand_ != nullptr;
    }

    const std::string* getUnaryOpString() const{
      return UnaryOperand_;
    }


    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     outputstream << IndentationLevel << "  Type: " << UnaryOperand  << std::endl;
     UnaryExpressionVariable->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};
#endif
