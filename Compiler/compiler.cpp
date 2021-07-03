#include "compiler.hpp"
#include "../common/inc/ast.hpp"
#include "compiler_class.hpp"

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

//defining the global allocations

GlobalVariables global_variables;
FunctionDeclarations function_declarations;
RegisterDeclarations register_declarations;
MemoryDeclaration memory;
LocalVariables local_variables;
EnumDeclarationCompiler enums;


//globalvariables
int stack_size;
static int makeNameUnq=0;
std::string function_name;
int no_arguments;
std::vector<std::string>arg_name;
std::string function_return;
std::vector<std::string>loop_names;

//functions

std::string makeName(std::string base){
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}

std::string getTypes(const Node* ast) {
  return ast->getType();
}

int CountTerms(std::ofstream& output, int no, const Node* ast){
  const Expression* expr = dynamic_cast<const Expression*>(ast);
  std::string tmp = getTypes(expr->getExpression());
  if(tmp == "IntConstant"){
    const IntConstant* val = dynamic_cast<const IntConstant*>(expr->getExpression());
    output << "li $" << (4+(no-1)) << "," << val->getIntConstantValue() << std::endl;
  }
  if(expr->getNext() != nullptr){
    no ++;
    no = CountTerms(output, no, expr->getNext());
  }
  return no;
}

int CountArguments(int no, const Node* ast){
  if(ast->getType() == "ParameterList"){
    no++;
    const ParameterList* tmp = dynamic_cast<const ParameterList*>(ast);
    if(tmp->hasLeft()){
      no = CountArguments(no, tmp->getLeft());
    }

    const ParametersListNode* node = dynamic_cast<const ParametersListNode*>(tmp->getRight());
    const identifierC* var_name = dynamic_cast<const identifierC*>(node->getRight());
    arg_name.push_back(*(var_name->getName()));

  }

  if(ast->getType() == "Variable"){
    const Variable* tmp = dynamic_cast<const Variable*>(ast);
    if(tmp->getArray_Information() != nullptr){
      no = CountArguments(no, tmp->getArray_Information());
    }
  }
  return no;
}

bool CallFunction(bool exit_token, const Node* ast){

  if(ast->getType() == "FunctionDefinition"){
    const FunctionDefinition* func = dynamic_cast<const FunctionDefinition*>(ast);
    exit_token = CallFunction(exit_token, func->getContentsOfFunction());
  }

  if(ast->getType() == "CompoundStatement"){
    const CompoundStatement* tmp = dynamic_cast<const CompoundStatement*>(ast);
    if(tmp->hasNext()){
      exit_token = CallFunction(exit_token, tmp->getDeclaration());
    }
    if(tmp->hasLists()){
      exit_token = CallFunction(exit_token, tmp->getStatementList());
    }
  }

  if(ast->getType() == "StatementListNode"){
    const StatementListNode* tmp = dynamic_cast<const StatementListNode*>(ast);
    if(tmp->getStatement() != nullptr){
      exit_token = CallFunction(exit_token, tmp->getStatement());
    }
    exit_token = CallFunction(exit_token, tmp->getNextStatement());
  }

  if(ast->getType() == "Declaration"){
    const Declaration* tmp = dynamic_cast<const Declaration*>(ast);
    exit_token = CallFunction(exit_token, tmp->getDeclaratorList());
  }

  if(ast->getType() == "DeclarationList"){
    const DeclarationList* tmp = dynamic_cast<const DeclarationList*>(ast);
    if(tmp->hasPrevious()){
      exit_token = CallFunction(exit_token, tmp->getPrevious());
    }
    exit_token = CallFunction(exit_token, tmp->getPresent());
  }

  if(ast->getType() == "InitDeclaratorList"){
    const InitDeclaratorList* tmp = dynamic_cast<const InitDeclaratorList*>(ast);
    if(tmp->hasPrevious()){
      exit_token = CallFunction(exit_token, tmp->getPrevious());
    }
    exit_token = CallFunction(exit_token, tmp->getPresent());
  }

  if(ast->getType() == "InitDeclarator"){
    const InitDeclarator* tmp = dynamic_cast<const InitDeclarator*>(ast);
    if(tmp->getInitialiser() != nullptr){
      exit_token = CallFunction(exit_token, tmp->getInitialiser());
    }
    exit_token = CallFunction(exit_token, tmp->getDeclarator());
  }

  if(ast->getType() == "ReturnStatement"){
    const ReturnStatement* tmp = dynamic_cast<const ReturnStatement*>(ast);
    if(tmp->HasExpression()){
      exit_token = CallFunction(exit_token, tmp->getExpression());
    }
  }

  if(ast->getType() == "AdditiveExpression"){
    const AdditiveExpression* tmp = dynamic_cast<const AdditiveExpression*>(ast);
    if(getTypes(tmp->getRightSideOfExpression()) == "PostfixExpression"){
      exit_token = CallFunction(exit_token, tmp->getRightSideOfExpression());
    }
    if(getTypes(tmp->getLeftSideOfExpression()) == "PostfixExpression"){
      exit_token = CallFunction(exit_token, tmp->getLeftSideOfExpression());
    }
  }

  if(ast->getType() == "Expression"){
    const Expression* tmp = dynamic_cast<const Expression*>(ast);
    exit_token = CallFunction(exit_token, tmp->getExpression());
  }

  if(ast->getType() == "IfStatement"){
    const IfStatement* tmp = dynamic_cast<const IfStatement*>(ast);
    exit_token = CallFunction(exit_token, tmp->getCondition());
    exit_token = CallFunction(exit_token, tmp->getIf());
    if(tmp->getELSE() != nullptr){
      exit_token = CallFunction(exit_token, tmp->getELSE());
    }
  }

  if(ast->getType() == "WhileStatement"){
    const WhileStatement* tmp = dynamic_cast<const WhileStatement*>(ast);
    exit_token = CallFunction(exit_token, tmp->getWhileParameter());
    exit_token = CallFunction(exit_token, tmp->getWhileStatement());
  }

  if(ast->getType() == "ForStatement"){
    const ForStatement* tmp = dynamic_cast<const ForStatement*>(ast);
    exit_token = CallFunction(exit_token, tmp->getExpressionStatement1());
    exit_token = CallFunction(exit_token, tmp->getExpressionStatement2());
    exit_token = CallFunction(exit_token, tmp->getForStatement());
    exit_token = CallFunction(exit_token, tmp->getExpression());
  }

  if(ast->getType() == "PostfixExpression"){
    const PostfixExpression* tmp = dynamic_cast<const PostfixExpression*>(ast);
    if(tmp->getTypes() == "function"){
      return true;
    }
  }

  if(ast->getType() == "UnaryExpression"){
    const UnaryExpression* tmp = dynamic_cast<const UnaryExpression*>(ast);
    if(getTypes(tmp->getUnaryExpression()) == "PostfixExpression"){
      exit_token = CallFunction(exit_token, tmp->getUnaryExpression());
    }
  }

  return exit_token;
}

int MemoryAllocator(int mem_size, const Node* ast){  //planing to expand this for later us


  if(ast->getType() == "FunctionDefinition"){
    const FunctionDefinition* func = dynamic_cast<const FunctionDefinition*>(ast);
    mem_size = 16;
    mem_size = MemoryAllocator(mem_size, func->getContentsOfFunction());
  }

  if(ast->getType() == "CompoundStatement"){
    const CompoundStatement* tmp = dynamic_cast<const CompoundStatement*>(ast);
    if(tmp->hasNext()){
      mem_size = MemoryAllocator(mem_size, tmp->getDeclaration());
    }
    if(tmp->hasLists()){
      mem_size = MemoryAllocator(mem_size, tmp->getStatementList());
    }
  }

  if(ast->getType() == "Variable"){
    const Variable* tmp = dynamic_cast<const Variable*>(ast);
    if(tmp->getVariable_Information() == "array"){
      const IntConstant* tmp_size = dynamic_cast<const IntConstant*>(tmp->getArray_Information());
      mem_size += 4*(tmp_size->getIntConstantValue());
    }
  }

  if(ast->getType() == "StatementListNode"){
    const StatementListNode* tmp = dynamic_cast<const StatementListNode*>(ast);
    if(tmp->getStatement() != nullptr){
      mem_size = MemoryAllocator(mem_size, tmp->getStatement());
    }
    mem_size = MemoryAllocator(mem_size, tmp->getNextStatement());
  }

  if(ast->getType() == "Declaration"){
    const Declaration* tmp = dynamic_cast<const Declaration*>(ast);
    mem_size = MemoryAllocator(mem_size, tmp->getDeclaratorList());
  }

  if(ast->getType() == "DeclarationList"){
    mem_size += 4;
    const DeclarationList* tmp = dynamic_cast<const DeclarationList*>(ast);
    if(tmp->hasPrevious()){
      mem_size = MemoryAllocator(mem_size, tmp->getPrevious());
    }
    mem_size = MemoryAllocator(mem_size, tmp->getPresent());
  }

  if(ast->getType() == "InitDeclaratorList"){
    const InitDeclaratorList* tmp = dynamic_cast<const InitDeclaratorList*>(ast);
    if(tmp->hasPrevious()){
      mem_size += 4;
      mem_size = MemoryAllocator(mem_size, tmp->getPrevious());
    }
    mem_size = MemoryAllocator(mem_size, tmp->getPresent());
  }

  if(ast->getType() == "InitDeclarator"){
    const InitDeclarator* tmp = dynamic_cast<const InitDeclarator*>(ast);
    if(tmp->getInitialiser() != nullptr){
      mem_size = MemoryAllocator(mem_size, tmp->getInitialiser());
    }
    mem_size = MemoryAllocator(mem_size, tmp->getDeclarator());
  }

  if(ast->getType() == "ReturnStatement"){
    const ReturnStatement* tmp = dynamic_cast<const ReturnStatement*>(ast);
    if(tmp->HasExpression()){
      mem_size = MemoryAllocator(mem_size, tmp->getExpression());
    }
  }

  if(ast->getType() == "AdditiveExpression"){
    const AdditiveExpression* tmp = dynamic_cast<const AdditiveExpression*>(ast);
    if(getTypes(tmp->getRightSideOfExpression()) == "PostfixExpression"){
      mem_size = MemoryAllocator(mem_size, tmp->getRightSideOfExpression());
    }
    if(getTypes(tmp->getLeftSideOfExpression()) == "PostfixExpression"){
      mem_size = MemoryAllocator(mem_size, tmp->getLeftSideOfExpression());
    }
  }

  if(ast->getType() == "Expression"){
    const Expression* tmp = dynamic_cast<const Expression*>(ast);
    mem_size = MemoryAllocator(mem_size, tmp->getExpression());
  }

  if(ast->getType() == "AssignmentExpression"){
    const AssignmentExpression* tmp = dynamic_cast<const AssignmentExpression*>(ast);
    mem_size +=4;
  }

  if(ast->getType() == "IfStatement"){
    const IfStatement* tmp = dynamic_cast<const IfStatement*>(ast);
    mem_size = MemoryAllocator(mem_size, tmp->getCondition());
    mem_size = MemoryAllocator(mem_size, tmp->getIf());
    if(tmp->getELSE() != nullptr){
      mem_size = MemoryAllocator(mem_size, tmp->getELSE());
    }
  }

  if(ast->getType() == "WhileStatement"){
    const WhileStatement* tmp = dynamic_cast<const WhileStatement*>(ast);
    mem_size = MemoryAllocator(mem_size, tmp->getWhileParameter());
    mem_size = MemoryAllocator(mem_size, tmp->getWhileStatement());
  }

  if(ast->getType() == "ForStatement"){
    const ForStatement* tmp = dynamic_cast<const ForStatement*>(ast);
    mem_size = MemoryAllocator(mem_size, tmp->getExpressionStatement1());
    mem_size = MemoryAllocator(mem_size, tmp->getExpressionStatement2());
    mem_size = MemoryAllocator(mem_size, tmp->getForStatement());
    mem_size = MemoryAllocator(mem_size, tmp->getExpression());
  }

  if(ast->getType() == "PostfixExpression"){
    const PostfixExpression* tmp = dynamic_cast<const PostfixExpression*>(ast);
    mem_size += 16;
    if(tmp->getOthers() != nullptr){
      if(getTypes(tmp->getOthers()) == "Expression"){
        mem_size = MemoryAllocator(mem_size, tmp->getOthers());
      }
    }
  }

  return mem_size;  //very basic to begin with for testing
}

