#include "../common/inc/ast.hpp"
#include "python_interpreter.hpp"
#include "python_interpreter_Translate_Statement_Functions.hpp"
#include "IndentationAdder.hpp"

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <cstdio>

//INDENTATIONLEVEL is the global variable that will be used for determining the number of indents req for python.
//The number of indents for python is 2 spaces

const std::string INDENTATIONLEVEL = "  ";
bool FirstTimeInsideFunction; // to know when to insert the global variables?

std::string findtype(const Node* input){
  return (input->getType());
}

std::vector<std::string> GlobalVariableList;


void TranslatingStatement(int NumberOfIndents, std::ofstream& output_python_file, const Node* ast_root){
  std::string Type = findtype(ast_root);  //StatementListNode
// const Statement* temp_state = dynamic_cast<const ReturnStatement*>(ast_root);

  //should there be a base case? for recursive purposes, as we have next statement as well?

  //BASE CASE, Where there is no statement inside...
  // if (ast_root->hasStatement() == false)
  // {
  //   output_python_file << INDENTATIONLEVEL;
  //   output_python_file << "pass" << std::endl;
  //   return;
  // }
  if(Type == "CompoundStatement")
  {
    const CompoundStatement* compound_state = dynamic_cast<const CompoundStatement*>(ast_root);
    TranslatingCompoundStatement(NumberOfIndents, output_python_file, compound_state);
  }

  if(Type == "ReturnStatement")
  {
    const ReturnStatement* return_state = dynamic_cast<const ReturnStatement*>(ast_root);
    //if(return_state->getExpression() != nullptr)
  //  {
    TranslatingReturnStatement(NumberOfIndents, output_python_file, return_state);
  //  }
  }
  else if(Type == "IfStatement")
  {
    const IfStatement* if_state = dynamic_cast<const IfStatement*>(ast_root);
    if(if_state->getIf() != nullptr)   //is it even necessary to check this?
    {
      TranslatingIfStatement(NumberOfIndents, output_python_file, if_state);
    }
  }
  else if(Type == "WhileStatement")
  {
    const WhileStatement* while_state = dynamic_cast<const WhileStatement*>(ast_root);
    if(while_state->getWhileStatement() != nullptr)   //is it even necessary to check this?
    {
      TranslatingWhileStatement(NumberOfIndents, output_python_file, while_state);

    }
  }

  else
  {
    AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
    Translating_Condition_Of_Statement(ast_root,output_python_file);
    output_python_file << "\n";
  }

}


void TranslatingFunctionCall(std::ofstream& output_python_file, const PostfixExpression* Function_Call)
{

  const identifierC* Function_Call_Identifier = dynamic_cast<const identifierC*>(Function_Call->getPostfixExpression()); //the getright of ParametersListNode is identifierC.
  const std::string* Function_Call_String = Function_Call_Identifier->getName();

  const std::string function_name = *Function_Call_String;
  output_python_file << function_name;
  output_python_file << "(";
  if (Function_Call->hasOthers() == true)
  {
    const Expression* function_call_Arg_exps = dynamic_cast<const Expression*>(Function_Call->getOthers());
    TranslatingFunctionCallArgumentList(output_python_file, function_call_Arg_exps);
  }
  output_python_file << ")";

}

void TranslatingFunctionCallArgumentList(std::ofstream& output_python_file, const Expression* function_call_Arg_exps)
{

  if ((function_call_Arg_exps->hasNext()) == true)
  {

    const Expression* temp_next_arg = dynamic_cast<const Expression*>(function_call_Arg_exps->getNext());
    TranslatingFunctionCallArgumentList(output_python_file,temp_next_arg);
    output_python_file << ",";
  }

  if ((function_call_Arg_exps->getExpression()->getType()) == "identifierC")
  {
    const identifierC* function_call_Arg_to_IdenC = dynamic_cast<const identifierC*>(function_call_Arg_exps->getExpression());
    output_python_file << *(function_call_Arg_to_IdenC->getName());
  }


  if ((function_call_Arg_exps->getExpression())->getType() == "IntConstant")
  {
    const IntConstant* function_call_Arg_to_IntC = dynamic_cast<const IntConstant*>(function_call_Arg_exps->getExpression());
    output_python_file << (function_call_Arg_to_IntC->getIntConstantValue());
  }

  if ((function_call_Arg_exps->getExpression())->getType() == "AdditiveExpression"){
    Translating_Condition_Of_Statement(function_call_Arg_exps->getExpression(), output_python_file);
  }

  if ((function_call_Arg_exps->getExpression())->getType() == "MultiplicativeExpression"){
    Translating_Condition_Of_Statement(function_call_Arg_exps->getExpression(), output_python_file);
  }


}


