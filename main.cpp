#include <iostream>
#include <string>

#include "Compiler/compiler.hpp"
#include "Python_Translator/py_translator/python_interpreter.hpp"

void printerror();

int main(int argc, char** argv){
  if(argc != 5){
    printerror();
    return 1;
  }
  std::string token(argv[1]);
  std::string input(argv[2]);
  std::string link(argv[3]);
  std::string output(argv[4]);
  if((token == "--translate") && (link == "-o")){
    return python_Translating_main(input, output);
  }
  if((token == "-S") && (link == "-o")){
    return compiler(input, output);
  }
  printerror();
  return 1;
}

void printerror(){
  std::cout << "Needs 4 inputs" << std::endl;
  std::cout << "################################################" << std::endl;
  std::cout << "FORMAT FOR TRANSLATOR:" << std::endl;
  std::cout << "bin/c_compiler --translate [source-file.c] -o [dest-file.py]" << std::endl;
  std::cout << "################################################" << std::endl;
  std::cout << "FORMAT FOR COMPILER:" << '\n';
  std::cout << "bin/c_compiler -S [source-file.c] -o [dest-file.s]" << '\n';
}
