#ifndef python_translator_Translating_Statement_Functions_hpp
#define python_translator_Translating_Statement_Functions_hpp

#include <string>
#include <iostream>
#include "../common/inc/ast.hpp"


// this is to Translating the condition of the below statements
void Translating_Condition_Of_Statement(const Node* Condition, std::ofstream& output_python_file);

/// THINKING OF PUTTING ALL THE BELOW STATEMENT TRANSLATION FUNCTIONS IN SEPERATE FILE TO SEPERATE THE python_interpreter file.
void TranslatingReturnStatement(int NumberOfIndents, std::ofstream& output_python_file, const ReturnStatement* return_state);





void TranslatingIfStatement(int NumberOfIndents, std::ofstream& output_python_file, const IfStatement* if_state);
void TranslatingWhileStatement(int NumberOfIndents, std::ofstream& output_python_file, const WhileStatement* while_state);
void TranslatingSwitchStatement(int NumberOfIndents, std::ofstream& output_python_file, const SwitchStatement* switch_state);
void TranslatingDoStatement(int NumberOfIndents, std::ofstream& output_python_file, const DoStatement* do_state);
void TranslatingForStatement(int NumberOfIndents, std::ofstream& output_python_file, const ForStatement* for_state);
void TranslatingGoToStatement(int NumberOfIndents, std::ofstream& output_python_file, const GoToStatement* go_to_state);
void TranslatingContinueStatement(int NumberOfIndents, std::ofstream& output_python_file, const ContinueStatement* continue_state);
void TranslatingBreakStatement(int NumberOfIndents, std::ofstream& output_python_file, const BreakStatement* break_state);


#endif
