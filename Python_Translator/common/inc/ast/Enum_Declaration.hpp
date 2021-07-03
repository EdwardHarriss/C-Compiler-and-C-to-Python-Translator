#ifndef ast_Enum_Declaration_hpp
#define ast_Enum_Declaration_hpp

#include "ast_node.hpp"

class enum_declaration : public Node
{
  private:  // enum has Enum_ID and an initial value.
    const Node* EnumInitialValue;
    std::string EnumID;

  public:
    enum_declaration(const std::string& Enum_ID, const Node* Enum_Initial_Value)
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

    const std::string& getEnumID() const // returning the ENUM ID
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

#endif