void TranslatingStatementList(int NumberOfIndents, std::ofstream& output_python_file, const StatementListNode* state_list_node)
{

 if (state_list_node->hasStatement() == true)
 {
    const StatementListNode* sln = dynamic_cast<const StatementListNode*>(state_list_node->getStatement());
    TranslatingStatementList(NumberOfIndents, output_python_file, sln);

  }
  if (state_list_node->hasNextStatement() == true)
  {
    //const StatementListNode* tmp = dynamic_cast<const StatementListNode*>(state_list_node->getNextStatement());
    TranslatingStatement(NumberOfIndents, output_python_file, state_list_node->getNextStatement());
  }

}



void TranslatingCompoundStatement(int NumberOfIndents, std::ofstream& output_python_file, const CompoundStatement* ast_root){
  //two cases, if list is not empty or if list is empty.
  if(FirstTimeInsideFunction == true)
  {
    FirstTimeInsideFunction = false;
    if (GlobalVariableList.size() != 0)
    {
      for (int i=0; i<GlobalVariableList.size(); i++)
      {
        output_python_file << INDENTATIONLEVEL;
        output_python_file << "global " << GlobalVariableList[i] << std::endl;
      }
    }
  }
  if(ast_root->hasNext() == true)
  {
    const DeclarationList* ast_root_to_declist = dynamic_cast<const DeclarationList*>(ast_root->getDeclaration());
    TranslatingDeclarationList(NumberOfIndents, output_python_file, ast_root_to_declist);
  }
  if(ast_root->hasLists() == true)
  {
    const StatementListNode* state_list_node = dynamic_cast<const StatementListNode*>(ast_root->getStatementList());
    TranslatingStatementList(NumberOfIndents, output_python_file, state_list_node);
  }
  else
  {
    AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
    output_python_file << "pass";
    output_python_file << std::endl;
    return void();
  }

}
void TranslatingDeclarationList(int NumberOfIndents, std::ofstream& output_python_file, const DeclarationList* ast_root_to_declist) //for local variables tho
{
  //AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
  if(ast_root_to_declist->hasPrevious()){
    const DeclarationList* dec = dynamic_cast<const DeclarationList*>(ast_root_to_declist->getPrevious());
    TranslatingDeclarationList(NumberOfIndents, output_python_file,dec);
  }


  if ((ast_root_to_declist->getPresent())->getType() == "Declaration") // is this just for variables? what about function calls or something
  {
    //output_python_file << INDENTATIONLEVEL;
    const Declaration* declist_to_Declaration = dynamic_cast<const Declaration*>(ast_root_to_declist->getPresent());
    const InitDeclaratorList* local_dec_to_init_dec_list = dynamic_cast<const InitDeclaratorList*>(((declist_to_Declaration)->getDeclaratorList()));
 // do we need to do an if statement check here?
    TranslatingLocalInitDecList(NumberOfIndents,output_python_file,local_dec_to_init_dec_list);

  }

}

void TranslatingLocalInitDecList(int NumberOfIndents,std::ofstream& output_python_file, const InitDeclaratorList* local_dec_to_init_dec_list)
{
  if(local_dec_to_init_dec_list->hasPrevious()){
    const InitDeclaratorList* dec_list = dynamic_cast<const InitDeclaratorList*>(((local_dec_to_init_dec_list)->getPrevious()));
    TranslatingLocalInitDecList(NumberOfIndents, output_python_file, dec_list);
  }
  const InitDeclarator* init_dec_list_to_InitDeclarator_Present = dynamic_cast<const InitDeclarator*>(local_dec_to_init_dec_list->getPresent());
  TranslatingLocalInitDeclarator(NumberOfIndents,output_python_file,init_dec_list_to_InitDeclarator_Present);

}

