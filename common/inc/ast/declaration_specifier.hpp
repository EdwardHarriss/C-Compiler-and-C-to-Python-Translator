#ifndef declaration_specifier_hpp
#define declaration_specifier_hpp

#include <string>
#include <iostream>

#include "ast_node.hpp"

class Declaration : public Node
{
  private:
    const Node* declarator_list;
    const Node* declarator_specifier;
  public:
    Declaration(const Node* declarator_specifiers, const Node* init_declarator_list) :
      declarator_list(init_declarator_list),
      declarator_specifier(declarator_specifiers){
      type = "Declaration";
    }

    const Node* getDeclaratorSpecifiers() const{
      return declarator_specifier;
    }

    const Node* getDeclaratorList() const{
      return declarator_list;
    }

    bool hasDeclarationSpecifier() const{
      return declarator_specifier != nullptr;
    }

    bool hasDeclarationList() const{
      return declarator_list != nullptr;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << declarator_specifier << std::endl;
    declarator_list->print(outputstream, IndentationLevel + " ");
    outputstream << std::endl << IndentationLevel << " ]";
    return outputstream;
    }

};

class DeclarationList: public Node{
  private:
    const Node* previous;
    const Node* present;
  public:
     DeclarationList(const Node* previous_in, const Node* present_in): previous(previous_in), present(present_in){
       type = "DeclarationList";
     }

     const Node* getPrevious() const{
       return previous;
     }

     const Node* getPresent() const{
       return present;
     }

     const bool hasPrevious() const{
       return previous != nullptr;
     }

     virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     if(hasPrevious()){
       previous->print(outputstream, IndentationLevel + " ");
     }
     present->print(outputstream, IndentationLevel + " ");
     outputstream << std::endl << IndentationLevel << " ]";
     return outputstream;
     }

};

class InitDeclaratorList: public Node{
  private:
    const Node* previous;
    const Node* present;
  public:
    InitDeclaratorList(const Node* previous_in, const Node* present_in): previous(previous_in), present(present_in){
      type = "InitDeclaratorList";
    }

    const Node* getPrevious() const{
      return previous;
    }

    const Node* getPresent() const{
      return present;
    }

    const bool hasPrevious() const{
      return previous != nullptr;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << std::endl;
    if(hasPrevious()){
      previous->print(outputstream, IndentationLevel + " ");
    }
    present->print(outputstream, IndentationLevel + " ");
    outputstream << std::endl << IndentationLevel << " ]";
    return outputstream;
    }
};

class DeclarationSpecifier: public Node{
  private:
    const Node* Left;
    const Node* Right;
  public:
    DeclarationSpecifier(const Node* Leftin, const Node* Rightin): Left(Leftin), Right(Rightin){
      type = "DeclarationSpecifier";
    }

    const Node* getLeft() const{
      return Left;
    }

    const Node* getRight() const{
      return Right;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << std::endl;
    Left->print(outputstream, IndentationLevel + " ");
    Right->print(outputstream, IndentationLevel + " ");
    outputstream << std::endl << IndentationLevel << " ]";
    return outputstream;
    }
};

class Specifier: public Node{
  private:
    const char* spec;
  public:
    Specifier(const char* spec_in): spec(spec_in){
      type = "Specifier";
    }

    const std::string getSpec() const{
      std::string str(spec);
      return str;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << spec << std::endl;
    outputstream << std::endl << IndentationLevel << " ]";
    return outputstream;
    }
};

class InitDeclarator : public Node
{
  private:
    const Node* declarators;
    const Node* initialisers;
  public:
    InitDeclarator(const Node* declarator, const Node* initialiser) :
      declarators(declarator),
      initialisers(initialiser){
      type = "InitDeclarator";
    }

    const Node* getDeclarator() const{
      return declarators;
    }

    const Node* getInitialiser() const{
      return initialisers;
    }

    bool hasInitialiser() const{
      return initialisers != nullptr;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [ " << declarators << std::endl;
    initialisers->print(outputstream, IndentationLevel + " ");
    outputstream << std::endl << IndentationLevel << " ]";
    return outputstream;
    }
};

class PostfixExpression : public Node {
  private:
    const Node* postfix_expression;
    const char* type1;
    const Node* others;

  public:
    PostfixExpression(const Node* postfix_expressionin, const char* operator1, const Node* indentifier): postfix_expression(postfix_expressionin),
    type1(operator1),
    others(indentifier){
      type = "PostfixExpression";
    }

    const Node* getPostfixExpression() const{
      return postfix_expression;
    }

    const std::string getTypes() const{
      std::string str(type1);
      return str;
    }

    const Node* getOthers() const{
      return others;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      outputstream << IndentationLevel << "  Type: " << type << std::endl;
      postfix_expression->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class PostfixExpressionStr : public Node {
  private:
    const Node* postfix_expression;
    const char* type1;
    const std::string* others;

  public:
    PostfixExpressionStr(const Node* postfix_expressionin, const char* operator1, const std::string* indentifier): postfix_expression(postfix_expressionin),
    type1(operator1),
    others(indentifier){
      type = "PostfixExpressionStr";
    }

    const Node* getPostfixExpression() const{
      return postfix_expression;
    }

    const std::string getTypes() const{
      std::string str(type1);
      return str;
    }

    const std::string* getOthers() const{
      return others;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      outputstream << IndentationLevel << "  Type: " << type << std::endl;
      postfix_expression->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class EmptyExpression : public Node {
 private:

 public:
  EmptyExpression()
  {
    type = "EmptyExpression";
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " []";
    return outputstream;
  }
};

class ParametersListNode: public Node{
  private:
    const Node* left;
    const Node* right;
  public:
    ParametersListNode(const Node* left_in, const Node* right_in): left(left_in), right(right_in){
      type = "ParametersListNode";
    }

    const Node* getLeft() const{
      return left;
    }

    const Node* getRight() const{
      return right;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      left->print(outputstream, IndentationLevel + "  ");
      if(right != nullptr){
        right->print(outputstream, IndentationLevel + "  ");
      }
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class PointerAbstractDeclarator: public Node{
  private:
    const Node* left;
  public:
    PointerAbstractDeclarator(const Node* left_in): left(left_in){
      type = "PointerAbstractDeclarator";
    }

    const Node* getLeft() const{
      return left;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      left->print(outputstream, IndentationLevel + "  ");
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class AbstractDeclarator: public Node{
  private:
    const Node* nodes;
  public:
    AbstractDeclarator(const Node* left_in): nodes(left_in){
      type = "AbstractDeclarator";
    }

    const Node* getNodes() const{
      return nodes;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
      outputstream << IndentationLevel << type << " [" << std::endl;
      if(nodes != nullptr){
        nodes->print(outputstream, IndentationLevel + "  ");
      }
      outputstream << std::endl << IndentationLevel << "]";
      return outputstream;
    }
};

class ParameterList: public Node{
private:
  const Node* left;
  const Node* right;
public:
  ParameterList(const Node* left_in, const Node* right_in): left(left_in), right(right_in){
    type = "ParameterList";
  }

  const Node* getLeft() const{
    return left;
  }

  const Node* getRight() const{
    return right;
  }

  bool hasLeft() const{
    return left!= nullptr;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override {
    outputstream << IndentationLevel << type << " [" << std::endl;
    right->print(outputstream, IndentationLevel + "  ");
    if(left != nullptr){
      left->print(outputstream, IndentationLevel + "  ");
    }
    outputstream << std::endl << IndentationLevel << "]";
    return outputstream;
  }
};


#endif
