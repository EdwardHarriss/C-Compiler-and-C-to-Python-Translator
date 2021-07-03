#ifndef ast_Struct_Definition_hpp
#define ast_Struct_Definition_hpp

#include "ast_node.hpp"

class struct_declaration : public Node
{

private:
  const Node* StructDef;

public:

  struct_declaration(const Node* Struct_Def) : StructDef(StructDef) // constructor function
  {
    type = "StructDeclaration";
  }

  const Node* getStructDeclaration() const // getter function for structdef
  {
   return StructDef;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
  {
   outputstream << IndentationLevel << type << " [ "  << std::endl;
   StructDef->print(outputstream, IndentationLevel + "  ");
   outputstream << std::endl;
   outputstream << std::endl << IndentationLevel << "]";
   return outputstream;
  }

};

#endif
