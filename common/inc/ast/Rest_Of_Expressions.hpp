#ifndef ast_rest_of_expressions_hpp
#define ast_rest_of_expressions_hpp

#include "ast_node.hpp"
// any non algebraic / logical expressions are here. unary in other file.

class Expression: public Node{
  private:
    const Node* expr;
    const Node* next;
  public:
    Expression(const Node* next_in, const Node* expr_in): next(next_in), expr(expr_in){
      type = "Expression";
    }

    const Node* getExpression() const{
      return expr;
    }

    const Node* getNext() const{
      return next;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     expr->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class RelationalExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;
    std::string ConditionForRelation;

  public: //initialising the class / constructor
    RelationalExpression(const Node* Left_SideOf_Expression, std::string Condition_For_Relation, const Node* Right_SideOf_Expression) : LeftSideOfExpression(Left_SideOf_Expression), RightSideOfExpression(Right_SideOf_Expression), ConditionForRelation(Condition_For_Relation)
    {
     type = "RelationalExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const std::string getConditionForRelation() const  // GETTER for ec
    {
     return ConditionForRelation;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << ConditionForRelation  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class AssignmentExpression : public Node{
  private:
    const Node* LeftSideOfExpression;  //this is the variable essentially.
    const Node* RightSideOfExpression; //the value being assigned to the variable
    const std::string* assignment;

  public: //initialising the class / constructor
    AssignmentExpression(const Node* Left_Side_Of_Expression, const std::string* assignment_in, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), assignment(assignment_in)
    {
     type = "AssignmentExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const std::string* getAssignment() const{
      return assignment;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << assignment  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class ConditionalExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;
    const Node* ConditionForExpression;

  public: //initialising the class / constructor
    ConditionalExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression, const Node* Condition_For_Expression1) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), ConditionForExpression(Condition_For_Expression1)
    {
     type = "ConditionalExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const   // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const Node* getConditionForExpression() const  // GETTER for ec
    {
     return ConditionForExpression;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     ConditionForExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "  ? " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "  :" << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};



#endif