void CompileCallingtoFunction(std::ofstream& output, const Node* ast, int arguments){


  const Expression* tmp = dynamic_cast<const Expression*>(ast);
  if(tmp->getNext() != nullptr){
    CompileCallingtoFunction(output, tmp->getNext(), arguments);
    arguments++;
  }

  if(getTypes(tmp->getExpression()) == "AdditiveExpression"){
    arguments++;
    CompileAdditionExpressionNoMem(output, tmp->getExpression());
  }

  if(getTypes(tmp->getExpression()) == "identifierC"){
    arguments++;
    const identifierC* name_node = dynamic_cast<const identifierC*>(tmp->getExpression());
    int name_location = memory.FindVariable(*(name_node->getName()));
    output << "lw $" << (arguments+3) << "," << name_location << "($fp)\n";
  }

  if(getTypes(tmp->getExpression()) == "UnaryExpression"){
    arguments++;
    const UnaryExpression* unary_node = dynamic_cast<const UnaryExpression*>(tmp->getExpression());
    if(getTypes(unary_node->getUnaryExpression()) == "identifierC"){
      const identifierC* name_node = dynamic_cast<const identifierC*>(unary_node->getUnaryExpression());
      std::string name = *name_node->getName();
      int name_location = memory.FindVariable(name);
      output << "lw $2," << name_location << std::endl;
      output << "nop\n";
    }
    std::string mul_factor = *unary_node->getUnaryOpString();
    if(mul_factor == "-"){
      output << "subu $2,$0,$2\n";
    }
    output << "move $" << (arguments+3) << ",$2\n";
  }
}

