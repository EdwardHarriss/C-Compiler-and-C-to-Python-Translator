%code requires{
  #include "../inc/ast.hpp"
  #include <vector>

  #include <cassert>

//  extern const AndExpression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

  extern std::vector<const Node*> ast_roots;

  extern void yyset_in(FILE* inputfile);
}

// Represents the value associated with any kind of
// AST node.
%union{
  int int_constant;
  float float_constant;
  char *char_constant;
  std::string *str;
  const Node* node;
}

%type <node> external_declaration function_definition declaration declarator declaration_list compound_statement init_declarator_list
%type <node> struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration type_specifier_node declaration_specifiers
%type <node> specifier_qualifier_list struct_declarator_list constant_expression conditional_expression logical_or_expression expression
%type <node> assignment_expression unary_expression postfix_expression cast_expression type_name enum_specifier struct_declarator
%type <node> logical_and_expression inclusive_or_expression abstract_declarator primary_expression argument_expression_list pointer
%type <node> direct_declarator parameter_type_list identifier_list type_qualifier_list parameter_list parameter_declaration direct_abstract_declarator
%type <node> statement labeled_statement expression_statement selection_statement iteration_statement jump_statement statement_list
%type <node> multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression
%type <node> init_declarator initializer enumerator_list enumerator storage_class_specifier type_specifier type_qualifier function_declaration


%type <node> CONST VOLATILE
%type <str> C_IDENTIFIER CASE DEFAULT
%type <int_constant> INT_CONSTANT
%type <float_constant> FLOAT_CONST
%type <char_constant> CHAR_CONST
%type <str> unary_operator assignment_operator


%token C_IDENTIFIER INT_CONSTANT FLOAT_CONST CHAR_CONST SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit

%%

translation_unit
  : external_declaration                           { ast_roots.push_back($1); }
  | translation_unit external_declaration          { ast_roots.push_back($2); }
  ;

external_declaration
  : function_definition                            { $$ = $1; }
  | declaration /*(1)*/                            { $$ = $1; }
  ;

function_declaration
  : declaration_specifiers declarator parameter_list ';'               { $$ = new FunctionDeclaration($1, $2, $3); }

function_definition /*(2)*/
  : declaration_specifiers declarator parameter_list compound_statement  { $$ = new FunctionDefinition($1, $2, $3, $4); }
  | declaration_specifiers declarator compound_statement                   { $$ = new FunctionDefinition($1, $2, nullptr, $3); }
  | declarator parameter_list compound_statement                         { $$ = new FunctionDefinition(NULL,$1, $2, $3);}
  | declarator compound_statement                                          { $$ = new FunctionDefinition(NULL, $1,nullptr, $2); }
  ;

// (1) going down the declaration rabit hole

declaration
  : declaration_specifiers ';'                        { $$ = new Declaration($1, NULL); }
  | declaration_specifiers init_declarator_list ';'   { $$ = new Declaration($1, $2); }
  | init_declarator_list ';'                          { $$ = new Declaration(nullptr, $1); }
  ;

declaration_specifiers
  : storage_class_specifier                             { $$ = $1; }
  | storage_class_specifier declaration_specifiers      { $$ = new DeclarationSpecifier($1, $2); }
  | type_specifier                                      { $$ = $1; }
  | type_specifier declaration_specifiers               { $$ = new DeclarationSpecifier($1, $2); }
  | type_qualifier                                      { $$ = $1; }
  | type_qualifier declaration_specifiers               { $$ = new DeclarationSpecifier($1, $2); }
  ;

init_declarator_list
	: init_declarator                                    { $$ = new InitDeclaratorList(nullptr, $1);}
	| init_declarator_list ',' init_declarator           { $$ = new InitDeclaratorList($1, $3);}
	;

init_declarator
	: declarator                                 { $$ = new InitDeclarator($1, nullptr);}
	| declarator '=' initializer                 { $$ = new InitDeclarator($1, $3);}
	;

initializer
	: assignment_expression                  { $$ = $1; }
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

