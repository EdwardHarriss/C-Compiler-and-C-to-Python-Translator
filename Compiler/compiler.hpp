#ifndef compiler_hpp
#define compiler_hpp

#include "../common/inc/ast.hpp"


#include <string>
#include <vector>

std::string makeName(std::string base);

std::string getTypes(const Node* ast);

int MoveArguments(std::ofstream& output, int no, const Node* ast);

int CountTerms(std::ofstream& output, int no, const Node* ast);

void CompileReturnStatement(std::ofstream& output, const ReturnStatement* ast);

void CompileBody(std::ofstream& output, const Node* ast);

void CompilePostfixExpression(std::ofstream& output, const Node* ast);

int CountArguments(int no, const Node* ast);

void CompileExpression(std::ofstream& output, const Node* ast);

void CompileAdditionExpression(std::ofstream& output, const Node* ast, const std::string var_name);

bool CallFunction(const Node* ast);

std::string getTypes(const Node* ast);

int MemoryAllocator(int mem_size, const Node* ast);

int CompileArray(std::ofstream& output, const PostfixExpression* ast);

void compileFunction(std::ofstream& ast, const FunctionDefinition* output);

void compilerAst(std::ofstream& output,std::vector<const Node*> ast_roots);

int compiler(const std::string& input_file, const std::string& output_file);

void CompileAdditionExpressionNoMem(std::ofstream& output, const Node* ast);

std::vector<std::string> CompileCaseBody(std::ofstream& output, const Node* ast, std::vector<std::string> case_names);

void CompileStatement(std::ofstream& output, const Node* ast);

void CompileLogicalAndExpressionNoMem(std::ofstream& output, const Node* ast);

void CompileCallingtoFunction(std::ofstream& output, const Node* ast, int arguments);

void CompileMultiplicativeExpressionNoMem(std::ofstream& output, const Node* ast);

void CompileAndExpression(std::ofstream& output, const Node* ast, const std::string var_name);

void CompileMultiplicativeExpression(std::ofstream& output, const Node* ast, const std::string var_name);

void CompileIntConstant(std::ofstream& output, const Node* ast, std::string var_name);

void CompileEqualityExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileRelationalExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileExclusiveOrExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileInclusiveOrExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileidentifierC(std::ofstream& output, const Node* ast, std::string var_name);

void CompileLogicalOrExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileLogicalAndExpression(std::ofstream& output, const Node* ast, std::string var_name);

void CompileIfCondition(std::ofstream& output, const Node* ast);

void CompileForLoops(std::ofstream& output, const Node* ast);

void CompileWhileStatement(std::ofstream& output, const Node* ast);

void CompileDeclarationList(std::ofstream& output, const Node* ast);

void CompileEnum(std::ofstream& output, const Node* ast);

void CompileDeclarationSpecifier(std::ofstream& output, const Node* ast);

void CompileDeclaration(std::ofstream& output, const Node* ast);

void CompileAssignmentExpression(std::ofstream& output, const Node* ast);

void CompileBreakStatement(std::ofstream& output, const Node* ast);

void CompileContinueStatement(std::ofstream& output, const Node* ast);

std::vector<std::string> CompileCases(std::ofstream& output, const Node* ast, std::vector<std::string> case_names);

std::vector<std::string> CompileCaseBody(std::ofstream& output, const Node* ast, std::vector<std::string> case_names);

void CompileSwitchStatement(std::ofstream& output, const Node* ast);

#endif compiler_hpp
