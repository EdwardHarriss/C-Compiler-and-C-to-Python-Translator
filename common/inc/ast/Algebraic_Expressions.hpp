#ifndef ast_algebraic_Expression_hpp
#define ast_algebraic_Expression_hpp

#include "ast_node.hpp"

class InclusiveOrExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    InclusiveOrExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression)
    {
     type = "InclusiveOrExpression";  // type is the inherited variable from the node class.
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
     outputstream << IndentationLevel << "  Type: " << " | "  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }

};

class ExclusiveOrExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    ExclusiveOrExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression)
    {
     type = "ExclusiveOrExpression";  // type is the inherited variable from the node class.
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
     outputstream << IndentationLevel << "  Type: " << " ^ "  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class AndExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    AndExpression(const Node* Left_Side_Of_Expression, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression)
    {
     type = "AndExpression";  // type is the inherited variable from the node class.
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
     outputstream << IndentationLevel << "  Type: " << " & "  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class EqualityExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const char* ConditionForEquality;
    const Node* RightSideOfExpression;


  public: //initialising the class / constructor
    EqualityExpression(const Node* Left_Side_Of_Expression, const char* Condition_For_Equality, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), ConditionForEquality(Condition_For_Equality)
    {
     type = "EqualityExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const char* getConditionForEquality() const  // GETTER for ec
    {
     return ConditionForEquality;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << ConditionForEquality  << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class ShiftExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const char* ConditionForShift;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    ShiftExpression(const Node* Left_Side_Of_Expression, const char* Condition_For_Shift, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), ConditionForShift(Condition_For_Shift)
    {
     type = "ShiftExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const char* getConditionForShift() const  // GETTER for ec
    {
     return ConditionForShift;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << ConditionForShift << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class AdditiveExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const char* ConditionForAddition;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    AdditiveExpression(const Node* Left_Side_Of_Expression, const char* Condition_For_Addition, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), ConditionForAddition(Condition_For_Addition)
    {
     type = "AdditiveExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const std::string getConditionForAddition() const  // GETTER for ec
    {
     std::string str(ConditionForAddition);
     return str;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << ConditionForAddition << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class MultiplicativeExpression : public Node{
  private:
    const Node* LeftSideOfExpression;
    const char* ConditionForMultiplication;
    const Node* RightSideOfExpression;

  public: //initialising the class / constructor
    MultiplicativeExpression(const Node* Left_Side_Of_Expression, const char* Condition_For_Multiplication, const Node* Right_Side_Of_Expression) : LeftSideOfExpression(Left_Side_Of_Expression), RightSideOfExpression(Right_Side_Of_Expression), ConditionForMultiplication(Condition_For_Multiplication)
    {
     type = "MultiplicativeExpression";  // type is the inherited variable from the node class.
    }

    const Node* getLeftSideOfExpression() const  // GETTER for LHS
    {
     return LeftSideOfExpression;
    }

    const Node* getRightSideOfExpression() const // GETTER for RHS
    {
     return RightSideOfExpression;
    }

    const char* getConditionForMultiplication() const  // GETTER for ec
    {
     return ConditionForMultiplication;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     LeftSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     outputstream << IndentationLevel << "  Type: " << ConditionForMultiplication << std::endl;
     RightSideOfExpression->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

#endif
