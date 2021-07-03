#ifndef ast_Struct_Declaration_hpp
#define ast_Struct_Declaration_hpp

#include "ast_node.hpp"

class StructDeclaration : public Node
{

private:
  const Node* StructDef;
  const Node* StructList;
public:

  StructDeclaration(const Node* Struct_Def, const Node* Struct_list) : StructDef(Struct_Def), StructList(Struct_list){
    type = "StructDeclaration";
  }

  const Node* getStructDeclaration() const // getter function for structdef
  {
   return StructDef;
  }

  const Node* getStructList() const // getter function for structdef
  {
   return StructList;
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
