#include "IndentationAdder.hpp"

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdio>

//INDENTATIONLEVEL is the variable that will be used for determining the number of indents req for python.
//The number of indents for python is 2 spaces

const std::string INDENTATIONLEVEL = "  ";

// We need a function that will apply the indents appropiately.

void AppropiateAmountOfIndents(int NumberOfIndents, std::ofstream& output_python_file) {
  for (int i = 0; i < NumberOfIndents; i++)
  {
    output_python_file << INDENTATIONLEVEL;
  }
}
