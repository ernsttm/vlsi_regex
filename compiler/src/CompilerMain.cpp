//
// Created by todd on 11/18/18.
//
#include <fstream>
#include <iostream>
#include <string>

#include "compiler/RootCompiler.h"

// A simple utility method to read the regular expression out of the given regular expression file.
std::string getRegexString(std::string fileName) {
  std::string regexLine;

  std::ifstream file(fileName);
  if (file.is_open()) {
    if (!getline(file, regexLine)) {
      throw std::invalid_argument(fileName + " doesn't contain a regular expression.");
    }
    file.close();
  } else {
    throw std::invalid_argument(fileName + " can't be opened.");
  }

  return regexLine;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage : ./regex_compiler <regex_file> <output_file> "
                 "\n\tregex_file : The file containing the regular expression to compile."
                 "\n\toutput_file : The name of the file to output the compiled Verilog to.";
  }

  std::string regexString = getRegexString(argv[1]);
  compiler::RootCompiler regexCompiler { };
}