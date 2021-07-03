#include <iostream>
#include <fstream>

#include python_interpreter

int main()
{
    const Expression *ast=parseAST();

    ast->print(std::cout);
    std::cout<<std::endl;

    return 0;
}
