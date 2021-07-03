#ifndef ast_Enum_Declaration_hpp
#define ast_Enum_Declaration_hpp

#include "ast_node.hpp"

class EnumDeclaration : public Node
{
  private:  // enum has Enum_ID and an initial value.
    const Node* EnumInitialValue;
    const std::string* EnumID;

  public:
    EnumDeclaration(const std::string* Enum_ID, const Node* Enum_Initial_Value)
      : EnumID(Enum_ID), EnumInitialValue(Enum_Initial_Value) {
      type = "EnumDeclaration";
    }

    const Node* getEnumInitialValue() const  // returning the initialisation value.
    {
      return EnumInitialValue;
    }

    bool ProgramHasEnumInitialValue() const
    {
      return EnumInitialValue != nullptr; //check to see if it isn't empty
    }

    const std::string* getEnumID() const // returning the ENUM ID
    {
      return EnumID;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     EnumInitialValue->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
     if (ProgramHasEnumInitialValue() == true) //required so dont miss out printing next enum pointer.
     {
        outputstream << std::endl;
        EnumInitialValue->print(outputstream, IndentationLevel + "  ");
      }
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

class EnumSpecifier: public Node{
private:
  const std::string* enum_name;
  const Node* enumerator;
public:
  EnumSpecifier(const std::string* enum_name_in, const Node* enumerator_in): enum_name(enum_name_in), enumerator(enumerator_in){
    type = "EnumSpecifier";
  }

  bool hasVarName() const{
    return enum_name != nullptr;
  }

  const std::string* getEnumName() const{
    return enum_name;
  }

  const Node* getEnumerator() const{
    return enumerator;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
  {
   outputstream << IndentationLevel << type << " [ " << std::endl;
   outputstream << std::endl;
   if (hasVarName() == true) //required so dont miss out printing next enum pointer.
   {
      outputstream << enum_name << std::endl;
    }
   enumerator->print(outputstream, IndentationLevel + "  ");
   outputstream << std::endl << IndentationLevel << "]";
   return outputstream;
  }
};

#endif
