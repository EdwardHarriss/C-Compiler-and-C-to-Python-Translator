#ifndef ast_Enum_Declaration_List_Node_hpp
#define ast_Enum_Declaration_List_Node_hpp

#include "ast_node.hpp"

class EnumDeclarationListNode : public Node
{
  private: // enum list contains pointers:
  const Node* CurrentEnumDeclaration;
  const Node* NextEnumDeclaration;

  public:
  EnumDeclarationListNode(const Node* Current_Enum_Declaration1, const Node* Next_Enum_Declaration) : CurrentEnumDeclaration(Current_Enum_Declaration1), NextEnumDeclaration(Next_Enum_Declaration)
  {
    type = "EnumDeclarationListNode";
  }

  const Node* getCurrentEnumDeclaration() const  // getter function for enum decl
  {
    return CurrentEnumDeclaration;
  }

  const Node* getNextEnumDeclaration() const // getter function for next enum decl
  {
    return NextEnumDeclaration;
  }

  bool ProgramHasNextEnumDeclaration() const // required to check later if want to print or not.
  {
    return CurrentEnumDeclaration != nullptr;
  }

  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
  {
   outputstream << IndentationLevel << type << " [ " << std::endl;
   CurrentEnumDeclaration->print(outputstream, IndentationLevel + "  ");
   outputstream << std::endl;
   if (ProgramHasNextEnumDeclaration() == true) //required so dont miss out printing next enum pointer.
   {
      outputstream << std::endl;
      CurrentEnumDeclaration->print(outputstream, IndentationLevel + "  ");
    }
   outputstream << std::endl << IndentationLevel << "]";
   return outputstream;
  }

};



#endif
