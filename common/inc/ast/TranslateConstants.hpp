#ifndef translate_constants_hpp
#define translate_constants_hpp

#include "ast_node.hpp"

class IntConstant : public Node
{
  private:

  long long int IntConstantValue;

public:  // the function constructor.
 IntConstant(long long int Integer_Constant_Value) : IntConstantValue(Integer_Constant_Value) {
   type = "IntConstant";
 }

 long long int getIntConstantValue() const {
   return IntConstantValue;
 }

 virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
  {
   outputstream << IndentationLevel << type << " [ ";
   outputstream << IntConstantValue;
   outputstream << "]";
   return outputstream;
 }

};

class identifierC: public Node{
  private:
    const std::string* name;
  public:
    identifierC(const std::string* name_in): name(name_in){
      type = "identifierC";
    }

    const std::string* getName() const{
      return name;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
     {
      outputstream << IndentationLevel << type << " [ ";
      outputstream << name;
      outputstream << "]";
      return outputstream;
    }
};

class FloatConstant: public Node{
  private:
    const float val;
  public:
    FloatConstant(const float val_in): val(val_in){
      type = "FloatConstant";
    }

    const float getFloatVal() const{
      return val;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
     {
      outputstream << IndentationLevel << type << " [ ";
      outputstream << val;
      outputstream << "]";
      return outputstream;
    }
};

class CharConstant: public Node{
  private:
    const char* val;
  public:
    CharConstant(const char* val_in): val(val_in){
      type = "CharConstant";
    }

    const char* getCharVal() const{
      return val;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
     {
      outputstream << IndentationLevel << type << " [ ";
      outputstream << val;
      outputstream << "]";
      return outputstream;
    }
};

class DefaultNode: public Node{
  private:
    const std::string* name;
  public:
    DefaultNode(const std::string* name_in): name(name_in){
      type = "DefaultNode";
    }

    const std::string* getName() const{
      return name;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
     {
      outputstream << IndentationLevel << type << " [ ";
      outputstream << name;
      outputstream << "]";
      return outputstream;
    }
};

class CaseNode: public Node{
  private:
    const std::string* name;
  public:
    CaseNode(const std::string* name_in): name(name_in){
      type = "CaseNode";
    }

    const std::string* getName() const{
      return name;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override
     {
      outputstream << IndentationLevel << type << " [ ";
      outputstream << name;
      outputstream << "]";
      return outputstream;
    }
};

#endif