void CompileLogicalAndExpressionNoMem(std::ofstream& output, const Node* ast){
  const LogicalAndExpression* landexp = dynamic_cast<const LogicalAndExpression*>(ast);
  std::string test = getTypes(landexp->getLeftSideOfExpression());
  long long int lhs_value, rhs_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(landexp->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $2," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(landexp->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $2," << lhs_value << std::endl;
  }

  output << "nop\n";
  std::string logical_and_1 = makeName("and");
  output << "beq $2,$0," << logical_and_1 << std::endl;
  output << "nop\n\n";


  test = getTypes(landexp->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(landexp->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $2," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(landexp->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }


  output << "nop\nbeq $2,$0," << logical_and_1 << std::endl;
  output << "nop\n" << std::endl;


  std::string logical_and_2 = makeName("and");
  output << "li $2,1\n";
  output << "b " << logical_and_2 << std::endl;
  output << "nop\n" << std::endl;


  output << logical_and_1 << ":\n";
  output << "move $2,$0\n" << std::endl;

  output << logical_and_2 << ":\n";
}

void CompileMultiplicativeExpressionNoMem(std::ofstream& output, const Node* ast){
  const MultiplicativeExpression* addexpr = dynamic_cast<const MultiplicativeExpression*>(ast);
  std::string tmp = getTypes(addexpr->getLeftSideOfExpression());
  if(tmp == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  tmp = getTypes(addexpr->getRightSideOfExpression());

  if(tmp == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  tmp = getTypes(addexpr->getLeftSideOfExpression());
  if(tmp == "identifierC"){
    const identifierC* var_name_lhs = dynamic_cast<const identifierC*>(addexpr->getLeftSideOfExpression());
    int tmp_mem_location_lhs = memory.FindVariable(*(var_name_lhs->getName()));
    output << "lw $3," << tmp_mem_location_lhs << "($fp)" << std::endl;
  }
  if(tmp == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(addexpr->getLeftSideOfExpression());
    output << "li $3," << lhs_node->getIntConstantValue() << std::endl;
  }

  tmp = getTypes(addexpr->getRightSideOfExpression());
  if(tmp == "identifierC"){
    const identifierC* var_name_rhs = dynamic_cast<const identifierC*>(addexpr->getRightSideOfExpression());
    int tmp_mem_location_rhs = memory.FindVariable(*(var_name_rhs->getName()));
    output << "lw $2," << tmp_mem_location_rhs << "($fp)" << std::endl;
  }
  if(tmp == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(addexpr->getRightSideOfExpression());
    output << "li $2," << rhs_node->getIntConstantValue() << std::endl;
  }

  output << "nop\n";

  std::string condition(addexpr->getConditionForMultiplication());


  if(condition == "*"){
    output << "mult $3, $2" << std::endl;
    output << "mflo $2" << std::endl;
  }

  if(condition == "/"){
    output << "div $3,$2\n";
    output << "mflo $2\n";
  }

  if(condition == "%"){
    output << "div $3,$2\n";
    output << "mfhi $2\n";
  }
}

void CompileReturnStatement(std::ofstream& output, const Node* ast){


  const Expression* expr = dynamic_cast<const Expression*>(ast);
  std::string tmp = getTypes(expr->getExpression());

  if(tmp == "UnaryExpression"){
    const UnaryExpression* unary_statement = dynamic_cast<const UnaryExpression*>(expr->getExpression());
    if(unary_statement->hasString()){
      tmp = getTypes(unary_statement->getUnaryExpression());
      if(tmp == "PostfixExpression"){
        const PostfixExpression* node = dynamic_cast<const PostfixExpression*>(unary_statement->getUnaryExpression());
        if(node->getTypes() == "array"){
          int mem_location = CompileArray(output, node);
          output << "lw $2," << mem_location << "($fp)\n";
        }
        else if(node->getTypes() == "function"){
          const identifierC* function_name_node = dynamic_cast<const identifierC*>(node->getPostfixExpression());
          if(getTypes(node->getOthers()) == "Expression"){
            int arguments = 0;
            CompileCallingtoFunction(output, node->getOthers(), arguments);
          }


          const std::string* function_name = function_name_node->getName();
          output << "jal " << *function_name << std::endl;
          output << "nop\n";
        }
      }
      std::string mul_factor = *unary_statement->getUnaryOpString();
      if(mul_factor == "-"){
        output << "subu $2,$0,$2\n";
      }
    }
  }

  else if(tmp == "AdditiveExpression"){ //if return a+b or a-b
    const AdditiveExpression* addexpr = dynamic_cast<const AdditiveExpression*>(expr->getExpression());
    tmp = getTypes(addexpr->getLeftSideOfExpression());

    if(tmp == "PostfixExpression"){
      const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
      if(lhs_node->getTypes() == "array"){
        int lhs_mem_location = CompileArray(output, lhs_node);
        output << "lw $2," << lhs_mem_location << "($fp)\n";
      }
      else if(lhs_node->getTypes() == "function"){
        const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
        if(getTypes(lhs_node->getOthers()) == "Expression"){
          const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
          if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* lhs_function_name = lhs_function_name_node->getName();
        output << "jal " << *lhs_function_name << std::endl;
        output << "nop\n";
      }
    }

    tmp = getTypes(addexpr->getRightSideOfExpression());

    if(tmp == "PostfixExpression"){
      const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
      if(rhs_node->getTypes() == "array"){
        int rhs_mem_location = CompileArray(output, rhs_node);
        output << "lw $2," << rhs_mem_location << "($fp)\n";
      }
      else if(rhs_node->getTypes() == "function"){
        const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
        if(getTypes(rhs_node->getOthers()) == "Expression"){
          const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
          if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* rhs_function_name = rhs_function_name_node->getName();
        output << "jal " << *rhs_function_name << std::endl;
        output << "nop\n";
      }
    }

    tmp = getTypes(addexpr->getLeftSideOfExpression());

    if(tmp == "identifierC"){
      const identifierC* var_name_lhs = dynamic_cast<const identifierC*>(addexpr->getLeftSideOfExpression());
      if(enums.CheckEnum(*(var_name_lhs->getName()))){
        long long int lhs_value = enums.GetEnum(*(var_name_lhs->getName()));
        output << "li $3," << lhs_value << std::endl;
      }
      else{
        int tmp_mem_location_lhs = memory.FindVariable(*(var_name_lhs->getName()));
        output << "lw $3," << tmp_mem_location_lhs << "($fp)" << std::endl;
      }
    }
    if(tmp == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(addexpr->getLeftSideOfExpression());
      output << "li $3," << lhs_node->getIntConstantValue() << std::endl;
    }

    else if(tmp == "AdditiveExpression"){
      CompileAdditionExpressionNoMem(output, addexpr->getLeftSideOfExpression());
      output << "move $3,$2\n";
    }

    else if(tmp == "MultiplicativeExpression"){
      CompileMultiplicativeExpressionNoMem(output, addexpr->getLeftSideOfExpression());
      output << "move $3,$2\n";
    }

    tmp = getTypes(addexpr->getRightSideOfExpression());

    if(tmp == "identifierC"){
      const identifierC* var_name_rhs = dynamic_cast<const identifierC*>(addexpr->getRightSideOfExpression());
      if(enums.CheckEnum(*(var_name_rhs->getName()))){
        long long int rhs_value = enums.GetEnum(*(var_name_rhs->getName()));
        output << "li $2," << rhs_value << std::endl;
      }
      else{
        int tmp_mem_location_rhs = memory.FindVariable(*(var_name_rhs->getName()));
        output << "lw $2," << tmp_mem_location_rhs << "($fp)" << std::endl;
      }
    }
    if(tmp == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(addexpr->getRightSideOfExpression());
      output << "li $2," << rhs_node->getIntConstantValue() << std::endl;
    }

    else if(tmp == "AdditiveExpression"){
      CompileAdditionExpressionNoMem(output, addexpr->getRightSideOfExpression());
    }

    else if(tmp == "MultiplicativeExpression"){
      CompileMultiplicativeExpressionNoMem(output, addexpr->getRightSideOfExpression());
    }

    output << "nop\n";


    if(addexpr->getConditionForAddition() == "+"){
      output << "addu $2,$3,$2" << std::endl;
    }

    else{
      output << "subu $2,$3,$2" << std::endl;
    }
  }

  else if(tmp == "LogicalAndExpression"){
    const LogicalAndExpression* landexp = dynamic_cast<const LogicalAndExpression*>(expr->getExpression());
    std::string test = getTypes(landexp->getLeftSideOfExpression());
    if(test == "PostfixExpression"){
      const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(landexp->getRightSideOfExpression());
      if(lhs_node->getTypes() == "array"){
        int lhs_mem_location = CompileArray(output, lhs_node);
        output << "lw $2," << lhs_mem_location << "($fp)\n";
      }
      else if(lhs_node->getTypes() == "function"){
        const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
        if(getTypes(lhs_node->getOthers()) == "Expression"){
          const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
          if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileLogicalAndExpressionNoMem(output, lhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* lhs_function_name = lhs_function_name_node->getName();
        output << "jal " << *lhs_function_name << std::endl;
        output << "nop\n";
      }
    }

    test = getTypes(landexp->getRightSideOfExpression());

    if(test == "PostfixExpression"){
      const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(landexp->getRightSideOfExpression());
      if(rhs_node->getTypes() == "array"){
        int rhs_mem_location = CompileArray(output, rhs_node);
        output << "lw $2," << rhs_mem_location << "($fp)\n";
      }
      else if(rhs_node->getTypes() == "function"){
        const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
        if(getTypes(rhs_node->getOthers()) == "Expression"){
          const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
          if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileLogicalAndExpressionNoMem(output, rhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* rhs_function_name = rhs_function_name_node->getName();
        output << "jal " << *rhs_function_name << std::endl;
        output << "nop\n";
      }
    }



    long long int lhs_value, rhs_value;
    if(test == "identifierC"){
      const identifierC* lhs_node = dynamic_cast<const identifierC*>(landexp->getLeftSideOfExpression());
      const std::string* lhs = lhs_node->getName();
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(landexp->getLeftSideOfExpression());
      lhs_value = lhs_node->getIntConstantValue();
      output << "li $2," << lhs_value << std::endl;
    }

    output << "nop\n";
    std::string logical_and_1 = makeName("and");
    output << "beq $2,$0," << logical_and_1 << std::endl;
    output << "nop\n\n";


    test = getTypes(landexp->getRightSideOfExpression());

    if(test == "identifierC"){
      const identifierC* rhs_node = dynamic_cast<const identifierC*>(landexp->getRightSideOfExpression());
      const std::string* rhs = rhs_node->getName();
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(landexp->getRightSideOfExpression());
      rhs_value = rhs_node->getIntConstantValue();
      output << "li $2," << rhs_value << std::endl;
    }


    output << "nop\nbeq $2,$0," << logical_and_1 << std::endl;
    output << "nop\n" << std::endl;


    std::string logical_and_2 = makeName("and");
    output << "li $2,1\n";
    output << "b " << logical_and_2 << std::endl;
    output << "nop\n" << std::endl;


    output << logical_and_1 << ":\n";
    output << "move $2,$0\n" << std::endl;

    output << logical_and_2 << ":\n";

  }

  else if(tmp == "MultiplicativeExpression"){ //if return a+b or a-b
    const MultiplicativeExpression* addexpr = dynamic_cast<const MultiplicativeExpression*>(expr->getExpression());
    tmp = getTypes(addexpr->getLeftSideOfExpression());
    if(tmp == "PostfixExpression"){
      const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
      if(lhs_node->getTypes() == "array"){
        int lhs_mem_location = CompileArray(output, lhs_node);
        output << "lw $2," << lhs_mem_location << "($fp)\n";
      }
      else if(lhs_node->getTypes() == "function"){
        const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
        if(getTypes(lhs_node->getOthers()) == "Expression"){
          const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
          if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileMultiplicativeExpressionNoMem(output, lhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* lhs_function_name = lhs_function_name_node->getName();
        output << "jal " << *lhs_function_name << std::endl;
        output << "nop\n";
      }
    }

    tmp = getTypes(addexpr->getRightSideOfExpression());

    if(tmp == "PostfixExpression"){
      const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(addexpr->getRightSideOfExpression());
      if(rhs_node->getTypes() == "array"){
        int rhs_mem_location = CompileArray(output, rhs_node);
        output << "lw $2," << rhs_mem_location << "($fp)\n";
      }
      else if(rhs_node->getTypes() == "function"){
        const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
        if(getTypes(rhs_node->getOthers()) == "Expression"){
          const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
          if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
            CompileMultiplicativeExpressionNoMem(output, rhs_function_expr->getExpression());
            output << "move $4,$2\n";
          }
        }
        const std::string* rhs_function_name = rhs_function_name_node->getName();
        output << "jal " << *rhs_function_name << std::endl;
        output << "nop\n";
      }
    }

    tmp = getTypes(addexpr->getLeftSideOfExpression());
    if(tmp == "identifierC"){
      const identifierC* var_name_lhs = dynamic_cast<const identifierC*>(addexpr->getLeftSideOfExpression());
      if(enums.CheckEnum(*(var_name_lhs->getName()))){
        long long int lhs_value = enums.GetEnum(*(var_name_lhs->getName()));
        output << "li $3," << lhs_value << std::endl;
      }
      else{
        int tmp_mem_location_lhs = memory.FindVariable(*(var_name_lhs->getName()));
        output << "lw $3," << tmp_mem_location_lhs << "($fp)" << std::endl;
      }
    }
    if(tmp == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(addexpr->getLeftSideOfExpression());
      output << "li $3," << lhs_node->getIntConstantValue() << std::endl;
    }

    else if(tmp == "AdditiveExpression"){
      CompileAdditionExpressionNoMem(output, addexpr->getLeftSideOfExpression());
      output << "move $3,$2\n";
    }

    else if(tmp == "MultiplicativeExpression"){
      CompileMultiplicativeExpressionNoMem(output, addexpr->getLeftSideOfExpression());
      output << "move $3,$2\n";
    }

    tmp = getTypes(addexpr->getRightSideOfExpression());

    if(tmp == "identifierC"){
      const identifierC* var_name_rhs = dynamic_cast<const identifierC*>(addexpr->getRightSideOfExpression());
      if(enums.CheckEnum(*(var_name_rhs->getName()))){
        long long int rhs_value = enums.GetEnum(*(var_name_rhs->getName()));
        output << "li $2," << rhs_value << std::endl;
      }
      else{
        int tmp_mem_location_rhs = memory.FindVariable(*(var_name_rhs->getName()));
        output << "lw $2," << tmp_mem_location_rhs << "($fp)" << std::endl;
      }
    }
    if(tmp == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(addexpr->getRightSideOfExpression());
      output << "li $2," << rhs_node->getIntConstantValue() << std::endl;
    }

    else if(tmp == "AdditiveExpression"){
      CompileAdditionExpressionNoMem(output, addexpr->getRightSideOfExpression());
    }

    else if(tmp == "MultiplicativeExpression"){
      CompileMultiplicativeExpressionNoMem(output, addexpr->getRightSideOfExpression());
    }

    output << "nop\n";

    std::string condition(addexpr->getConditionForMultiplication());


    if(condition == "*"){
      output << "mult $3, $2" << std::endl;
      output << "mflo $2" << std::endl;
    }

    if(condition == "/"){
      output << "div $3,$2\n";
      output << "mflo $2\n";
    }

    if(condition == "%"){
      output << "div $3,$2\n";
      output << "mfhi $2\n";
    }
  }

  else if(tmp == "IntConstant"){ //if return(int)
    const IntConstant* int_constant = dynamic_cast<const IntConstant*>(expr->getExpression());
    output << "li $2," << int_constant->getIntConstantValue() << "\n";
  }

  else if(tmp == "PostfixExpression"){ //if return(function())
    const PostfixExpression* postfix_exp = dynamic_cast<const PostfixExpression*>(expr->getExpression());
    const identifierC* name_node = dynamic_cast<const identifierC*>(postfix_exp->getPostfixExpression());
    const std::string* name_expr = name_node->getName();
    int name_expr_location;
    if(postfix_exp->getTypes() == "array"){
      const Expression* tmp_exp = dynamic_cast<const Expression*>(postfix_exp->getOthers());
      const IntConstant* tmp_int = dynamic_cast<const IntConstant*>(tmp_exp->getExpression());
      std::string array_string = *name_node->getName();
      std::string ss = std::to_string(tmp_int->getIntConstantValue());
      std::string var_name = array_string+ss;
      name_expr_location = memory.FindVariable(var_name);
      output << "lw $2," << name_expr_location << "($fp)\n";
    }
    else{
      name_expr_location = memory.FindVariable(*name_expr);
    }
    if(postfix_exp->getTypes() == "function"){
      if(postfix_exp->getOthers() != nullptr){
        int expr_terms = 1 ;
        output << ".cprestore 16\n";
        expr_terms = CountTerms(output, expr_terms, postfix_exp->getOthers());
      }
      output << "jal " << *name_expr << "\nnop\n";
    }
    else if(postfix_exp->getTypes() == "--"){
      output << "lw $2," << name_expr_location << "($fp)\n";
      output << "subiu $2,$2,1\n";
    }
    else if(postfix_exp->getTypes() == "++"){
      output << "lw $2," << name_expr_location << "($fp)\n";
      output << "addiu $2,$2,1\n";
    }
  }

  else if(tmp == "AndExpression"){
    const AndExpression* addexpr = dynamic_cast<const AndExpression*>(expr->getExpression());
    tmp = getTypes(addexpr->getLeftSideOfExpression());
    if(tmp == "identifierC"){
      const identifierC* var_name_lhs = dynamic_cast<const identifierC*>(addexpr->getLeftSideOfExpression());
      int tmp_mem_location_lhs = memory.FindVariable(*(var_name_lhs->getName()));
      output << "lw $3," << tmp_mem_location_lhs << "($fp)" << std::endl;
    }
    if(tmp == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(addexpr->getLeftSideOfExpression());
      output << "li $3," << lhs_node->getIntConstantValue() << std::endl;
    }

    tmp = getTypes(addexpr->getRightSideOfExpression());
    if(tmp == "identifierC"){
      const identifierC* var_name_rhs = dynamic_cast<const identifierC*>(addexpr->getRightSideOfExpression());
      int tmp_mem_location_rhs = memory.FindVariable(*(var_name_rhs->getName()));
      output << "lw $2," << tmp_mem_location_rhs << "($fp)" << std::endl;
    }
    if(tmp == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(addexpr->getRightSideOfExpression());
      output << "li $2," << rhs_node->getIntConstantValue() << std::endl;
    }

    output << "nop\n";

    output << "and $2,$3,$2\n";
  }

  else if(tmp == "EqualityExpression"){
    const EqualityExpression* equalexpr = dynamic_cast<const EqualityExpression*>(expr->getExpression());
    tmp = getTypes(equalexpr->getLeftSideOfExpression());
    if(tmp == "identifierC"){
      const identifierC* var_name_lhs = dynamic_cast<const identifierC*>(equalexpr->getLeftSideOfExpression());
      int tmp_mem_location_lhs = memory.FindVariable(*(var_name_lhs->getName()));
      output << "lw $3," << tmp_mem_location_lhs << "($fp)" << std::endl;
    }
    if(tmp == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(equalexpr->getLeftSideOfExpression());
      output << "li $3," << lhs_node->getIntConstantValue() << std::endl;
    }

    tmp = getTypes(equalexpr->getRightSideOfExpression());
    if(tmp == "identifierC"){
      const identifierC* var_name_rhs = dynamic_cast<const identifierC*>(equalexpr->getRightSideOfExpression());
      int tmp_mem_location_rhs = memory.FindVariable(*(var_name_rhs->getName()));
      output << "lw $2," << tmp_mem_location_rhs << "($fp)" << std::endl;
    }
    if(tmp == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(equalexpr->getRightSideOfExpression());
      output << "li $2," << rhs_node->getIntConstantValue() << std::endl;
    }

    output << "nop\n";

    std::string condition(equalexpr->getConditionForEquality());
    if(condition == "=="){
      output << "xor $2,$3,$2\nsltu $2,$2,1\nandi $2,$2,0x00ff\n";
    }
    else{
      output << "xor $2,$3,$2\nsltu $2,$0,$2\nandi $2,$2,0x00ff\n";
    }

  }

  else if(tmp == "RelationalExpression"){
    const RelationalExpression* tmp_relational = dynamic_cast<const RelationalExpression*>(expr->getExpression());
    std::string test = getTypes(tmp_relational->getLeftSideOfExpression());
    long long int lhs_value, rhs_value;
    std::string condition(tmp_relational->getConditionForRelation());
    if(test == "identifierC"){
      const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_relational->getLeftSideOfExpression());
      const std::string* lhs = lhs_node->getName();
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getLeftSideOfExpression());
      lhs_value = lhs_node->getIntConstantValue();
      if((condition == "<=") || (condition == ">=")){
        output << "li $3," << (lhs_value+1) << std::endl;
      }
      else{
        output << "li $3," << lhs_value << std::endl;
      }
    }

    test = getTypes(tmp_relational->getRightSideOfExpression());

    if(test == "identifierC"){
      const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_relational->getRightSideOfExpression());
      const std::string* rhs = rhs_node->getName();
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getRightSideOfExpression());
      rhs_value = rhs_node->getIntConstantValue();
      if((condition == "<") || (condition == ">")){
        output << "li $2," << (rhs_value+1) << std::endl;
      }
      else{
        output << "li $2," << rhs_value << std::endl;
      }
    }

    output << "nop\n";



    if(condition == "<"){
      output << "slt $2,$3,$2\nandi $2,$2,0x00ff\n";
    }

    else if(condition == ">"){
      output << "slt $2,$2,$3\nandi $2,$2,0x00ff\n";
    }

    else if(condition == "<="){
      output << "slt $2,$3,$2\nxori $2,$3,0x1\nandi $2,$2,0x00ff\n";
    }

    else if(condition == ">="){
      output << "slt $2,$2,$3\nxori $2,$3,0x1\nandi $2,$2,0x00ff\n";
    }
  }

  else if(tmp == "ExclusiveOrExpression"){
    const ExclusiveOrExpression* ex_or = dynamic_cast<const ExclusiveOrExpression*>(expr->getExpression());
    std::string test = getTypes(ex_or->getLeftSideOfExpression());
    long long int lhs_value, rhs_value;
    if(test == "identifierC"){
      const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
      const std::string* lhs = lhs_node->getName();
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
      lhs_value = lhs_node->getIntConstantValue();
      output << "li $3," << lhs_value << std::endl;
    }

    test = getTypes(ex_or->getRightSideOfExpression());

    if(test == "identifierC"){
      const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
      const std::string* rhs = rhs_node->getName();
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
      rhs_value = rhs_node->getIntConstantValue();
      output << "li $2," << rhs_value << std::endl;
    }

    output << "nop\nxor $2,$3,$2\n";
  }

  else if(tmp == "InclusiveOrExpression"){
    const InclusiveOrExpression* ex_or = dynamic_cast<const InclusiveOrExpression*>(expr->getExpression());
    std::string test = getTypes(ex_or->getLeftSideOfExpression());
    long long int lhs_value, rhs_value;
    if(test == "identifierC"){
      const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
      const std::string* lhs = lhs_node->getName();
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
      lhs_value = lhs_node->getIntConstantValue();
      output << "li $3," << lhs_value << std::endl;
    }

    test = getTypes(ex_or->getRightSideOfExpression());

    if(test == "identifierC"){
      const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
      const std::string* rhs = rhs_node->getName();
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
      rhs_value = rhs_node->getIntConstantValue();
      output << "li $2," << rhs_value << std::endl;
    }

    output << "nop\nor $2,$3,$2\n";
  }

  else if(tmp == "LogicalOrExpression"){
    const LogicalOrExpression* ex_or = dynamic_cast<const LogicalOrExpression*>(expr->getExpression());
    std::string test = getTypes(ex_or->getLeftSideOfExpression());
    long long int lhs_value, rhs_value;
    if(test == "identifierC"){
      const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
      const std::string* lhs = lhs_node->getName();
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
      lhs_value = lhs_node->getIntConstantValue();
      output << "li $2," << lhs_value << std::endl;
    }

    output << "nop\n";
    std::string logical_or_1 = makeName("or");
    output << "bne $2,$0," << logical_or_1 << std::endl;
    output << "nop\n\n";


    test = getTypes(ex_or->getRightSideOfExpression());

    if(test == "identifierC"){
      const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
      const std::string* rhs = rhs_node->getName();
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }

    else if(test == "IntConstant"){
      const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
      rhs_value = rhs_node->getIntConstantValue();
      output << "li $2," << rhs_value << std::endl;
    }

    std::string logical_or_2 = makeName("or");
    output << "nop\nbeq $2,$0," << logical_or_2 << std::endl;
    output << "nop\n" << std::endl;

    output << logical_or_1 << ":" << std::endl;
    output << "li $2,1\n";
    std::string logical_or_3 = makeName("or");
    output << "b " << logical_or_3 << std::endl;
    output << "nop\n" << std::endl;

    output << logical_or_2 << ":\n";
    output << "move $2,$0\n" << std::endl;

    output << logical_or_3 << ":\n";


  }

  else if(tmp == "identifierC"){
    const identifierC* name_node = dynamic_cast<const identifierC*>(expr->getExpression());
    if(enums.CheckEnum(*(name_node->getName()))){
      long long int lhs_value = enums.GetEnum(*(name_node->getName()));
      output << "li $2," << lhs_value << std::endl;
    }
    else{
      int tmp_mem_location_lhs = memory.FindVariable(*(name_node->getName()));
      output << "lw $2," << tmp_mem_location_lhs << "($fp)" << std::endl;
    }
  }

  output << "b " << function_return << std::endl;
  output << "nop" << std::endl;


}

int CompileArray(std::ofstream& output, const PostfixExpression* ast){
  const identifierC* array_node_name = dynamic_cast<const identifierC*>(ast->getPostfixExpression());
  const Expression* array_placement = dynamic_cast<const Expression*>(ast->getOthers());
  std::string var_name;
  if(getTypes(array_placement->getExpression()) == "AdditiveExpression"){
    const AdditiveExpression* add_expr = dynamic_cast<const AdditiveExpression*>(array_placement->getExpression());
    std::string inside_array = makeName("array");
    CompileAdditionExpression(output,add_expr, inside_array);
    int place = local_variables.getValue(inside_array);
    std::string ss = std::to_string(place);
    std::string array_string = *array_node_name->getName();
    var_name = array_string+ss;
  }
  else if(getTypes(array_placement->getExpression()) == "IntConstant"){
    const IntConstant* int_node = dynamic_cast<const IntConstant*>(array_placement->getExpression());
    std::string ss = std::to_string(int_node->getIntConstantValue());
    std::string array_string =*array_node_name->getName();
    var_name = array_string+ss;
  }
  else if(getTypes(array_placement->getExpression()) == "identifierC"){
    const identifierC* array_place_name = dynamic_cast<const identifierC*>(array_placement->getExpression());
    int tmp = local_variables.getValue(*array_place_name->getName());
    std::string ss = std::to_string(tmp);
    std::string array_string =*array_node_name->getName();
    var_name = array_string+ss;
  }
  return (memory.FindVariable(var_name));
}

void CompileAdditionExpressionNoMem(std::ofstream& output, const Node* ast){
  const AdditiveExpression* tmp_add = dynamic_cast<const AdditiveExpression*>(ast);
  std::string test = getTypes(tmp_add->getLeftSideOfExpression());
  if(test == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_add->getRightSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_add->getRightSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_add->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $3," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_add->getLeftSideOfExpression());
  long long int lhs_value, rhs_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_add->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $3," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_add->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $3," << lhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_add->getLeftSideOfExpression());
    output << "move $3,$2\n";
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_add->getLeftSideOfExpression());
    output << "move $3,$2\n";
  }

  test = getTypes(tmp_add->getRightSideOfExpression());


  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_add->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $2," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_add->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_add->getRightSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_add->getRightSideOfExpression());
  }



  output << "nop\n";

  std::string condition(tmp_add->getConditionForAddition());


  if(condition == "+"){
    output << "addu $2,$2,$3\n";
  }

  else if(condition == "-"){
    output << "subu $2,$3,$2\n";
  }
}

void CompileAdditionExpression(std::ofstream& output, const Node* ast, const std::string var_name){
  const AdditiveExpression* tmp_add = dynamic_cast<const AdditiveExpression*>(ast);
  long long int lhs_value, rhs_value, addition_value;
  std::string test = getTypes(tmp_add->getLeftSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_add->getRightSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_add->getRightSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_add->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }
  test = getTypes(tmp_add->getLeftSideOfExpression());

  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_add->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    if(enums.CheckEnum(*lhs)){
      lhs_value = enums.GetEnum(*lhs);
      output << "li $3," << lhs_value << std::endl;
    }
    else{
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_add->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $3," << lhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_add->getLeftSideOfExpression());
    output << "move $3,$2\n";
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_add->getLeftSideOfExpression());
    output << "move $3,$2\n";
  }

  test = getTypes(tmp_add->getRightSideOfExpression());


  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_add->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    if(enums.CheckEnum(*rhs)){
      rhs_value = enums.GetEnum(*rhs);
      output << "li $2," << rhs_value << std::endl;
    }
    else{
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_add->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_add->getRightSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_add->getRightSideOfExpression());
  }

  output << "nop\n";

  std::string condition(tmp_add->getConditionForAddition());


  if(condition == "+"){
    output << "addu $2,$2,$3\n";
    long long int addition_value = lhs_value+rhs_value;
  }

  else if(condition == "-"){
    output << "subu $2,$3,$2\n";
    long long int addition_value = lhs_value-rhs_value;
  }

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, addition_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)" << "\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileAndExpression(std::ofstream& output, const Node* ast, const std::string var_name){
  const AndExpression* tmp_add = dynamic_cast<const AndExpression*>(ast);
  std::string test = getTypes(tmp_add->getLeftSideOfExpression());
  long long int lhs_value, rhs_value, addition_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_add->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $3," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_add->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $3," << lhs_value << std::endl;
  }

  test = getTypes(tmp_add->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_add->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $2," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_add->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  output << "nop\n";

  output << "addu $2, $3, $2\n";

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, addition_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileMultiplicativeExpression(std::ofstream& output, const Node* ast, const std::string var_name){
  const MultiplicativeExpression* tmp_mul = dynamic_cast<const MultiplicativeExpression*>(ast);
  long long int lhs_value, rhs_value, addition_value;
  std::string test = getTypes(tmp_mul->getLeftSideOfExpression());
  if(test == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_mul->getRightSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_mul->getRightSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_mul->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileMultiplicativeExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_mul->getLeftSideOfExpression());


  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_mul->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    if(enums.CheckEnum(*lhs)){
      lhs_value = enums.GetEnum(*lhs);
      output << "li $3," << lhs_value << std::endl;
    }
    else{
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_mul->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $3," << lhs_value << std::endl;
  }

  test = getTypes(tmp_mul->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_mul->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    if(enums.CheckEnum(*rhs)){
      rhs_value = enums.GetEnum(*rhs);
      output << "li $2," << rhs_value << std::endl;
    }
    else{
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_mul->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  output << "nop\n";

  std::string condition(tmp_mul->getConditionForMultiplication());

  if(condition == "*"){
    output << "mult $3,$2\n";
    output << "mflo $2\n";
    long long int addition_value = lhs_value*rhs_value;
  }

  if(condition == "/"){
    output << "div $3,$2\n";
    output << "mflo $2\n";
    long long int division_value = lhs_value/rhs_value;
  }

  if(condition == "%"){
    output << "div $3,$2\n";
    output << "mfhi $2\n";
    long long int division_value = lhs_value/rhs_value;
  }


  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, addition_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileIntConstant(std::ofstream& output, const Node* ast, std::string var_name){
  const IntConstant* tmp_name = dynamic_cast<const IntConstant*>(ast);
  local_variables.addValue(var_name, tmp_name->getIntConstantValue());
  std::vector<memlocation> memory_ = memory.getMemory();
  int memory_size = memory_.size();
  std::vector<variablesstruct> variables = local_variables.getLocalVariables();
  int var_size = variables.size();

  output << "li $2," << tmp_name->getIntConstantValue() << "\n";

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileEqualityExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const EqualityExpression* tmp_equal = dynamic_cast<const EqualityExpression*>(ast);
  long long int lhs_value, rhs_value, addition_value;
  std::string test = getTypes(tmp_equal->getLeftSideOfExpression());
  if(test == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getRightSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_equal->getRightSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }
  test = getTypes(tmp_equal->getLeftSideOfExpression());

  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_equal->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    if(enums.CheckEnum(*lhs)){
      lhs_value = enums.GetEnum(*lhs);
      output << "li $3," << lhs_value << std::endl;
    }
    else{
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $3," << lhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
  }

  test = getTypes(tmp_equal->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_equal->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    if(enums.CheckEnum(*rhs)){
      lhs_value = enums.GetEnum(*rhs);
      output << "li $2," << rhs_value << std::endl;
    }
    else{
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
  }


  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
  }

  output << "nop\n";

  std::string condition(tmp_equal->getConditionForEquality());

  if(condition == "=="){
    output << "xor $2,$3,$3\nsltu $2,$2,1\nandi $2,$2,0x00ff";
    long long int addition_value = lhs_value==rhs_value;
  }

  else if(condition == "!="){
    output << "xor $2,$3,$3\nsltu $2,$0,$2\nandi $2,$2,0x00ff";
    long long int addition_value = lhs_value!=rhs_value;
  }


  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, addition_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileRelationalExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const RelationalExpression* tmp_relational = dynamic_cast<const RelationalExpression*>(ast);
  long long int lhs_value, rhs_value, addition_value;
  std::string test = getTypes(tmp_relational->getLeftSideOfExpression());
  if(test == "PostfixExpression"){
    const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getLeftSideOfExpression());
    if(lhs_node->getTypes() == "array"){
      int lhs_mem_location = CompileArray(output, lhs_node);
      output << "lw $2," << lhs_mem_location << "($fp)\n";
    }
    else if(lhs_node->getTypes() == "function"){
      const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
      if(getTypes(lhs_node->getOthers()) == "Expression"){
        const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
        if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* lhs_function_name = lhs_function_name_node->getName();
      output << "jal " << *lhs_function_name << std::endl;
      output << "nop\n";
    }
  }

  test = getTypes(tmp_relational->getRightSideOfExpression());

  if(test == "PostfixExpression"){
    const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getRightSideOfExpression());
    if(rhs_node->getTypes() == "array"){
      int rhs_mem_location = CompileArray(output, rhs_node);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
    else if(rhs_node->getTypes() == "function"){
      const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
      if(getTypes(rhs_node->getOthers()) == "Expression"){
        const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
        if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
          CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
          output << "move $4,$2\n";
        }
      }
      const std::string* rhs_function_name = rhs_function_name_node->getName();
      output << "jal " << *rhs_function_name << std::endl;
      output << "nop\n";
    }
  }
  test = getTypes(tmp_relational->getLeftSideOfExpression());
  std::string condition(tmp_relational->getConditionForRelation());
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_relational->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    if(enums.CheckEnum(*lhs)){
      lhs_value = enums.GetEnum(*lhs);
      output << "li $3," << lhs_value << std::endl;
    }
    else{
      lhs_value = local_variables.getValue(*lhs);
      int lhs_mem_location = memory.FindVariable(*lhs);
      output << "lw $3," << lhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    if((condition == "<") && (condition == ">")){
      output << "li $3," << (lhs_value+1) << std::endl;
    }
    else{
      output << "li $3," << lhs_value << std::endl;
    }
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
  }

  test = getTypes(tmp_relational->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_relational->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    if(enums.CheckEnum(*rhs)){
      rhs_value = enums.GetEnum(*rhs);
      output << "li $2," << rhs_value << std::endl;
    }
    else{
      rhs_value = local_variables.getValue(*rhs);
      int rhs_mem_location = memory.FindVariable(*rhs);
      output << "lw $2," << rhs_mem_location << "($fp)\n";
    }
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    if((condition == "<") && (condition == ">")){
      output << "li $2," << (lhs_value+1) << std::endl;
    }
    else{
      output << "li $2," << lhs_value << std::endl;
    }
  }

  else if(test == "AdditiveExpression"){
    CompileAdditionExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
  }

  else if(test == "MultiplicativeExpression"){
    CompileMultiplicativeExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
  }

  output << "nop\n";



  if(condition == "<"){
    output << "slt $2,$3,$2\nandi $2,$2,0x00ff\n";
    long long int addition_value = lhs_value<rhs_value;
  }

  else if(condition == ">"){
    output << "slt $2,$2,$3\nandi $2,$2,0x00ff\n";
    long long int addition_value = lhs_value>rhs_value;
  }

  else if(condition == "<="){
    output << "slt $2,$2,$3\nxori $2,$2,0x1\nandi $2,$2,0x00ff\n";
    long long int addition_value = lhs_value<=rhs_value;
  }

  else if(condition == ">="){
    output << "slt $2,$3,$2\nxori $2,$2,0x1\nandi $2,$2,0x00ff\n";
    long long int addition_value = lhs_value>=rhs_value;
  }

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, addition_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)" << "\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileExclusiveOrExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const ExclusiveOrExpression* ex_or = dynamic_cast<const ExclusiveOrExpression*>(ast);
  std::string test = getTypes(ex_or->getLeftSideOfExpression());
  long long int lhs_value, rhs_value, xor_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $2," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $2," << lhs_value << std::endl;
  }

  test = getTypes(ex_or->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $3," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $3," << rhs_value << std::endl;
  }

  output << "nop\nxor $2,$3,$2\n";

  xor_value = lhs_value^rhs_value;

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, xor_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }

}

void CompileInclusiveOrExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const InclusiveOrExpression* ex_or = dynamic_cast<const InclusiveOrExpression*>(ast);
  std::string test = getTypes(ex_or->getLeftSideOfExpression());
  long long int lhs_value, rhs_value, xor_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $2," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $2," << lhs_value << std::endl;
  }

  test = getTypes(ex_or->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $3," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $3," << rhs_value << std::endl;
  }

  output << "nop\nor $2,$3,$2\n";

  xor_value = lhs_value|rhs_value;

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, xor_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileidentifierC(std::ofstream& output, const Node* ast, std::string var_name){
  const identifierC* var_node = dynamic_cast<const identifierC*>(ast);
  int equal_var_location = memory.FindVariable(*(var_node->getName()));
  output << "lw $2," << equal_var_location << "($fp)\n";
  output << "nop\n";
  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addVariable(var_name);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileLogicalOrExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const LogicalOrExpression* ex_or = dynamic_cast<const LogicalOrExpression*>(ast);
  std::string test = getTypes(ex_or->getLeftSideOfExpression());
  long long int lhs_value, rhs_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(ex_or->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $2," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(ex_or->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $2," << lhs_value << std::endl;
  }

  output << "nop\n";
  std::string logical_or_1 = makeName("or");
  output << "bne $2,$0," << logical_or_1 << std::endl;
  output << "nop\n\n";


  test = getTypes(ex_or->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(ex_or->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $2," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(ex_or->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }

  std::string logical_or_2 = makeName("or");
  output << "nop\nbeq $2,$0," << logical_or_2 << std::endl;
  output << "nop\n" << std::endl;

  output << logical_or_1 << ":" << std::endl;
  output << "li $2,1\n";
  std::string logical_or_3 = makeName("or");
  output << "b " << logical_or_3 << std::endl;
  output << "nop\n" << std::endl;

  output << logical_or_2 << ":\n";
  output << "move $2,$0\n" << std::endl;

  output << logical_or_3 << ":\n";

  long long int lor_value = lhs_value||rhs_value;

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, lor_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileLogicalAndExpression(std::ofstream& output, const Node* ast, std::string var_name){
  const LogicalAndExpression* landexp = dynamic_cast<const LogicalAndExpression*>(ast);
  std::string test = getTypes(landexp->getLeftSideOfExpression());
  long long int lhs_value, rhs_value;
  if(test == "identifierC"){
    const identifierC* lhs_node = dynamic_cast<const identifierC*>(landexp->getLeftSideOfExpression());
    const std::string* lhs = lhs_node->getName();
    lhs_value = local_variables.getValue(*lhs);
    int lhs_mem_location = memory.FindVariable(*lhs);
    output << "lw $2," << lhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(landexp->getLeftSideOfExpression());
    lhs_value = lhs_node->getIntConstantValue();
    output << "li $2," << lhs_value << std::endl;
  }

  output << "nop\n";
  std::string logical_and_1 = makeName("and");
  output << "beq $2,$0," << logical_and_1 << std::endl;
  output << "nop\n\n";


  test = getTypes(landexp->getRightSideOfExpression());

  if(test == "identifierC"){
    const identifierC* rhs_node = dynamic_cast<const identifierC*>(landexp->getRightSideOfExpression());
    const std::string* rhs = rhs_node->getName();
    rhs_value = local_variables.getValue(*rhs);
    int rhs_mem_location = memory.FindVariable(*rhs);
    output << "lw $2," << rhs_mem_location << "($fp)\n";
  }

  else if(test == "IntConstant"){
    const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(landexp->getRightSideOfExpression());
    rhs_value = rhs_node->getIntConstantValue();
    output << "li $2," << rhs_value << std::endl;
  }


  output << "nop\nbeq $2,$0," << logical_and_1 << std::endl;
  output << "nop\n" << std::endl;


  std::string logical_and_2 = makeName("and");
  output << "li $2,1\n";
  output << "b " << logical_and_2 << std::endl;
  output << "nop\n" << std::endl;


  output << logical_and_1 << ":\n";
  output << "move $2,$0\n" << std::endl;

  output << logical_and_2 << ":\n";

  long long int land_value = lhs_value&&rhs_value;

  if(memory.InMemory(var_name)){
    int tmp_name_location = memory.FindVariable(var_name);
    output << "sw $2," << tmp_name_location << "($fp)" << std::endl;
  }
  else{
    local_variables.addValue(var_name, land_value);
    std::vector<variablesstruct> variables = local_variables.getLocalVariables();
    int var_size = variables.size();
    output << "sw $2," << stack_size-(12+(4*(var_size))) << "($fp)\n";
    memory.AddValue(var_name, stack_size-(12+(4*(var_size))));
  }
}

void CompileIfCondition(std::ofstream& output, const Node* ast){
  const IfStatement* if_state = dynamic_cast<const IfStatement*>(ast);
  std::string type_condition = getTypes(if_state->getCondition());
  bool condition_met;
  std::string if_not = makeName("if_not");
  if(type_condition == "Expression"){
    const Expression* expr = dynamic_cast<const Expression*>(if_state->getCondition());
    if(expr->getNext() != nullptr){
      CompileIfCondition(output, expr->getNext());
    }
    std::string expr_type = getTypes(expr->getExpression());

    if(expr_type == "IntConstant"){
      const IntConstant* int_node = dynamic_cast<const IntConstant*>(expr->getExpression());
      long long int int_value = int_node->getIntConstantValue();
      if(int_value == 0){
        if(if_state->getELSE() != nullptr){
          CompileBody(output, if_state->getELSE());
        }
      }
      else{
        CompileBody(output, if_state->getIf());
      }
      return;
    }

    else if(expr_type == "identifierC"){
      const identifierC* name_node = dynamic_cast<const identifierC*>(expr->getExpression());
      if(enums.CheckEnum(*(name_node->getName()))){
        long long int lhs_value = enums.GetEnum(*(name_node->getName()));
        output << "li $2," << lhs_value << std::endl;
      }
      else{
        int equal_var_location = memory.FindVariable(*(name_node->getName()));
        output << "lw $2," << equal_var_location << "($fp)" << std::endl;
      }
      output << "nop\n";
      output << "beq $2,$0," << if_not << std::endl;
      output << "nop\n\n";
    }

    else if(expr_type == "RelationalExpression"){
      const RelationalExpression* tmp_relational = dynamic_cast<const RelationalExpression*>(expr->getExpression());
      std::string condition(tmp_relational->getConditionForRelation());
      std::string test = getTypes(tmp_relational->getLeftSideOfExpression());
      if(test == "PostfixExpression"){
        const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getLeftSideOfExpression());
        if(lhs_node->getTypes() == "array"){
          int lhs_mem_location = CompileArray(output, lhs_node);
          output << "lw $2," << lhs_mem_location << "($fp)\n";
        }
        else if(lhs_node->getTypes() == "function"){
          const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
          if(getTypes(lhs_node->getOthers()) == "Expression"){
            const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
            if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* lhs_function_name = lhs_function_name_node->getName();
          output << "jal " << *lhs_function_name << std::endl;
          output << "nop\n";
        }
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());

      if(test == "PostfixExpression"){
        const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getRightSideOfExpression());
        if(rhs_node->getTypes() == "array"){
          int rhs_mem_location = CompileArray(output, rhs_node);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
        else if(rhs_node->getTypes() == "function"){
          const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
          if(getTypes(rhs_node->getOthers()) == "Expression"){
            const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
            if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* rhs_function_name = rhs_function_name_node->getName();
          output << "jal " << *rhs_function_name << std::endl;
          output << "nop\n";
        }
      }
      test = getTypes(tmp_relational->getLeftSideOfExpression());
      long long int lhs_value, rhs_value;
      if(test == "identifierC"){
        const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_relational->getLeftSideOfExpression());
        const std::string* lhs = lhs_node->getName();
        if(enums.CheckEnum(*lhs)){
          lhs_value = enums.GetEnum(*lhs);
          output << "li $3," << lhs_value << std::endl;
        }
        else{
          lhs_value = local_variables.getValue(*lhs);
          int lhs_mem_location = memory.FindVariable(*lhs);
          output << "lw $3," << lhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getLeftSideOfExpression());
        lhs_value = lhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $3," << (lhs_value+1) << std::endl;
        }
        else{
          output << "li $3," << lhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());


      if(test == "identifierC"){
        const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_relational->getRightSideOfExpression());
        const std::string* rhs = rhs_node->getName();
        if(enums.CheckEnum(*rhs)){
          rhs_value = enums.GetEnum(*rhs);
          output << "li $2," << rhs_value << std::endl;
        }
        else{
          rhs_value = local_variables.getValue(*rhs);
          int rhs_mem_location = memory.FindVariable(*rhs);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getRightSideOfExpression());
        rhs_value = rhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $2," << (rhs_value+1) << std::endl;
        }
        else{
          output << "li $2," << rhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      output << "nop\n";



      if(condition == "<"){
        output << "slt $2,$3,$2\nbeq $2,$0," << if_not << std::endl;
      }

      else if(condition == ">"){
        output << "slt $2,$2,$3\nbeq $2,$0," << if_not << std::endl;
      }

      else if(condition == "<="){
        output << "slt $2,$3,$2\nbeq $2,$0," << if_not << std::endl;
      }

      else if(condition == ">="){
        output << "slt $2,$2,$3\nbeq $2,$0," << if_not << std::endl;
      }

      output << "nop\n";
    }

    else if(expr_type == "EqualityExpression"){
      const EqualityExpression* tmp_equal = dynamic_cast<const EqualityExpression*>(expr->getExpression());
      long long int lhs_value, rhs_value, addition_value;
      std::string test = getTypes(tmp_equal->getLeftSideOfExpression());
      if(test == "PostfixExpression"){
        const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getLeftSideOfExpression());
        if(lhs_node->getTypes() == "array"){
          int lhs_mem_location = CompileArray(output, lhs_node);
          output << "lw $2," << lhs_mem_location << "($fp)\n";
        }
        else if(lhs_node->getTypes() == "function"){
          const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
          if(getTypes(lhs_node->getOthers()) == "Expression"){
            const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
            if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* lhs_function_name = lhs_function_name_node->getName();
          output << "jal " << *lhs_function_name << std::endl;
          output << "nop\n";
        }
      }

      test = getTypes(tmp_equal->getRightSideOfExpression());

      if(test == "PostfixExpression"){
        const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getRightSideOfExpression());
        if(rhs_node->getTypes() == "array"){
          int rhs_mem_location = CompileArray(output, rhs_node);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
        else if(rhs_node->getTypes() == "function"){
          const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
          if(getTypes(rhs_node->getOthers()) == "Expression"){
            const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
            if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* rhs_function_name = rhs_function_name_node->getName();
          output << "jal " << *rhs_function_name << std::endl;
          output << "nop\n";
        }
      }
      test = getTypes(tmp_equal->getLeftSideOfExpression());
      if(test == "identifierC"){
        const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_equal->getLeftSideOfExpression());
        const std::string* lhs = lhs_node->getName();
        if(enums.CheckEnum(*lhs)){
          lhs_value = enums.GetEnum(*lhs);
          output << "li $3," << lhs_value << std::endl;
        }
        else{
          lhs_value = local_variables.getValue(*lhs);
          int lhs_mem_location = memory.FindVariable(*lhs);
          output << "lw $3," << lhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getLeftSideOfExpression());
        lhs_value = lhs_node->getIntConstantValue();
        output << "li $3," << lhs_value << std::endl;
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
      }

      test = getTypes(tmp_equal->getRightSideOfExpression());

      if(test == "identifierC"){
        const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_equal->getRightSideOfExpression());
        const std::string* rhs = rhs_node->getName();
        if(enums.CheckEnum(*rhs)){
          rhs_value = enums.GetEnum(*rhs);
          output << "li $2," << rhs_value << std::endl;
        }
        else{
          rhs_value = local_variables.getValue(*rhs);
          int rhs_mem_location = memory.FindVariable(*rhs);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getRightSideOfExpression());
        rhs_value = rhs_node->getIntConstantValue();
        output << "li $2," << rhs_value << std::endl;
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
      }

      output << "nop\n";

      std::string condition(tmp_equal->getConditionForEquality());

      if(condition == "=="){
        output << "subu $2,$2,$3\nbne $2,$0," << if_not << std::endl;
      }

      else if(condition == "!="){
        output << "subu $2,$2,$3\nbeq $2,$0," << if_not << std::endl;
      }

      output << "nop\n";
    }

    CompileBody(output, if_state->getIf());

    output << if_not << ":\n";

    if(if_state->getELSE() != nullptr){
      CompileBody(output, if_state->getELSE());
    }
    else{
      output << "nop\n";
    }



  }
}

void CompileForLoops(std::ofstream& output, const Node* ast){


  const ForStatement* for_state = dynamic_cast<const ForStatement*>(ast);
  //first expression
  std::string expression1 = getTypes(for_state->getExpressionStatement1());
  if(expression1 == "Expression"){
    CompileExpression(output, for_state->getExpressionStatement1());
  }
  //begin start of loop
  std::string for_start = makeName("for_start");
  loop_names.push_back(for_start);
  std::string for_end = makeName("for_end");
  output << for_start << ":\n";
  //second expression
  std::string expression2 = getTypes(for_state->getExpressionStatement2());
  if(expression2 == "Expression"){
    const Expression* expr_2 = dynamic_cast<const Expression*>(for_state->getExpressionStatement2());
    if(getTypes(expr_2->getExpression()) == "RelationalExpression"){
      const RelationalExpression* tmp_relational = dynamic_cast<const RelationalExpression*>(expr_2->getExpression());
      std::string condition(tmp_relational->getConditionForRelation());
      std::string test = getTypes(tmp_relational->getLeftSideOfExpression());
      if(test == "PostfixExpression"){
        const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getLeftSideOfExpression());
        if(lhs_node->getTypes() == "array"){
          int lhs_mem_location = CompileArray(output, lhs_node);
          output << "lw $2," << lhs_mem_location << "($fp)\n";
        }
        else if(lhs_node->getTypes() == "function"){
          const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
          if(getTypes(lhs_node->getOthers()) == "Expression"){
            const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
            if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* lhs_function_name = lhs_function_name_node->getName();
          output << "jal " << *lhs_function_name << std::endl;
          output << "nop\n";
        }
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());

      if(test == "PostfixExpression"){
        const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getRightSideOfExpression());
        if(rhs_node->getTypes() == "array"){
          int rhs_mem_location = CompileArray(output, rhs_node);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
        else if(rhs_node->getTypes() == "function"){
          const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
          if(getTypes(rhs_node->getOthers()) == "Expression"){
            const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
            if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* rhs_function_name = rhs_function_name_node->getName();
          output << "jal " << *rhs_function_name << std::endl;
          output << "nop\n";
        }
      }
      test = getTypes(tmp_relational->getLeftSideOfExpression());
      long long int lhs_value, rhs_value;
      if(test == "identifierC"){
        const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_relational->getLeftSideOfExpression());
        const std::string* lhs = lhs_node->getName();
        if(enums.CheckEnum(*lhs)){
          lhs_value = enums.GetEnum(*lhs);
          output << "li $3," << lhs_value << std::endl;
        }
        else{
          lhs_value = local_variables.getValue(*lhs);
          int lhs_mem_location = memory.FindVariable(*lhs);
          output << "lw $3," << lhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getLeftSideOfExpression());
        lhs_value = lhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $3," << (lhs_value+1) << std::endl;
        }
        else{
          output << "li $3," << lhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());


      if(test == "identifierC"){
        const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_relational->getRightSideOfExpression());
        const std::string* rhs = rhs_node->getName();
        if(enums.CheckEnum(*rhs)){
          rhs_value = enums.GetEnum(*rhs);
          output << "li $2," << rhs_value << std::endl;
        }
        else{
          rhs_value = local_variables.getValue(*rhs);
          int rhs_mem_location = memory.FindVariable(*rhs);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getRightSideOfExpression());
        rhs_value = rhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $2," << (rhs_value+1) << std::endl;
        }
        else{
          output << "li $2," << rhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      output << "nop\n";



      if(condition == "<"){
        output << "slt $2,$3,$2\n";
      }

      else if(condition == ">"){
        output << "slt $2,$2,$3\n";
      }

      else if(condition == "<="){
        output << "slt $2,$3,$2\n";
      }

      else if(condition == ">="){
        output << "slt $2,$2,$3\n";
      }

      output << "beq $2,$0," << for_end << std::endl;
      output << "nop\n";
    }
  }
  //in for loop
  std::string for_body = getTypes(for_state->getForStatement());
  if(for_body == "CompoundStatement"){
    CompileBody(output, for_state->getForStatement());
  }
  //third expression
  if(for_state->HasExpression()){
    std::string expression3 = getTypes(for_state->getExpression());
    if(expression3 == "Expression"){
      CompileExpression(output, for_state->getExpression());
    }
  }
  //final_statement
  output << "b " << for_start << std::endl;
  output << "nop\n";
  output << for_end << ":\n";
}

void CompileWhileStatement(std::ofstream& output, const Node* ast){
  const WhileStatement* tmp_while = dynamic_cast<const WhileStatement*>(ast);
  std::string while_start = makeName("while_start");
  loop_names.push_back(while_start);
  std::string while_end = makeName("while_end");
  output << while_start << ":\n";
  std::string parameter_type = getTypes(tmp_while->getWhileParameter());
  if(parameter_type == "Expression"){
    const Expression* expr = dynamic_cast<const Expression*>(tmp_while->getWhileParameter());
    if(expr->getNext() != nullptr){
      CompileWhileStatement(output, expr->getNext());
    }
    std::string node_type = getTypes(expr->getExpression());

    if(node_type == "RelationalExpression"){

      const RelationalExpression* tmp_relational = dynamic_cast<const RelationalExpression*>(expr->getExpression());
      std::string condition(tmp_relational->getConditionForRelation());
      std::string test = getTypes(tmp_relational->getLeftSideOfExpression());
      if(test == "PostfixExpression"){
        const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getLeftSideOfExpression());
        if(lhs_node->getTypes() == "array"){
          int lhs_mem_location = CompileArray(output, lhs_node);
          output << "lw $2," << lhs_mem_location << "($fp)\n";
        }
        else if(lhs_node->getTypes() == "function"){
          const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
          if(getTypes(lhs_node->getOthers()) == "Expression"){
            const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
            if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* lhs_function_name = lhs_function_name_node->getName();
          output << "jal " << *lhs_function_name << std::endl;
          output << "nop\n";
        }
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());

      if(test == "PostfixExpression"){
        const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_relational->getRightSideOfExpression());
        if(rhs_node->getTypes() == "array"){
          int rhs_mem_location = CompileArray(output, rhs_node);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
        else if(rhs_node->getTypes() == "function"){
          const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
          if(getTypes(rhs_node->getOthers()) == "Expression"){
            const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
            if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* rhs_function_name = rhs_function_name_node->getName();
          output << "jal " << *rhs_function_name << std::endl;
          output << "nop\n";
        }
      }
      test = getTypes(tmp_relational->getLeftSideOfExpression());
      long long int lhs_value, rhs_value;
      if(test == "identifierC"){
        const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_relational->getLeftSideOfExpression());
        const std::string* lhs = lhs_node->getName();
        if(enums.CheckEnum(*lhs)){
          lhs_value = enums.GetEnum(*lhs);
          output << "li $3," << lhs_value << std::endl;
        }
        else{
          lhs_value = local_variables.getValue(*lhs);
          int lhs_mem_location = memory.FindVariable(*lhs);
          output << "lw $3," << lhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getLeftSideOfExpression());
        lhs_value = lhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $3," << (lhs_value+1) << std::endl;
        }
        else{
          output << "li $3," << lhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getLeftSideOfExpression());
      }

      test = getTypes(tmp_relational->getRightSideOfExpression());


      if(test == "identifierC"){
        const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_relational->getRightSideOfExpression());
        const std::string* rhs = rhs_node->getName();
        if(enums.CheckEnum(*rhs)){
          rhs_value = enums.GetEnum(*rhs);
          output << "li $2," << rhs_value << std::endl;
        }
        else{
          rhs_value = local_variables.getValue(*rhs);
          int rhs_mem_location = memory.FindVariable(*rhs);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_relational->getRightSideOfExpression());
        rhs_value = rhs_node->getIntConstantValue();
        if((condition == "<=") || (condition == ">=")){
          output << "li $2," << (rhs_value+1) << std::endl;
        }
        else{
          output << "li $2," << rhs_value << std::endl;
        }
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_relational->getRightSideOfExpression());
      }

      output << "nop\n";



      if(condition == "<"){
        output << "slt $2,$3,$2\nbeq $2,$0," << while_end << std::endl;
      }

      else if(condition == ">"){
        output << "slt $2,$2,$3\nbeq $2,$0," << while_end << std::endl;
      }

      else if(condition == "<="){
        output << "slt $2,$3,$2\nbeq $2,$0," << while_end << std::endl;
      }

      else if(condition == ">="){
        output << "slt $2,$2,$3\nbeq $2,$0," << while_end << std::endl;
      }

      output << "nop\n";

    }

    else if(node_type == "identifierC"){
      const identifierC* name_node = dynamic_cast<const identifierC*>(expr->getExpression());
      if(enums.CheckEnum(*(name_node->getName()))){
        long long int lhs_value = enums.GetEnum(*(name_node->getName()));
        output << "li $2," << lhs_value << std::endl;
      }
      else{
        int equal_var_location = memory.FindVariable(*(name_node->getName()));
        output << "lw $2," << equal_var_location << "($fp)" << std::endl;
      }
      output << "nop\n";
      output << "beq $2,$0," << while_end << std::endl;
      output << "nop\n\n";
    }

    else if(node_type == "IntConstant"){
      const IntConstant* int_node = dynamic_cast<const IntConstant*>(expr->getExpression());
      long long int int_const = int_node->getIntConstantValue();
      if(int_const == 0){
        output << "b " << while_end << std::endl;
      }
      else{
        output << "b " << while_start << std::endl;
      }
    }

    else if(node_type == "EqualityExpression"){
      const EqualityExpression* tmp_equal = dynamic_cast<const EqualityExpression*>(expr->getExpression());
      long long int lhs_value, rhs_value, addition_value;
      std::string test = getTypes(tmp_equal->getLeftSideOfExpression());
      if(test == "PostfixExpression"){
        const PostfixExpression* lhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getLeftSideOfExpression());
        if(lhs_node->getTypes() == "array"){
          int lhs_mem_location = CompileArray(output, lhs_node);
          output << "lw $2," << lhs_mem_location << "($fp)\n";
        }
        else if(lhs_node->getTypes() == "function"){
          const identifierC* lhs_function_name_node = dynamic_cast<const identifierC*>(lhs_node->getPostfixExpression());
          if(getTypes(lhs_node->getOthers()) == "Expression"){
            const Expression* lhs_function_expr = dynamic_cast<const Expression*>(lhs_node->getOthers());
            if(getTypes(lhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, lhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* lhs_function_name = lhs_function_name_node->getName();
          output << "jal " << *lhs_function_name << std::endl;
          output << "nop\n";
        }
      }

      test = getTypes(tmp_equal->getRightSideOfExpression());

      if(test == "PostfixExpression"){
        const PostfixExpression* rhs_node = dynamic_cast<const PostfixExpression*>(tmp_equal->getRightSideOfExpression());
        if(rhs_node->getTypes() == "array"){
          int rhs_mem_location = CompileArray(output, rhs_node);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
        else if(rhs_node->getTypes() == "function"){
          const identifierC* rhs_function_name_node = dynamic_cast<const identifierC*>(rhs_node->getPostfixExpression());
          if(getTypes(rhs_node->getOthers()) == "Expression"){
            const Expression* rhs_function_expr = dynamic_cast<const Expression*>(rhs_node->getOthers());
            if(getTypes(rhs_function_expr->getExpression()) == "AdditiveExpression"){
              CompileAdditionExpressionNoMem(output, rhs_function_expr->getExpression());
              output << "move $4,$2\n";
            }
          }
          const std::string* rhs_function_name = rhs_function_name_node->getName();
          output << "jal " << *rhs_function_name << std::endl;
          output << "nop\n";
        }
      }
      test = getTypes(tmp_equal->getLeftSideOfExpression());
      if(test == "identifierC"){
        const identifierC* lhs_node = dynamic_cast<const identifierC*>(tmp_equal->getLeftSideOfExpression());
        const std::string* lhs = lhs_node->getName();
        if(enums.CheckEnum(*lhs)){
          lhs_value = enums.GetEnum(*lhs);
          output << "li $3," << lhs_value << std::endl;
        }
        else{
          lhs_value = local_variables.getValue(*lhs);
          int lhs_mem_location = memory.FindVariable(*lhs);
          output << "lw $3," << lhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* lhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getLeftSideOfExpression());
        lhs_value = lhs_node->getIntConstantValue();
        output << "li $3," << lhs_value << std::endl;
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_equal->getLeftSideOfExpression());
      }

      test = getTypes(tmp_equal->getRightSideOfExpression());

      if(test == "identifierC"){
        const identifierC* rhs_node = dynamic_cast<const identifierC*>(tmp_equal->getRightSideOfExpression());
        const std::string* rhs = rhs_node->getName();
        if(enums.CheckEnum(*rhs)){
          rhs_value = enums.GetEnum(*rhs);
          output << "li $2," << rhs_value << std::endl;
        }
        else{
          rhs_value = local_variables.getValue(*rhs);
          int rhs_mem_location = memory.FindVariable(*rhs);
          output << "lw $2," << rhs_mem_location << "($fp)\n";
        }
      }

      else if(test == "IntConstant"){
        const IntConstant* rhs_node = dynamic_cast<const IntConstant*>(tmp_equal->getRightSideOfExpression());
        rhs_value = rhs_node->getIntConstantValue();
        output << "li $2," << rhs_value << std::endl;
      }

      else if(test == "AdditiveExpression"){
        CompileAdditionExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
      }

      else if(test == "MultiplicativeExpression"){
        CompileMultiplicativeExpressionNoMem(output, tmp_equal->getRightSideOfExpression());
      }

      output << "nop\n";

      std::string condition(tmp_equal->getConditionForEquality());

      if(condition == "=="){
        output << "subu $2,$2,$3\nbne $2,$0," << while_end << std::endl;
      }

      else if(condition == "!="){
        output << "subu $2,$2,$3\nbeq $2,$0," << while_end << std::endl;
      }

      output << "nop\n";
    }
  }

  CompileBody(output, tmp_while->getWhileStatement());

  output << "b " << while_start << std::endl;
  output << "nop\n\n";

  output << while_end << ":\n";


}

void CompileDeclarationList(std::ofstream& output, const Node* ast){

  const InitDeclaratorList* list = dynamic_cast<const InitDeclaratorList*>(ast);
  if(list->hasPrevious()){
    const InitDeclaratorList* tmp = dynamic_cast<const InitDeclaratorList*>(list->getPrevious());
    CompileDeclarationList(output, tmp);
  }

  else{
    const InitDeclarator* tmp = dynamic_cast<const InitDeclarator*>(list->getPresent());

    std::string tmp_dec = getTypes(tmp->getDeclarator());

    if(tmp->hasInitialiser()){

      const identifierC* tmp_name_node = dynamic_cast<const identifierC*>(tmp->getDeclarator());
      const std::string* tmp_name = tmp_name_node->getName();


      if(getTypes(tmp->getInitialiser()) == "AdditiveExpression"){
        CompileAdditionExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "AndExpression"){
        CompileAndExpression(output, tmp->getInitialiser(), *tmp_name);
      }


      else if(getTypes(tmp->getInitialiser()) == "MultiplicativeExpression"){
        CompileMultiplicativeExpression(output, tmp->getInitialiser(), *tmp_name);
      }


      else if(getTypes(tmp->getInitialiser()) == "IntConstant"){
        CompileIntConstant(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "EqualityExpression"){
        CompileEqualityExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "RelationalExpression"){
        CompileRelationalExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "ExclusiveOrExpression"){
        CompileExclusiveOrExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "identifierC"){
        CompileidentifierC(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "InclusiveOrExpression"){
        CompileInclusiveOrExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "LogicalOrExpression"){
        CompileLogicalOrExpression(output, tmp->getInitialiser(), *tmp_name);
      }

      else if(getTypes(tmp->getInitialiser()) == "LogicalAndExpression"){
        CompileLogicalAndExpression(output, tmp->getInitialiser(), *tmp_name);
      }
    }

    if(tmp_dec == "Variable"){
      const Variable* var = dynamic_cast<const Variable*>(tmp->getDeclarator());
      const identifierC* var_name_node = dynamic_cast<const identifierC*>(var->getVariable_Identifier());
      const std::string* var_name = var_name_node->getName();
      std::string var_info = var->getVariable_Information();
      if(var_info == "array"){
        std::vector<int> var_tmp;
        std::string array_type = getTypes(var->getArray_Information());
        int array_size;
        if(array_type == "IntConstant"){
          const IntConstant* array_size_node = dynamic_cast<const IntConstant*>(var->getArray_Information());
          array_size = array_size_node->getIntConstantValue();
          var_tmp.resize(array_size, 0);
        }
        if(function_name.size() == 0){
          global_variables.addVariable(var_tmp);
        }
        else{
          std::vector<memlocation> copy_memory = memory.getMemory();
          int size = copy_memory.size();
          memlocation last_mem;
          if(size == 0){
            last_mem.location = 4;
          }
          else{
            memlocation last_mem = copy_memory[size];
          }
          for(int i = last_mem.location+4; i<(last_mem.location+4)+(array_size*4); i = i+4){
            int k=0;
            std::string array_string = *var_name;
            std::string ss = std::to_string(k);
            memory.AddValue(array_string+ss, i);
            k++;
          }
        }
      }
    }
  }
}

void CompileEnum(std::ofstream& output, const Node* ast){
  const EnumDeclarationListNode* enum_list = dynamic_cast<const EnumDeclarationListNode*>(ast);
  if(enum_list->ProgramHasNextEnumDeclaration()){
    CompileEnum(output, enum_list->getCurrentEnumDeclaration());
  }
  const EnumDeclaration* enum_dec = dynamic_cast<const EnumDeclaration*>(enum_list->getNextEnumDeclaration());
  const std::string* enum_var_name = enum_dec->getEnumID();
  if(enum_dec->ProgramHasEnumInitialValue()){
    const IntConstant* enum_value_node = dynamic_cast<const IntConstant*>(enum_dec->getEnumInitialValue());
    long long int enum_value = enum_value_node->getIntConstantValue();
    enums.AddEnum(*enum_var_name, enum_value);
  }
  else{
    enums.AddEnum(*enum_var_name);
  }
}

void CompileDeclarationSpecifier(std::ofstream& output, const Node* ast){
  if(ast->getType() == "EnumSpecifier"){
    const EnumSpecifier* enum_spec = dynamic_cast<const EnumSpecifier*>(ast);
    CompileEnum(output, enum_spec->getEnumerator());
  }
}

void CompileDeclaration(std::ofstream& output, const Node* ast){

  if(ast->getType() == "DeclarationList"){
    const DeclarationList* tmp = dynamic_cast<const DeclarationList*>(ast);
    if(tmp->hasPrevious()){
      CompileDeclaration(output, tmp->getPrevious());
    }
    CompileDeclaration(output, tmp->getPresent());
  }

  if(ast->getType() == "Declaration"){  //don't think you can have int nothing so havn't programmed it
    const Declaration* tmp = dynamic_cast<const Declaration*>(ast);
    std::string test = getTypes(tmp->getDeclaratorList()); //don't need to program float char unsigned yet
    if(test == "InitDeclaratorList"){
      const InitDeclaratorList* dec_list = dynamic_cast<const InitDeclaratorList*>(tmp->getDeclaratorList());
      CompileDeclarationList(output, dec_list);
      return;
    }
  }
}

void CompileAssignmentExpression(std::ofstream& output, const Node* ast){
  const AssignmentExpression* ass_expr = dynamic_cast<const AssignmentExpression*>(ast);
  //firstly get variable assigning to
  std::string var_name_type = getTypes(ass_expr->getLeftSideOfExpression());
  std::string var_name;
  if(var_name_type == "identifierC"){
    const identifierC* var_name_node = dynamic_cast<const identifierC*>(ass_expr->getLeftSideOfExpression());
    const std::string* var_name_pointer = var_name_node->getName();
    var_name = *var_name_pointer;
  }
  if(var_name_type == "PostfixExpression"){
    const PostfixExpression* var_name_node = dynamic_cast<const PostfixExpression*>(ass_expr->getLeftSideOfExpression());
    if(var_name_node->getTypes() == "array"){
      std::string ss;
      const identifierC* array_name_node = dynamic_cast<const identifierC*>(var_name_node->getPostfixExpression());
      const Expression* expr = dynamic_cast<const Expression*>(var_name_node->getOthers());
      if(getTypes(expr->getExpression()) == "IntConstant"){
        const IntConstant* int_const_node = dynamic_cast<const IntConstant*>(expr->getExpression());
        ss = std::to_string(int_const_node->getIntConstantValue());
      }
      if(getTypes(expr->getExpression()) == "AdditiveExpression"){
        std::string inside_array = makeName("array");
        CompileAdditionExpression(output,expr->getExpression(), inside_array);
        int place = local_variables.getValue(inside_array);
        ss = std::to_string(place);
      }
      if(getTypes(expr->getExpression()) == "identifierC"){
        const identifierC* array_place_name = dynamic_cast<const identifierC*>(expr->getExpression());
        int tmp = local_variables.getValue(*array_place_name->getName());
        std::string ss = std::to_string(tmp);
      }
      std::string array_string = *array_name_node->getName();
      var_name = array_string+ss;
    }
  }
  //secondly getting which assignment
  const std::string* var_assignment_type = ass_expr->getAssignment();
  if(*var_assignment_type == "="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "AdditiveExpression"){
      CompileAdditionExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "AndExpression"){
      CompileAndExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "MultiplicativeExpression"){
      CompileMultiplicativeExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "IntConstant"){
      CompileIntConstant(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "EqualityExpression"){
      CompileEqualityExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "RelationalExpression"){
      CompileRelationalExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "ExclusiveOrExpression"){
      CompileExclusiveOrExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "identifierC"){
      CompileidentifierC(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "InclusiveOrExpression"){
      CompileInclusiveOrExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "LogicalOrExpression"){
      CompileLogicalOrExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
    else if(var_expr_type == "LogicalAndExpression"){
      CompileLogicalAndExpression(output, ass_expr->getRightSideOfExpression(), var_name);
    }
  }

  if(*var_assignment_type == "+="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "identifierC"){
      const identifierC* equating_name = dynamic_cast<const identifierC*>(ass_expr->getRightSideOfExpression());
      int equal_var_location = memory.FindVariable(var_name);
      int rhs_var_location = memory.FindVariable(*(equating_name->getName()));
      output << "lw $2," << equal_var_location << "($fp)\n";
      output << "lw $3," << rhs_var_location << "($fp)\n";
      output << "nop\n";
      output << "addu $2,$3,$2\n";
      output << "sw $2," << equal_var_location << "($fp)\n";
    }
  }
  if(*var_assignment_type == "-="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "identifierC"){
      const identifierC* equating_name = dynamic_cast<const identifierC*>(ass_expr->getRightSideOfExpression());
      int equal_var_location = memory.FindVariable(var_name);
      int rhs_var_location = memory.FindVariable(*(equating_name->getName()));
      output << "lw $2," << equal_var_location << "($fp)\n";
      output << "lw $3," << rhs_var_location << "($fp)\n";
      output << "nop\n";
      output << "subu $2,$2,$3\n";
      output << "sw $2," << equal_var_location << "($fp)\n";
    }
  }
  if(*var_assignment_type == "*="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "identifierC"){
      const identifierC* equating_name = dynamic_cast<const identifierC*>(ass_expr->getRightSideOfExpression());
      int equal_var_location = memory.FindVariable(var_name);
      int rhs_var_location = memory.FindVariable(*(equating_name->getName()));
      output << "lw $2," << equal_var_location << "($fp)\n";
      output << "lw $3," << rhs_var_location << "($fp)\n";
      output << "nop\n";
      output << "mult $2,$3\n";
      output << "mflo $2\n";
      output << "sw $2," << equal_var_location << "($fp)\n";
    }
  }
  if(*var_assignment_type == "/="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "identifierC"){
      const identifierC* equating_name = dynamic_cast<const identifierC*>(ass_expr->getRightSideOfExpression());
      int equal_var_location = memory.FindVariable(var_name);
      int rhs_var_location = memory.FindVariable(*(equating_name->getName()));
      output << "lw $2," << equal_var_location << "($fp)\n";
      output << "lw $3," << rhs_var_location << "($fp)\n";
      output << "nop\n";
      output << "div $2,$3\n";
      output << "mflo $2\n";
      output << "sw $2," << equal_var_location << "($fp)\n";
    }
  }
  if(*var_assignment_type == "%="){
    std::string var_expr_type = getTypes(ass_expr->getRightSideOfExpression());
    if(var_expr_type == "identifierC"){
      const identifierC* equating_name = dynamic_cast<const identifierC*>(ass_expr->getRightSideOfExpression());
      int equal_var_location = memory.FindVariable(var_name);
      int rhs_var_location = memory.FindVariable(*(equating_name->getName()));
      output << "lw $2," << equal_var_location << "($fp)\n";
      output << "lw $3," << rhs_var_location << "($fp)\n";
      output << "nop\n";
      output << "div $2,$3\n";
      output << "mfhi $2\n";
      output << "sw $2," << equal_var_location << "($fp)\n";
    }
  }


}

void CompilePostfixExpression(std::ofstream& output, const Node* ast){
  const PostfixExpression* expr = dynamic_cast<const PostfixExpression*>(ast);
  const identifierC* name_node = dynamic_cast<const identifierC*>(expr->getPostfixExpression());
  const std::string* name_expr = name_node->getName();
  long long int var_value = local_variables.getValue(*name_expr);
  int name_expr_location = memory.FindVariable(*name_expr);
  output << "lw $2," << name_expr_location << "($fp)\n";
  output << "nop\n";
  std::string type_expr = expr->getTypes();
  if(type_expr == "++"){
    output << "addiu $2,$2,1\n";
    var_value++;
  }
  if(type_expr == "--"){
    output << "addiu $2,$2,-1\n";
    var_value--;
  }
  output << "sw $2," << name_expr_location << "($fp)" <<std::endl;
  local_variables.addValue(*name_expr, var_value);
}

void CompileBreakStatement(std::ofstream& output, const Node* ast){
  output << "b " << function_return << std::endl;
  output << "nop\n";
}

void CompileContinueStatement(std::ofstream& output, const Node* ast){
  std::string loop_back = loop_names.back();
  output << "b " << loop_back << std::endl;
  output << "nop\n";
}

std::vector<std::string> CompileCases(std::ofstream& output, const Node* ast, std::vector<std::string> case_names){
  const StatementListNode* tmp = dynamic_cast<const StatementListNode*>(ast);
  if(tmp->hasStatement()){
    case_names = CompileCases(output, tmp->getStatement(), case_names);
  }
  if(getTypes(tmp->getNextStatement()) == "LabeledStatement"){
    const LabeledStatement* case_node = dynamic_cast<const LabeledStatement*>(tmp->getNextStatement());
    if(case_node->hasConst()){
      if(getTypes(case_node->getConstExpression()) == "IntConstant"){
        const IntConstant* int_node = dynamic_cast<const IntConstant*>(case_node->getConstExpression());
        long long int value = int_node->getIntConstantValue();
        output << "li $3," << value << std::endl;
        std::string name = makeName("case");
        case_names.push_back(name);
        output << "beq $2,$3," << name << std::endl;
        output << "nop\n";
      }
    }
    else{
      if(getTypes(case_node->getIdentity()) == "DefaultNode"){
        std::string name = makeName("default");
        case_names.push_back(name);
        output << "b " << name << std::endl;
        output << "nop\n";
      }
    }
  }
  return case_names;
}

std::vector<std::string> CompileCaseBody(std::ofstream& output, const Node* ast, std::vector<std::string> case_names){
  const StatementListNode* tmp = dynamic_cast<const StatementListNode*>(ast);
  if(tmp->hasStatement()){
    case_names = CompileCaseBody(output, tmp->getStatement(), case_names);
  }
  if(getTypes(tmp->getNextStatement()) == "LabeledStatement"){
    const LabeledStatement* case_node = dynamic_cast<const LabeledStatement*>(tmp->getNextStatement());
    output << case_names[0] << ":" << std::endl;
    case_names.erase(case_names.begin());
    CompileStatement(output,case_node->getStatement());
  }
  return case_names;
}

void CompileSwitchStatement(std::ofstream& output, const Node* ast){
  const SwitchStatement* switch_state = dynamic_cast<const SwitchStatement*>(ast);
  if(getTypes(switch_state->getSwitch()) == "Expression"){ //finding original condition
    const Expression* expr = dynamic_cast<const Expression*>(switch_state->getSwitch());
    if(getTypes(expr->getExpression()) == "identifierC"){
      const identifierC* name_node = dynamic_cast<const identifierC*>(expr->getExpression());
      std::string name = *name_node->getName();
      int name_mem_location = memory.FindVariable(name);
      output << "lw $2," << name_mem_location << "($fp)\n";
    }
  }

  if(getTypes(switch_state->getBody()) == "CompoundStatement"){
    const CompoundStatement* compound_state = dynamic_cast<const CompoundStatement*>(switch_state->getBody());
    if(getTypes(compound_state->getStatementList()) == "StatementListNode"){
      std::vector<std::string> case_names;
      case_names = CompileCases(output, compound_state->getStatementList(), case_names);
      output << "b " << function_return << std::endl;
      output << "nop" << std::endl;
      case_names = CompileCaseBody(output, compound_state->getStatementList(), case_names);
    }
  }
}

void CompileExpression(std::ofstream& output, const Node* ast){
  const Expression* tmp = dynamic_cast<const Expression*>(ast);
  if(tmp->getNext() != nullptr){
    CompileExpression(output, tmp->getNext());
  }
  else{
    std::string nextName = getTypes(tmp->getExpression());

    if(nextName == "AssignmentExpression"){
        CompileAssignmentExpression(output, tmp->getExpression());
    }
    if(nextName == "PostfixExpression"){
        CompilePostfixExpression(output, tmp->getExpression());
    }
  }
}

void CompileStatement(std::ofstream& output, const Node* ast){

  if(ast->getType() == "StatementListNode"){
    const StatementListNode* state_list = dynamic_cast<const StatementListNode*>(ast);
    if(state_list->getStatement() != nullptr){
      CompileStatement(output, state_list->getStatement());
    }
    std::string statement_name = getTypes(state_list->getNextStatement());
    if(statement_name == "ReturnStatement"){
      const ReturnStatement* return_state = dynamic_cast<const ReturnStatement*>(state_list->getNextStatement());
      if(return_state->HasExpression()){
        CompileReturnStatement(output, return_state->getExpression());
      }
      else{
        output << "b " << function_return << std::endl;
        output << "nop\n";
      }
    }
    if(statement_name == "Expression"){
      CompileExpression(output, state_list->getNextStatement());
    }
    if(statement_name == "IfStatement"){
      CompileIfCondition(output, state_list->getNextStatement());
    }
    if(statement_name == "WhileStatement"){
      CompileWhileStatement(output, state_list->getNextStatement());
    }
    if(statement_name == "ForStatement"){
      CompileForLoops(output, state_list->getNextStatement());
    }
    if(statement_name == "SwitchStatement"){
      CompileSwitchStatement(output, state_list->getNextStatement());
    }
    if(statement_name == "BreakStatement"){
      CompileBreakStatement(output, state_list->getNextStatement());
    }
    if(statement_name == "ContinueStatement"){
      CompileContinueStatement(output, state_list->getNextStatement());
    }
  }

  else if(ast->getType() == "LabeledInternalList"){
    const LabeledInternalList* state_list = dynamic_cast<const LabeledInternalList*>(ast);
    if(state_list->getNext() != nullptr){
      CompileStatement(output, state_list->getNext());
    }
    std::string statement_name = getTypes(state_list->getStatement());
    if(statement_name == "ReturnStatement"){
      const ReturnStatement* return_state = dynamic_cast<const ReturnStatement*>(state_list->getStatement());
      if(return_state->HasExpression()){
        CompileReturnStatement(output, return_state->getExpression());
      }
      else{
        output << "b " << function_return << std::endl;
        output << "nop\n";
      }
    }
    if(statement_name == "Expression"){
      CompileExpression(output, state_list->getStatement());
    }
    if(statement_name == "IfStatement"){
      CompileIfCondition(output, state_list->getStatement());
    }
    if(statement_name == "WhileStatement"){
      CompileWhileStatement(output, state_list->getStatement());
    }
    if(statement_name == "ForStatement"){
      CompileForLoops(output, state_list->getStatement());
    }
    if(statement_name == "SwitchStatement"){
      CompileSwitchStatement(output, state_list->getStatement());
    }
    if(statement_name == "BreakStatement"){
      CompileBreakStatement(output, state_list->getStatement());
    }
  }
}


void CompileBody(std::ofstream& output, const Node* ast){

  if(ast->getType() == "CompoundStatement"){
    const CompoundStatement* tmp = dynamic_cast<const CompoundStatement*>(ast);


    if(tmp->hasNext()){  //if has declarations
      CompileDeclaration(output, tmp->getDeclaration());
    }
    if(tmp->hasLists()){ //if has statements
      CompileStatement(output, tmp->getStatementList());
    }
  }

}


void compileFunction(std::ofstream& output, const FunctionDefinition* ast){

  function_return = makeName("return");

  bool exit_token = false;

  bool has_func_call = CallFunction(exit_token, ast->getContentsOfFunction());

  int mem_size = 0;
  stack_size = MemoryAllocator(mem_size, ast);

  //getting function name
  functions func_name_struct = function_declarations.GetFunctionName();
  function_name = *func_name_struct.funcs_name;
  output << ".globl " << function_name << std::endl;
  output << ".ent " << function_name << std::endl;
  output << function_name << ":\n";
  if(has_func_call){
    output << ".frame $fp," << stack_size << ",$31\n";
  }


  //assigning function memory
  output << "addiu $sp,$sp," << (-1*stack_size) << std::endl;
  if(has_func_call){
    output << "sw $31," << (stack_size-4) << "($sp)\n";
    output << "sw $fp," << (stack_size-8) << "($sp)\n";
  }
  else{
    output << "sw $fp," << (stack_size-4) << "($sp)\n";
  }
  output << "move $fp,$sp\n";
  if(has_func_call){
    output << ".cprestore " << (stack_size-16) << std::endl;
  }

  //get arguments

  const Variable* var = dynamic_cast<const Variable*>(ast->getNodeName());
  no_arguments = 0;
  no_arguments = CountArguments(no_arguments, var);
  //stack_size = stack_size+((no_arguments-4)*4);
  function_declarations.AddFunctionArgs(func_name_struct.funcs_name, no_arguments);

  for(int i=no_arguments-1; i>=0; i--){
    register_declarations.AddVariable(arg_name[i], (4+i) );
  }

  if(no_arguments>0){
    for(int i=0; i<no_arguments; i++){
      if(i<5){
        int reg_number = 4+i;
        int mem_location = (stack_size + ((i)*4));
        const std::string var_name = register_declarations.getRegister(reg_number);
        memory.AddValue(var_name, mem_location);
        output << "sw $" << reg_number << "," << mem_location << "($fp)\n";
      }
      else{

      }
    }
  }

  //getting body of function

  CompileBody(output, ast->getContentsOfFunction());



  //final ending to functions

  output << function_return << ":" << std::endl;

  output << "move $sp,$fp\n";
  if(has_func_call){
    output << "lw $31," << (stack_size-4) << "($sp)\n";
    output << "lw $fp," << (stack_size-8) << "($sp)\n";
  }
  else{
    output << "lw $fp," << (stack_size-4) << "($sp)\n";
  }
  output << "addiu $sp,$sp," << (stack_size) << "\njr $31\nnop\n";
  output << ".end " << function_name << std::endl;
}

void compilerAst(std::ofstream& output,std::vector<const Node*> ast_roots){
  for(const Node* ast: ast_roots){ //big boi for loop

    if(ast->getType() == "Declaration"){
      const Declaration* tmp_dec = dynamic_cast<const Declaration*>(ast);
      if(tmp_dec->hasDeclarationList()){
        CompileDeclarationList(output, tmp_dec->getDeclaratorList());
      }
      if(tmp_dec->hasDeclarationSpecifier()){
        CompileDeclarationSpecifier(output, tmp_dec->getDeclaratorSpecifiers());
      }
    }


    if(ast->getType() == "FunctionDefinition"){ //added defining functions to class
      const FunctionDefinition* func_definition = dynamic_cast<const FunctionDefinition*>(ast);
      const std::string* func_name;
      std::string name_type = getTypes(func_definition->getNodeName());
      if(name_type == "Variable"){
        const Variable* var = dynamic_cast<const Variable*>(func_definition->getNodeName());
        name_type = getTypes(var->getVariable_Identifier());
        if(name_type == "identifierC"){
          const identifierC* func_name_node = dynamic_cast<const identifierC*>(var->getVariable_Identifier());
          func_name = func_name_node->getName();
          function_declarations.AddFunctionName(func_name);
          compileFunction(output, func_definition);
        }
      }
    }
  }
}


int compiler(const std::string& input_file, const std::string& output_file){
  FILE* input;

  input = fopen(input_file.c_str(), "r");


  //reading from this file
  yyset_in(input);

  if (!(input = fopen(input_file.c_str(), "r"))) {  //testing to see if can read
    std::cerr << "Cannot open source file: '" << input_file << "'." << std::endl;
    return 1;
  }

  //preparing output file
  std::ofstream output;
  output.open(output_file);

  std::vector<const Node*> ast_roots = parseAST();  //setting up nodes


  compilerAst(output, ast_roots);  //starting the rabit hole

  fclose(input);

  output.close();

  return 0;
}