storage_class_specifier
  : TYPEDEF                             { $$ = new Specifier("typedef"); }
  | EXTERN                              { $$ = new Specifier("extern"); }
  | STATIC                              { $$ = new Specifier("static"); }
  | AUTO                                { $$ = new Specifier("auto"); }
  | REGISTER                            { $$ = new Specifier("register"); }
  ;

type_specifier
  : VOID                                { $$ = new Specifier("void"); }
  | CHAR                                { $$ = new Specifier("char"); }
  | SHORT                               { $$ = new Specifier("short"); }
  | INT                                 { $$ = new Specifier("int"); }
  | LONG                                { $$ = new Specifier("long"); }
  | FLOAT                               { $$ = new Specifier("float"); }
  | DOUBLE                              { $$ = new Specifier("double"); }
  | SIGNED                              { $$ = new Specifier("signed"); }
  | UNSIGNED                            { $$ = new Specifier("unsigned"); }

type_specifier_node
  : struct_or_union_specifier           { $$ = $1; }
  | enum_specifier                      { $$ = $1; }
  ;

type_qualifier
  : CONST                               { $$ = new Specifier("const"); }
  | VOLATILE                            { $$ = new Specifier("volatile"); }

struct_or_union_specifier
  : struct_or_union C_IDENTIFIER '{' struct_declaration_list '}'    { $$ = new StructUnion($1 , *$2, $4); }
  | struct_or_union '{' struct_declaration_list '}'                 { $$ = new StructUnion($1 , $3); }
  | struct_or_union C_IDENTIFIER                                    { $$ = new StructUnion($1 , *$2); }
  ;

struct_or_union
  : STRUCT                              { $$ = new Specifier("struct"); }
  | UNION                               { $$ = new Specifier("union"); }
  ;

struct_declaration_list
	: struct_declaration                                   { $$ = $1; }
	| struct_declaration_list struct_declaration           { $$ = $2; }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'   { $$ = new StructDeclaration($1, $2); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list               { $$ = $2; }
	| type_specifier                                        { $$ = $1; }
	| type_qualifier specifier_qualifier_list               { $$ = $2; }
	| type_qualifier                                        { $$ = $1; }
	;

struct_declarator_list
  : struct_declarator                                    { $$ = $1; }
  | struct_declarator_list ',' struct_declarator         { $$ = $3; }
  ;

struct_declarator
	: declarator                                     { $$ = $1; }
	| ':' constant_expression                         { $$ = new ConstantExpression($2); }
  | declarator ':' constant_expression               { $$ = new ConstantExpression($1, $3);}
	;

enum_specifier
  : ENUM '{' enumerator_list '}'                    { $$ = $3; }
  | ENUM C_IDENTIFIER '{' enumerator_list '}'       { $$ = $4; }
  ;

enumerator_list
  : enumerator                                    { $$ = new EnumDeclarationListNode($1, nullptr); }
  | enumerator_list ',' enumerator                { $$ = new EnumDeclarationListNode($1, $3); }

enumerator
  : C_IDENTIFIER                              { $$ = new EnumDeclaration(*$1, nullptr); delete $1; }
  | C_IDENTIFIER '=' constant_expression      { $$ = new EnumDeclaration(*$1, $3); delete $1; }

constant_expression
	: conditional_expression                     { $$ = $1; }
	;

