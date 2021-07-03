#ifndef ast_hpp
#define ast_hpp

// Include headers in ast that contains the classes for the tree nodes.
#include "ast/ast_node.hpp"
#include "ast/function_declaration.hpp"
#include "ast/declaration_specifier.hpp"
#include "ast/Struct_Or_Union.hpp"
#include "ast/Struct_Declaration.hpp"
#include "ast/Enum_Declaration_List_Node.hpp"
#include "ast/Enum_Declaration.hpp"
#include "ast/Constant_Expressions.hpp"

#include "ast/TranslateConstants.hpp"
#include "ast/TranslateVariables.hpp"

#include "ast/Unary_Expression.hpp"
#include "ast/Rest_Of_Expressions.hpp"
#include "ast/Logical_Expressions.hpp"
#include "ast/Algebraic_Expressions.hpp"
#include "ast/loop_declaration.hpp"
#include "ast/statements.hpp"
#include "ast/point.hpp"
#include "ast/type_qualifier.hpp"



#include <vector>

extern std::vector<const Node*> parseAST();
extern void yyset_in(FILE* fd);

#endif
