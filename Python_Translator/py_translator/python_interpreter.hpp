#ifndef python_translator_hpp
#define python_translator_hpp

#include <string>
#include "../common/inc/ast.hpp"
#include "python_interpreter_Translate_Statement_Functions.hpp"



//this are all the higher level functions
std::string findtype(const Node* input);

void TranslatingFunctionDefinition(std::ofstream& output_python_file, const FunctionDefinition* func_def);
void TranslatingFunctionName(std::ofstream& output_python_file, const Node* func_def);

void TranslatingLocalInitDecList(int NumberOfIndents, std::ofstream& output_python_file, const InitDeclaratorList* outside_declaration_to_init_dec_list);

void TranslatingCompoundStatement(int NumberOfIndents, std::ofstream& output_python_file, const CompoundStatement* ast_root);

void TranslatingLocalInitDeclarator(int NumberOfIndents, std::ofstream& output_python_file, const InitDeclarator* init_dec_list_to_InitDeclarator_Present);


void TranslatingDeclarationList(int NumberOfIndents, std::ofstream& output_python_file, const DeclarationList* ast_root_to_declist);

int python_Translating_main(const std::string& name_of_source_file, const std::string& name_of_destination_file); //return 0 if successful compilation.

void TranslatingAST(const std::vector<const Node*>& ast_roots, std::ofstream& output_python_file );

void Translatingindvnode(std::ofstream& output_python_file, const Node* ast_root);

void TranslatingFunctionArgumentIndividually(std::ofstream& output_python_file, const Node* individual_node);

void TranslatingFunctionArgumentList(std::ofstream& output_python_file, const Node* arg_def);
void TranslatingFunctionCallArgumentList(std::ofstream& output_python_file, const Expression* function_call_Arg_exps);

void TranslatingFuncContents(std::ofstream& output_python_file, const CompoundStatement* ast_root);

void TranslatingListOfStatements(std::ofstream& output_python_file, const StatementListNode* ast_root);

void TranslatingExpression(std::ofstream& output_python_file, const IntConstant* ast_root);

void TranslatingStatementList(int NumberOfIndents,std::ofstream& output_python_file, const StatementListNode* state_node);

void TranslatingInitDecList(std::ofstream& output_python_file, const InitDeclaratorList* outside_declaration_to_init_dec_list);

void TranslatingInitDeclarator(std::ofstream& output_python_file,const InitDeclarator* init_dec_list_to_InitDeclarator_Present);

void TranslatingFunctionCall(std::ofstream& output_python_file, const PostfixExpression* Function_Call);




void TranslatingStatement(int NumberOfIndents, std::ofstream& output_python_file, const Node* ast_root);
void TranslatingOutsideDeclaration(std::ofstream& output_python_file, const Declaration* outside_declaration);  //translating the function itself here.


#endif