void TranslatingLocalInitDeclarator(int NumberOfIndents, std::ofstream& output_python_file, const InitDeclarator* init_dec_list_to_InitDeclarator_Present)
{
  if ((init_dec_list_to_InitDeclarator_Present->getDeclarator())->getType() == "identifierC")
  {
    const identifierC* Variable_C_Identifier = dynamic_cast<const identifierC*>(init_dec_list_to_InitDeclarator_Present->getDeclarator());
    const std::string* Variable_C_Name = Variable_C_Identifier->getName();
    const std::string Variable_C_Name_to_insert = *Variable_C_Name;
    if (init_dec_list_to_InitDeclarator_Present->hasInitialiser() == false)
    {
        AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
        output_python_file << Variable_C_Name_to_insert;
        output_python_file << " = 0" << std::endl;
    }
    else
    {
      //make it work for any value integer now...
      AppropiateAmountOfIndents(NumberOfIndents,output_python_file);
      output_python_file << Variable_C_Name_to_insert;


      if ((init_dec_list_to_InitDeclarator_Present->getInitialiser())->getType() == "IntConstant")
      {
        const IntConstant* InitDeclarator_Present_to_intconstant = dynamic_cast<const IntConstant*>(init_dec_list_to_InitDeclarator_Present->getInitialiser());
        const std::string IntConstantValue_To_Insert = std::to_string(InitDeclarator_Present_to_intconstant->getIntConstantValue());
        output_python_file << " = " << IntConstantValue_To_Insert << std::endl;
      }
      else if ((init_dec_list_to_InitDeclarator_Present->getInitialiser())->getType() == "identifierC"){
        const identifierC* InitDeclarator_Present_to_intconstant = dynamic_cast<const identifierC*>(init_dec_list_to_InitDeclarator_Present->getInitialiser());
        const std::string* name = InitDeclarator_Present_to_intconstant->getName();
        output_python_file << " = " << *name << std::endl;
      }
      else{
        output_python_file << " = ";
        Translating_Condition_Of_Statement(init_dec_list_to_InitDeclarator_Present->getInitialiser(), output_python_file);
        output_python_file << std::endl;
      }
    }
  }
}

void TranslatingFunctionArgumentIndividually(std::ofstream& output_python_file, const Node* individual_node)
{
  const ParametersListNode* individual_node_becomes_parameter_list_node = dynamic_cast<const ParametersListNode*>(individual_node);
  const identifierC* Argument_C_Identifier = dynamic_cast<const identifierC*>(individual_node_becomes_parameter_list_node->getRight()); //the getright of ParametersListNode is identifierC.
  const std::string* ArgumentName = Argument_C_Identifier->getName();

  const std::string ArgumentName_to_insert = *ArgumentName;

  output_python_file << ArgumentName_to_insert;

}

void TranslatingFunctionArgumentList(std::ofstream& output_python_file, const Node* arg_def)
{


  const ParameterList* arg_def_becomes_parameter_list = dynamic_cast<const ParameterList*>(arg_def);

  if (arg_def_becomes_parameter_list->hasLeft() == true)
  {
    TranslatingFunctionArgumentList(output_python_file,arg_def_becomes_parameter_list->getLeft());
    output_python_file << ",";
  }

  TranslatingFunctionArgumentIndividually(output_python_file,arg_def_becomes_parameter_list->getRight());

}

void TranslatingFunctionName(std::ofstream& output_python_file, const Node* func_def)
{

  const Variable* Func_name_node = dynamic_cast<const Variable*>(func_def);
  const identifierC* Func_name_node_Identifier_C = dynamic_cast<const identifierC*>(Func_name_node->getVariable_Identifier());

  const std::string* FunctionName = Func_name_node_Identifier_C->getName();

  const std::string FunctionName_ToInsert = *FunctionName;

  output_python_file << FunctionName_ToInsert;

  output_python_file << "(";

  if (Func_name_node->hasArray_Information() == true)
  {
    TranslatingFunctionArgumentList(output_python_file, Func_name_node->getArray_Information());
  }

  output_python_file << ")";

}

void TranslatingFunctionDefinition(std::ofstream& output_python_file, const FunctionDefinition* func_def)  //translating the function definition itself here.
{

  output_python_file << "def ";
  TranslatingFunctionName(output_python_file,func_def->getNodeName());

  output_python_file << ":" << "\n";

  const CompoundStatement* Comp_Statement = dynamic_cast<const CompoundStatement*>(func_def->getContentsOfFunction());
  TranslatingCompoundStatement(1, output_python_file, Comp_Statement);
  output_python_file << std::endl;


}

