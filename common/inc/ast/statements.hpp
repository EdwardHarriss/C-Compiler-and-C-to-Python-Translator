#ifndef statements_hpp
#define statements_hpp

#include "ast_node.hpp"



class CompoundStatement : public Node {
 private:
  const Node* lists;
  const Node* declaration;
 public:
  CompoundStatement(const Node* declaration_in, const Node* statement_list) : declaration(declaration_in), lists(statement_list){
    type = "CompoundStatement";
  }

  const Node* getStatementList() const {
    return lists;
  }

  const Node* getDeclaration() const{
    return declaration;
  }


  //
  bool hasLists() const {
    return lists != nullptr;
  }

  bool hasNext() const {
    return declaration != nullptr;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ ";
    if (hasLists()) {
      outputstream << std::endl;
      lists->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel;
    }
    outputstream << "]";
    return outputstream;
  }
};

class LabeledStatement: public Node{
  private:
    const Node* identity;
    const Node* constexpression;
    const Node* statements;
  public:
    LabeledStatement(const Node* identifier, const Node* constantexpression, const Node* statement):
    identity(identifier), constexpression(constantexpression), statements(statement){
      type = "LabeledStatement";
    }

    const Node* getIdentity() const {
      return identity;
    }

    const Node* getConstExpression() const {
      return constexpression;
    }

    const Node* getStatement() const {
      return statements;
    }

    bool hasConst() const {
      return constexpression != nullptr;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [ " << std::endl;
      outputstream << std::endl;
      if (hasConst()) {
        outputstream << std::endl;
        constexpression->print(outputstream, IndentationLevel + "  ");
        outputstream << std::endl << IndentationLevel;
      }
      statements->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class LabeledInternalList: public Node{
private:
  const Node* next;
  const Node* statement;
public:
  LabeledInternalList(const Node* next_in, const Node* statement_in): next(next_in), statement(statement_in){
    type = "LabeledInternalList";
  }

  const Node* getNext() const{
    return next;
  }

  const Node* getStatement() const{
    return statement;
  }

  bool hasNext() const{
    return next != nullptr;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << std::endl;
    outputstream << std::endl;
    if (hasNext()) {
      outputstream << std::endl;
      next->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel;
    }
    statement->print(outputstream, IndentationLevel + "  ");
    outputstream << std::endl << IndentationLevel << "]";
    return outputstream;
  }
};


#endif
