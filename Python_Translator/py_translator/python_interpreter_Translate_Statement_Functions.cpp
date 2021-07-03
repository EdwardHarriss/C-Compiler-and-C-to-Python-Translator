#include "python_interpreter_Translate_Statement_Functions.hpp"
#include "python_interpreter.hpp"

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdio>
#include "IndentationAdder.hpp"

void Translating_Condition_Of_Statement(const Node* Condition, std::ofstream& output_python_file)
{
// Need to only convert to an Expression... if it is an expression.
//  std::cout << "The condition is currently: " << (Condition)->getType() << '\n';
  // Final Cases that will end the function's recusion


  if ((Condition)->getType() == "IntConstant")
  {
    const IntConstant* int_const = dynamic_cast<const IntConstant*>(Condition);
    output_python_file << int_const->getIntConstantValue();

  }

  if ((Condition)->getType() == "Variable")
  {
    const Variable* variable_const = dynamic_cast<const Variable*>(Condition);
    output_python_file << variable_const->getVariable_Identifier();
  }

  if ((Condition)->getType() == "identifierC")
  {
    const identifierC* c_const = dynamic_cast<const identifierC*>(Condition);
    output_python_file << *(c_const->getName());
  }


  // in the case of it not being an Expression...
  if ((Condition)->getType() == "PostfixExpression") // basically function call
  {
    const PostfixExpression* postfix_function_call = dynamic_cast<const PostfixExpression*>(Condition);
    TranslatingFunctionCall(output_python_file, postfix_function_call);
  }


  if ((Condition)->getType() == "RelationalExpression")
  {
    const RelationalExpression* relational_Expression = dynamic_cast<const RelationalExpression*>(Condition);
    output_python_file <<  "(";
    Translating_Condition_Of_Statement(relational_Expression->getLeftSideOfExpression(),output_python_file);
    output_python_file << " ";
    output_python_file << relational_Expression->getConditionForRelation();
    output_python_file << " ";
    Translating_Condition_Of_Statement(relational_Expression->getRightSideOfExpression(),output_python_file);
    output_python_file <<  ")";
  }

  if ((Condition)->getType() == "AssignmentExpression")
  { //evauluate lhs and rhs independently
    const AssignmentExpression* assignment_exp = dynamic_cast<const AssignmentExpression*>(Condition);
    Translating_Condition_Of_Statement(assignment_exp->getLeftSideOfExpression(),output_python_file);
    output_python_file << " = ";

    Translating_Condition_Of_Statement(assignment_exp->getRightSideOfExpression(),output_python_file);


  }

  if ((Condition)->getType() == "EqualityExpression")
  {
      const EqualityExpression* Current_Equality_Statement = dynamic_cast<const EqualityExpression*>(Condition);
      output_python_file << "(";
      Translating_Condition_Of_Statement(Current_Equality_Statement->getLeftSideOfExpression(),output_python_file);
      output_python_file << " ";
      output_python_file << Current_Equality_Statement->getConditionForEquality();
      output_python_file << " ";
      Translating_Condition_Of_Statement(Current_Equality_Statement->getRightSideOfExpression(),output_python_file);
      output_python_file << ")";
  }



  if ((Condition)->getType() == "AdditiveExpression")
  {

      const AdditiveExpression* Current_Additive_Statement = dynamic_cast<const AdditiveExpression*>(Condition);

      output_python_file << "(";
      Translating_Condition_Of_Statement(Current_Additive_Statement->getLeftSideOfExpression(),output_python_file);
      output_python_file << " ";
      output_python_file << Current_Additive_Statement->getConditionForAddition();
      output_python_file << " ";
      Translating_Condition_Of_Statement(Current_Additive_Statement->getRightSideOfExpression(),output_python_file);
      output_python_file << ")";
  }

  if ((Condition)->getType() == "MultiplicativeExpression")
  {
      const MultiplicativeExpression* Current_Multiplicative_Statement = dynamic_cast<const MultiplicativeExpression*>(Condition);
      output_python_file << "(";
    //  std::cout << "dsdfsdfsdsdf" <<  (Current_Multiplicative_Statement->getLeftSideOfExpression())->getType() << '\n';
      Translating_Condition_Of_Statement(Current_Multiplicative_Statement->getLeftSideOfExpression(),output_python_file);
      //output_python_file << " ";
      output_python_file << Current_Multiplicative_Statement->getConditionForMultiplication();
      //output_python_file << " ";
      Translating_Condition_Of_Statement(Current_Multiplicative_Statement->getRightSideOfExpression(),output_python_file);
      output_python_file << ")";
  }

  if ((Condition)->getType() == "LogicalOrExpression")
  {
      const LogicalOrExpression* Current_Logical_Or_Statement = dynamic_cast<const LogicalOrExpression*>(Condition);
      output_python_file << "(";
      Translating_Condition_Of_Statement(Current_Logical_Or_Statement->getLeftSideOfExpression(),output_python_file);
      output_python_file << " ";
      output_python_file << "or";
      output_python_file << " ";
      Translating_Condition_Of_Statement(Current_Logical_Or_Statement->getRightSideOfExpression(),output_python_file);
      output_python_file << ")";
  }

  if ((Condition)->getType() == "LogicalAndExpression")
  {
      const LogicalAndExpression* Current_Logical_And_Statement = dynamic_cast<const LogicalAndExpression*>(Condition);
      output_python_file << "(";
      Translating_Condition_Of_Statement(Current_Logical_And_Statement->getLeftSideOfExpression(),output_python_file);
      output_python_file << " ";
      output_python_file << "and";
      output_python_file << " ";
      Translating_Condition_Of_Statement(Current_Logical_And_Statement->getRightSideOfExpression(),output_python_file);
      output_python_file << ")";
  }


  if ((Condition)->getType() == "UnaryExpression")
  {
    const UnaryExpression* unary_Expression = dynamic_cast<const UnaryExpression*>(Condition);
    const std::string* unaryOperand_ = unary_Expression->getUnaryOpString();
    output_python_file <<  "(" << *unaryOperand_;
    Translating_Condition_Of_Statement(unary_Expression->getUnaryExpression(),output_python_file);
    output_python_file <<  ")";
  }


  // *************** Begin case of it being an of expressions **************************


  if ((Condition)->getType() == "Expression")
  {

    const Expression* Temp_Condition = dynamic_cast<const Expression*>(Condition);


    if ((Temp_Condition->getExpression())->getType() == "IntConstant")
    {
      const IntConstant* int_const = dynamic_cast<const IntConstant*>(Temp_Condition->getExpression());
      output_python_file << std::to_string(int_const->getIntConstantValue());

    }

    if ((Temp_Condition->getExpression())->getType() == "Variable")
    {
      const Variable* variable_const = dynamic_cast<const Variable*>(Temp_Condition->getExpression());
      output_python_file << variable_const->getVariable_Identifier();
    }

    if ((Temp_Condition->getExpression())->getType() == "identifierC")
    {
      const identifierC* c_const = dynamic_cast<const identifierC*>(Temp_Condition->getExpression());
      output_python_file << *(c_const->getName());
    }


// Base cases, ended. Now the rest of the expressions begin.

    if ((Temp_Condition->getExpression())->getType() == "RelationalExpression")
    {
      const RelationalExpression* relational_Expression = dynamic_cast<const RelationalExpression*>(Temp_Condition->getExpression());
      output_python_file <<  "(";
      Translating_Condition_Of_Statement(relational_Expression->getLeftSideOfExpression(),output_python_file);
      output_python_file << " ";
      output_python_file << relational_Expression->getConditionForRelation();
      output_python_file << " ";
      Translating_Condition_Of_Statement(relational_Expression->getRightSideOfExpression(),output_python_file);
      output_python_file <<  ")";
    }

    if ((Temp_Condition->getExpression())->getType() == "PostfixExpression") // basically function call
    {
      const PostfixExpression* postfix_function_call = dynamic_cast<const PostfixExpression*>(Temp_Condition->getExpression());
      TranslatingFunctionCall(output_python_file, postfix_function_call);
    }

    if ((Temp_Condition->getExpression())->getType() == "AssignmentExpression")
    { //evauluate lhs and rhs independently
      const AssignmentExpression* assignment_exp = dynamic_cast<const AssignmentExpression*>(Temp_Condition->getExpression());

      Translating_Condition_Of_Statement(assignment_exp->getLeftSideOfExpression(),output_python_file);
      output_python_file << " = ";
      Translating_Condition_Of_Statement(assignment_exp->getRightSideOfExpression(),output_python_file);

    }

    if ((Temp_Condition->getExpression())->getType() == "EqualityExpression")
    {
        const EqualityExpression* Current_Equality_Statement = dynamic_cast<const EqualityExpression*>(Temp_Condition->getExpression());
        output_python_file << "(";
        Translating_Condition_Of_Statement(Current_Equality_Statement->getLeftSideOfExpression(),output_python_file);
        output_python_file << " ";
        output_python_file << Current_Equality_Statement->getConditionForEquality();
        output_python_file << " ";
        Translating_Condition_Of_Statement(Current_Equality_Statement->getRightSideOfExpression(),output_python_file);
        output_python_file << ")";
    }



    if ((Temp_Condition->getExpression())->getType() == "AdditiveExpression")
    {
        const AdditiveExpression* Current_Additive_Statement = dynamic_cast<const AdditiveExpression*>(Temp_Condition->getExpression());

        output_python_file << "(";
        Translating_Condition_Of_Statement(Current_Additive_Statement->getLeftSideOfExpression(),output_python_file);
        output_python_file << " ";
        output_python_file << Current_Additive_Statement->getConditionForAddition();
        output_python_file << " ";
        Translating_Condition_Of_Statement(Current_Additive_Statement->getRightSideOfExpression(),output_python_file);
        output_python_file << ")";
    }

    if ((Temp_Condition->getExpression())->getType() == "MultiplicativeExpression")
    {
        const MultiplicativeExpression* Current_Multiplicative_Statement = dynamic_cast<const MultiplicativeExpression*>(Temp_Condition->getExpression());
        output_python_file << "(";
      //  std::cout << "/* message */" <<  (Current_Multiplicative_Statement->getLeftSideOfExpression())->getType() << '\n';
        Translating_Condition_Of_Statement(Current_Multiplicative_Statement->getLeftSideOfExpression(),output_python_file);
        //output_python_file << " ";
        output_python_file << Current_Multiplicative_Statement->getConditionForMultiplication();
        //output_python_file << " ";
        Translating_Condition_Of_Statement(Current_Multiplicative_Statement->getRightSideOfExpression(),output_python_file);
        output_python_file << ")";
    }

    if ((Temp_Condition->getExpression())->getType() == "LogicalOrExpression")
    {
        const LogicalOrExpression* Current_Logical_Or_Statement = dynamic_cast<const LogicalOrExpression*>(Temp_Condition->getExpression());
        output_python_file << "(";
        Translating_Condition_Of_Statement(Current_Logical_Or_Statement->getLeftSideOfExpression(),output_python_file);
        output_python_file << " ";
        output_python_file << "or";
        output_python_file << " ";
        Translating_Condition_Of_Statement(Current_Logical_Or_Statement->getRightSideOfExpression(),output_python_file);
        output_python_file << ")";
    }

    if ((Temp_Condition->getExpression())->getType() == "LogicalAndExpression")
    {
        const LogicalAndExpression* Current_Logical_And_Statement = dynamic_cast<const LogicalAndExpression*>(Temp_Condition->getExpression());
        output_python_file << "(";
        Translating_Condition_Of_Statement(Current_Logical_And_Statement->getLeftSideOfExpression(),output_python_file);
        output_python_file << " ";
        output_python_file << "and";
        output_python_file << " ";
        Translating_Condition_Of_Statement(Current_Logical_And_Statement->getRightSideOfExpression(),output_python_file);
        output_python_file << ")";
    }


    if ((Temp_Condition->getExpression())->getType() == "UnaryExpression")
    {
      const UnaryExpression* unary_Expression = dynamic_cast<const UnaryExpression*>(Temp_Condition->getExpression());
      const std::string* unaryOperand_ = unary_Expression->getUnaryOpString();
      output_python_file <<  "(" << unaryOperand_;
      Translating_Condition_Of_Statement(unary_Expression->getUnaryExpression(),output_python_file);
      output_python_file <<  ")";
    }
  }





}

