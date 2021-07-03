#ifndef ast_logical_Expression_hpp
#define ast_logical_Expression_hpp

#include "ast_node.hpp"

class LogicalOrExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    LogicalOrExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression)
    {
     type = "LogicalOrExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }


    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << " || "  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }

};

class LogicalAndExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    LogicalAndExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression)
    {
     type = "LogicalAndExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }


    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << " && "  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }

};



#endif