void TranslatingInitDeclarator(std::ofstream& output_python_file,const InitDeclarator* init_dec_list_to_InitDeclarator_Present)
{

  if ((init_dec_list_to_InitDeclarator_Present->getDeclarator())->getType() == "identifierC")
  {
    const identifierC* Variable_C_Identifier = dynamic_cast<const identifierC*>(init_dec_list_to_InitDeclarator_Present->getDeclarator());
    const std::string* Variable_C_Name = Variable_C_Identifier->getName();
    const std::string Variable_C_Name_to_insert = *Variable_C_Name;
    if (init_dec_list_to_InitDeclarator_Present->hasInitialiser() == false)
    {
        output_python_file << Variable_C_Name_to_insert;
        GlobalVariableList.push_back(Variable_C_Name_to_insert);
        output_python_file << " = 0" << std::endl;
    }
    else
    {
      //make it work for any value integer now...
      output_python_file << Variable_C_Name_to_insert;
      GlobalVariableList.push_back(Variable_C_Name_to_insert);

      if ((init_dec_list_to_InitDeclarator_Present->getInitialiser())->getType() == "IntConstant")
      {
        const IntConstant* InitDeclarator_Present_to_intconstant = dynamic_cast<const IntConstant*>(init_dec_list_to_InitDeclarator_Present->getInitialiser());
        const std::string IntConstantValue_To_Insert = std::to_string(InitDeclarator_Present_to_intconstant->getIntConstantValue());
        output_python_file << " = " << IntConstantValue_To_Insert << std::endl;
      }

    }

  }

}

void TranslatingInitDecList(std::ofstream& output_python_file, const InitDeclaratorList* outside_declaration_to_init_dec_list)
{
  const InitDeclarator* init_dec_list_to_InitDeclarator_Present = dynamic_cast<const InitDeclarator*>(outside_declaration_to_init_dec_list->getPresent());
  TranslatingInitDeclarator(output_python_file,init_dec_list_to_InitDeclarator_Present);
}


void TranslatingOutsideDeclaration(std::ofstream& output_python_file, const Declaration* outside_declaration)
{
  if (outside_declaration->getType() == "Declaration") // is this just for variables? what about function calls or something
  {
    const InitDeclaratorList* outside_declaration_to_init_dec_list = dynamic_cast<const InitDeclaratorList*>(outside_declaration->getDeclaratorList());

//    std::cout << "outside_declaration_to_init_dec_list's type of Present: " << (outside_declaration_to_init_dec_list->getPresent())->getType() << '\n'; //declarator_list;  declarator_specifier;
    //std::cout << "outside_declaration_to_init_dec_list's type of Previous: " << (outside_declaration_to_init_dec_list->getPrevious())->getType() << '\n'; //declarator_list;  declarator_specifier;
  //  std::cout << "******************************************" << '\n';
  //  if (outside_declaration-)
    TranslatingInitDecList(output_python_file,outside_declaration_to_init_dec_list);


    //Do we need to deal with previous or not? Most likley yes, using recursion

  }




}


void Translatingindvnode(std::ofstream& output_python_file, const Node* ast_root)  //translating the function itself here.
{
  if(ast_root->getType() != "FunctionDefinition")
  {
    if (ast_root->getType() == "Declaration")
    {
      const Declaration* outside_declaration = dynamic_cast<const Declaration*>(ast_root);
      TranslatingOutsideDeclaration(output_python_file,outside_declaration);
    }
  }

  if(ast_root->getType() == "FunctionDefinition")
  {
    FirstTimeInsideFunction = true;
    const FunctionDefinition* func_def = dynamic_cast<const FunctionDefinition*>(ast_root);
    TranslatingFunctionDefinition(output_python_file, func_def);
  }

}


void TranslatingAST(const std::vector<const Node*>& ast_roots, std::ofstream& output_python_file ) {
  for (const Node* ast : ast_roots) {
    Translatingindvnode(output_python_file, ast);
  }

}


int python_Translating_main(const std::string& name_of_source_file, const std::string& name_of_destination_file){
  FILE* inputfile;

  if(!(inputfile = fopen(name_of_source_file.c_str(), "r"))){
    std::cerr << "Cannot open: " << name_of_source_file << std::endl;
    return 1;
  }

  inputfile = fopen(name_of_source_file.c_str(), "r");

  // Set file Flex and Yacc will read from.
  yyset_in(inputfile);

  // Prepare python output file.
  std::ofstream output_python_file;
  output_python_file.open(name_of_destination_file);

  // Produce translation AST tree.
  std::vector<const Node*> ast_roots = parseAST();


  TranslatingAST(ast_roots, output_python_file); //TRIGGER THE TRANSLATION of the TREE.

  output_python_file << std::endl << std::endl;
  output_python_file << "if __name__ == '__main__':" << std::endl  //prints stuff
         << INDENTATIONLEVEL << "import sys" << std::endl
         << INDENTATIONLEVEL << "ret = main()" << std::endl
         << INDENTATIONLEVEL << "sys.exit(ret)" << std::endl;


  fclose(inputfile);
  output_python_file.close();
  return 0;
}
