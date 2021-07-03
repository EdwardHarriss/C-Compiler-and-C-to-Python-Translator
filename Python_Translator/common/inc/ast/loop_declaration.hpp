#ifndef loop_declaration_hpp
#define loop_declaration_hpp

#include "ast_node.hpp"


class IfStatement: public Node{
  private:
    const Node* condition;
    const Node* if_exec;
    const Node* else_exec;
  public:
    IfStatement(const Node* condition_insert, const Node* if_body, const Node* else_body ):
      condition(condition_insert), if_exec(if_body), else_exec(else_body)
    {
      type = "IfStatement";
    }

    const Node* getCondition() const{
      return condition;
    }

    const Node* getIf() const{
      return if_exec;
    }

    const Node* getELSE() const{
      return else_exec;
    }

    bool HasElse() const
    {
        if (else_exec != nullptr)
        {
          return true;
        }
        else
        {
          return false;
        }

    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      condition->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl;
      if_exec->print(outputstream, IndentationLevel + "  ");
      if (else_exec != nullptr) {
        outputstream << std::endl;
        else_exec->print(outputstream, IndentationLevel + "  ");
      }
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }

};

class SwitchStatement: public Node{
  private:
    const Node* expression;
    const Node* body;
  public:
    SwitchStatement(const Node* ex_in, const Node* statement):
    expression(ex_in), body(statement) {
      type = "SwitchStatement";
    }

    const Node* getSwitch() const{
      return expression;
    }

    const Node* getBody() const{
      return body;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [" << std::endl;
    expression->print(outputstream, IndentationLevel + "  ");
    outputstream << std::endl;
    body->print(outputstream, IndentationLevel + "  ");
    outputstream << std::endl << IndentationLevel << "]";
    return outputstream;
  }

};

class WhileStatement: public Node{
  private:
    const Node* parameter1;
    const Node* statement1;

  public:
    WhileStatement(const Node* parameter_insert, const Node* state_insert):
      parameter1(parameter_insert), statement1(state_insert){
      type = "WhileStatement";
    }

    const Node* getWhileParameter() const
    {
      return parameter1;
    }

    const Node* getWhileStatement() const
    {
      return statement1;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      parameter1->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl;
      statement1->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class DoStatement: public Node{
  private:
    const Node* body1;
    const Node* while1;
  public:
    DoStatement(const Node* statement, const Node* expression):
      body1(statement), while1(expression){
      type = "DoStatement";
      }

    const Node* getBody() const{
      return body1;
    }

    const Node* getDoStatement() const{
      return while1;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      body1->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl;
      while1->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class ForStatement: public Node{
  private:
    const Node* expression_statement1;
    const Node* expression_statement2;
    const Node* expression;
    const Node* statement;
  public:
    ForStatement(const Node* expression_statement, const Node* expression_statementagain, const Node* expression, const Node* statement):
    expression_statement1(expression_statement), expression_statement2(expression_statementagain), expression(expression), statement(statement){
      type = "ForStatement";
    }

    const Node* getExpressionStatement1() const{
      return expression_statement1;
    }

    const Node* getExpressionStatement2() const{
      return expression_statement2;
    }

    const Node* getExpression() const{
      return expression;
    }

    const Node* getForStatement() const{
      return statement;
    }

    bool HasExpression(){
      return expression != nullptr;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      expression_statement1->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl;
      expression_statement2->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      if(expression != nullptr){
        expression->print(outputstream, IndentationLevel + "  ");
        outputstream << std::endl << IndentationLevel << "]";
      }
      statement->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class GoToStatement: public Node{
  private:
    const std::string* identifier;

  public:
    GoToStatement(const std::string* c_identifier): identifier(c_identifier){
      type = "GoToStatement";
    }

    const std::string* getIdentifier() const{
      return identifier;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << identifier << std::endl;
      outputstream << std::endl;
      return outputstream;
    }
};

class ContinueStatement: public Node{
public:
  ContinueStatement(){
    type = "ContinueStatement";
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [" << std::endl;
    outputstream << std::endl;
    return outputstream;
  }
};

class BreakStatement: public Node{
public:
  BreakStatement(){
    type = "BreakStatement";
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [" << std::endl;
    outputstream << std::endl;
    return outputstream;
  }
};

class ReturnStatement : public Node{
private:
  const Node* expression;
public:
  ReturnStatement(const Node* expression_insert): expression(expression_insert){
    type = "ReturnStatement";
  }

  const Node* getExpression() const{
    return expression;
  }

  bool HasExpression() const{
    return expression != nullptr;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [" << std::endl;
    if(expression != nullptr){
      expression->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
    }
    return outputstream;
  }
};


#endif