void TranslatingReturnStatement(int NumberOfIndents, std::ofstream& output_python_file, const ReturnStatement* return_state)
{
//  std::cout << "Inside the return statement now" << '\n';
  //case of return having something like int or bool.
  if (return_state->HasExpression() == true)
  {
    AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
    output_python_file << "return ";
    Translating_Condition_Of_Statement(return_state->getExpression(),output_python_file);
    output_python_file << std::endl;;
  }
  //just a blank return...
  else
  {
    AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
    output_python_file << "return";
    output_python_file << std::endl;;
  }


}

void TranslatingIfStatement(int NumberOfIndents, std::ofstream& output_python_file, const IfStatement* if_state)
{
  AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
  output_python_file << "if "; //now call recursive TranslatingConditionFunction function
  Translating_Condition_Of_Statement(if_state->getCondition(), output_python_file);
  output_python_file << ":" << std::endl;

  //Translating CONTENTS OF IF STATEMENT


  if(if_state->getIf() != nullptr){
    const CompoundStatement* comp_state = dynamic_cast<const CompoundStatement*>(if_state->getIf());

    TranslatingCompoundStatement(NumberOfIndents+1,output_python_file,comp_state);
  }

  if(if_state->HasElse() == true){
    AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
    output_python_file << "else";
    output_python_file << ":" << std::endl;
    const CompoundStatement* comp_state = dynamic_cast<const CompoundStatement*>(if_state->getELSE());
    TranslatingCompoundStatement(NumberOfIndents+1,output_python_file,comp_state);
  }

}

void TranslatingWhileStatement(int NumberOfIndents, std::ofstream& output_python_file, const WhileStatement* while_state)
{
  AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
  output_python_file << "while ";
  Translating_Condition_Of_Statement(while_state->getWhileParameter(), output_python_file);
  output_python_file <<":" << std::endl;

  // Translating CONTENTS OF WHILE LOOP
  //similar to the if statement
  if(while_state->getWhileStatement() != nullptr){
    const CompoundStatement* comp_state = dynamic_cast<const CompoundStatement*>(while_state->getWhileStatement());
    TranslatingCompoundStatement(NumberOfIndents+1,output_python_file,comp_state);
  }

}
