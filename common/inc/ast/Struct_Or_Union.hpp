#ifndef ast_Struct_Or_Union_hpp
#define ast_Struct_Or_Union_hpp

#include "ast_node.hpp"

class StructUnion : public Node
{
  private:
    const Node* StructUnionPointer;
    const Node* StructUnionList;
    std::string StructUnionID;

  public: //initialising the class / constructor, 3 different scenarios.

    StructUnion(const Node* argument1, std::string argument2)
            : StructUnionPointer(argument1)
            , StructUnionID(argument2)
            , StructUnionList(NULL)
        {}

    StructUnion(const Node* argument1, const Node* argument2)
        : StructUnionPointer(argument1)
        , StructUnionID(" ")
        , StructUnionList(argument2)
    {}

    StructUnion(const Node* argument1, std::string argument2, const Node* argument3)
        : StructUnionPointer(argument1)
        , StructUnionID(argument2)
        , StructUnionList(argument3)
    {}

    const Node* getStructUnionPointer() const  // GETTER for LHS
    {
     return StructUnionPointer;
    }

    const Node* getStructUnionList() const // GETTER for RHS
    {
     return StructUnionList;
    }

    const std::string getStructUnionID() const  // GETTER for ec
    {
     return StructUnionID;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;  //is this right?
     StructUnionPointer->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl;
    // outputstream << IndentationLevel << "  Type: " << ConditionForRelation  << std::endl;
     StructUnionList->print(outputstream, IndentationLevel + "  ");
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }


};



#endif