conditional_expression
	: logical_or_expression                                              { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression    { $$ = new ConditionalExpression($1, $3, $5); }
	;

expression
	: assignment_expression                                  { $$ = new Expression(nullptr, $1); }
	| expression ',' assignment_expression                   { $$ = new Expression($1, $3); }
	;

unary_expression
	: postfix_expression                   { $$ = $1; }
	| INC_OP unary_expression              { $$ = new UnaryExpression("++", $2); }
	| DEC_OP unary_expression              { $$ = new UnaryExpression("--", $2); }
	| unary_operator cast_expression       { $$ = new UnaryExpression($1, $2); }
	| SIZEOF unary_expression              { $$ = new UnaryExpression("sizeof", $2); }
	| SIZEOF '(' type_name ')'             { $$ = new UnaryExpression("sizeof", $3); }
	;

unary_operator
	: '&'              { $$ = new std::string("&"); }
	| '*'              { $$ = new std::string("*"); }
	| '+'              { $$ = new std::string("+"); }
	| '-'              { $$ = new std::string("-"); }
	| '~'              { $$ = new std::string("~"); }
	| '!'              { $$ = new std::string("!"); }
	;

cast_expression
	: unary_expression                       { $$ = $1; }
	| '(' type_name ')' cast_expression      { $$ = $2; }
	;

assignment_operator
  : '='          { $$ = new std::string("="); }
	| RIGHT_ASSIGN { $$ = new std::string(">>="); }
	| LEFT_ASSIGN  { $$ = new std::string("<<="); }
	| ADD_ASSIGN   { $$ = new std::string("+="); }
  | SUB_ASSIGN   { $$ = new std::string("-="); }
  | MUL_ASSIGN   { $$ = new std::string("*="); }
  | DIV_ASSIGN   { $$ = new std::string("/="); }
  | MOD_ASSIGN   { $$ = new std::string("%="); }
  | AND_ASSIGN   { $$ = new std::string("&="); }
  | XOR_ASSIGN   { $$ = new std::string("^="); }
  | OR_ASSIGN    { $$ = new std::string("|="); }
  ;

inclusive_or_expression
  : exclusive_or_expression                              { $$ = $1; }
  | inclusive_or_expression '|' exclusive_or_expression  { $$ = new InclusiveOrExpression($1, $3); }
  ;


logical_or_expression
  : logical_and_expression                              { $$ = $1; }
  | logical_or_expression OR_OP logical_and_expression  { $$ = new LogicalOrExpression($1, $3); }
  ;

logical_and_expression
  : inclusive_or_expression                                { $$ = $1; }
  | logical_and_expression AND_OP inclusive_or_expression  { $$ = new LogicalAndExpression($1, $3); }
  ;

type_name
	: specifier_qualifier_list                               { $$ = $1; }
	| specifier_qualifier_list abstract_declarator           { $$ = $2; }
	;

postfix_expression
	: primary_expression                                           { $$ = $1; }
	| postfix_expression '[' expression ']'                        { $$ = new PostfixExpression($1, "0",$3); }
	| postfix_expression '(' ')'                                   { $$ = new PostfixExpression($1, "function", nullptr); }
	| postfix_expression '(' argument_expression_list ')'          { $$ = new PostfixExpression($1, "function", $3); }
  | postfix_expression '(' expression ')'                         { $$ = new PostfixExpression($1, "function", $3); }
	| postfix_expression '.' C_IDENTIFIER                            { $$ = new PostfixExpressionStr($1, ".", $3); }
	| postfix_expression PTR_OP C_IDENTIFIER                       { $$ = new PostfixExpressionStr($1, "->", $3); }
	| postfix_expression INC_OP                                    { $$ = new PostfixExpression($1, "++", nullptr); }
	| postfix_expression DEC_OP                                    { $$ = new PostfixExpression($1, "--", nullptr); }
	;

primary_expression
	: C_IDENTIFIER                         { $$ = new identifierC($1); }
	| INT_CONSTANT                         { $$ = new IntConstant($1);}
	| FLOAT_CONST                          { $$ = new FloatConstant($1);}
  | CHAR_CONST                           { $$ = new CharConstant($1);}
  | '(' expression ')'                          { $$ = $2;}
	;

argument_expression_list
	: assignment_expression                                  { $$ = $1;}
	| argument_expression_list ',' assignment_expression     { $$ = $1;}
	;

assignment_expression
	: conditional_expression                                         { $$ = $1;}
	| unary_expression assignment_operator assignment_expression     { $$ = new AssignmentExpression($1, $2, $3); }
	;

// (2) going down the Declarator rabit hole

declarator
  : pointer direct_declarator           { $$ = new Variable( $2, "pointer", nullptr); }
  | direct_declarator                   { $$ = $1; }

direct_declarator
  : C_IDENTIFIER                        { $$ = new identifierC($1); }
  | '(' declarator ')'                  { $$ = $2; }
  | direct_declarator '[' constant_expression ']'   { $$ = new Variable( $1, "array", $3); }
	| direct_declarator '[' ']'                       { $$ = new Variable( $1, "array", nullptr); }
	| direct_declarator '(' parameter_list ')'   { $$ = new Variable( $1, "function", $3); }
	| direct_declarator '(' identifier_list ')'       { $$ = new Variable( $1, "function", $3); }
	| direct_declarator '(' ')'                       { $$ = new Variable( $1, "function", nullptr); }
  ;

pointer
	: '*'                                  { $$ = new Pointer(nullptr); }
	| '*' type_qualifier_list              { $$ = new Pointer($2); }
	| '*' pointer                          { $$ = new Pointer(nullptr); }
	| '*' type_qualifier_list pointer      { $$ = new Pointer($2); }
	;

type_qualifier_list
	: type_qualifier                         { $$ = $1; }
	| type_qualifier_list type_qualifier     { $$ = $2; }
	;

type_qualifier
	: CONST                      { $$ = new TypeQualifier("const"); }
	| VOLATILE                   { $$ = new TypeQualifier("volatile"); }
	;

parameter_type_list
	: parameter_list                      { $$ = $1; }
	| parameter_list ',' ELLIPSIS         { $$ = $1; }
	;

parameter_list
	: parameter_declaration                      { $$ = new ParameterList(nullptr, $1); }
	| parameter_list ',' parameter_declaration   { $$ = new ParameterList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator            { $$ = new ParametersListNode($1, $2); }
	| declaration_specifiers abstract_declarator   { $$ = new ParametersListNode($1, $2); }
	| declaration_specifiers                       { $$ = new ParametersListNode($1, nullptr); }
	;

abstract_declarator
	: pointer                                    { $$ = $1; }
  | direct_abstract_declarator                 { $$ = $1; }
	| pointer direct_abstract_declarator         { $$ = new PointerAbstractDeclarator($2); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'                            { $$ = new AbstractDeclarator($2); }
	| '[' ']'                                                { $$ = new AbstractDeclarator(nullptr); }
	| '[' constant_expression ']'                            { $$ = new AbstractDeclarator($2); }
	| direct_abstract_declarator '[' ']'                         { $$ = $1; }
	| direct_abstract_declarator '[' constant_expression ']'     { $$ = new AbstractDeclarator($3); }
	| '(' ')'                                                    { $$ = new AbstractDeclarator(nullptr); }
	| '(' parameter_type_list ')'                              { $$ = new AbstractDeclarator($2); }
	| direct_abstract_declarator '(' ')'                             { $$ = $1; }
	| direct_abstract_declarator '(' parameter_type_list ')'          { $$ = new AbstractDeclarator($3); }
	;

identifier_list
	: C_IDENTIFIER                        { $$ = new VariableNorm($1); }
	| identifier_list ',' C_IDENTIFIER      {$$ = new VariableNormNode($1, $3);}
	;

//looking at statement lists

statement
	: compound_statement     { $$ = $1; }
	| expression_statement   { $$ = $1; }
	| selection_statement    { $$ = $1; }
	| iteration_statement    { $$ = $1; }
	| jump_statement         { $$ = $1; }
	;

labeled_statement
	: C_IDENTIFIER ':' statement                 { $$ = new LabeledStatement($1, nullptr, $3); }
	| CASE constant_expression ':' statement     { $$ = new LabeledStatement($1, $2, $4); }
	| DEFAULT ':' statement                      { $$ = new LabeledStatement($1, nullptr, $3); }
	;

compound_statement
	: '{' '}'                                     { $$ = new CompoundStatement(nullptr, nullptr); }
	| '{' statement_list '}'                      { $$ = new CompoundStatement(nullptr, $2); }
	| '{' declaration_list '}'                    { $$ = new CompoundStatement($2, nullptr); }
	| '{' declaration_list statement_list '}'     { $$ = new CompoundStatement($2, $3); }
	;

declaration_list
	: declaration                      { $$ = new DeclarationList(nullptr, $1); }
	| declaration_list declaration     { $$ = new DeclarationList($1, $2); }
	;

statement_list
	: statement                        { $$ = new StatementListNode(nullptr, $1); }
	| statement_list statement         { $$ = new StatementListNode($1, $2); }
	;

expression_statement
	: ';'                        { $$ = new EmptyExpression(); }
	| expression ';'             { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement                    { $$ = new IfStatement($3, $5, nullptr); }
	| IF '(' expression ')' statement ELSE statement     { $$ = new IfStatement($3, $5, $7); }
	| SWITCH '(' expression ')' statement                { $$ = new SwitchStatement($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement                     { $$ = new WhileStatement($3, $5); }
	| DO statement WHILE '(' expression ')' ';'              { $$ = new DoStatement($2, $5); }
	| FOR '(' expression_statement expression_statement ')' statement        { $$ = new ForStatement($3, $4, nullptr, $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement       { $$ = new ForStatement($3, $4, $5, $7); }
	;

jump_statement
	: GOTO C_IDENTIFIER ';'              { $$ = new GoToStatement($2); }
	| CONTINUE ';'                       { $$ = new ContinueStatement(); }
	| BREAK ';'                          { $$ = new BreakStatement(); }
  | RETURN ';'                         { $$ = new ReturnStatement(nullptr); }
  | RETURN '(' expression ')' ';'      { $$ = new ReturnStatement($3); }
  | RETURN expression ';'              { $$ = new ReturnStatement($2); }
	;


multiplicative_expression
  : unary_expression                                { $$ = $1; }
  | multiplicative_expression '*' unary_expression  { $$ = new MultiplicativeExpression($1, "*", $3); }
  | multiplicative_expression '/' unary_expression  { $$ = new MultiplicativeExpression($1, "/", $3); }
  | multiplicative_expression '%' unary_expression  { $$ = new MultiplicativeExpression($1, "%", $3); }
  ;

additive_expression
  : multiplicative_expression                          { $$ = $1; }
  | additive_expression '+' multiplicative_expression  { $$ = new AdditiveExpression($1, "+", $3); }
  | additive_expression '-' multiplicative_expression  { $$ = new AdditiveExpression($1, "-", $3); }
  ;

shift_expression
  : additive_expression                            { $$ = $1; }
  | shift_expression LEFT_OP additive_expression   { $$ = new ShiftExpression($1, "<<", $3); }
  | shift_expression RIGHT_OP additive_expression  { $$ = new ShiftExpression($1, ">>", $3); }
  ;

relational_expression
  : shift_expression                              { $$ = $1; }
  | relational_expression '<' shift_expression    { $$ = new RelationalExpression($1, "<", $3); }
  | relational_expression '>' shift_expression    { $$ = new RelationalExpression($1, ">", $3); }
  | relational_expression LE_OP shift_expression  { $$ = new RelationalExpression($1, "<=", $3); }
  | relational_expression GE_OP shift_expression  { $$ = new RelationalExpression($1, ">=", $3); }
  ;

equality_expression
  : relational_expression                            { $$ = $1; }
  | equality_expression EQ_OP relational_expression  { $$ = new EqualityExpression($1, "==", $3); }
  | equality_expression NE_OP relational_expression  { $$ = new EqualityExpression($1, "!=", $3); }
  ;

and_expression
  : equality_expression                     { $$ = $1; }
  | and_expression '&' equality_expression  { $$ = new AndExpression($1, $3); }
  ;

exclusive_or_expression
  : and_expression                              { $$ = $1; }
  | exclusive_or_expression '^' and_expression  { $$ = new ExclusiveOrExpression($1, $3); }

%%

std::vector<const Node*> ast_roots;

std::vector<const Node*> parseAST() {
  yyparse();
  return ast_roots;
}
