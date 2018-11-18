//
// Created by todd on 11/18/18.
//
#include <fstream>
#include <iostream>
#include <string>

#include "compiler/Compiler.h"
#include "parser/Parser.h"

// A simple utility method to read the regular expression out of the given regular expression file.
std::string getRegexString(const std::string& fileName) {
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

void outputModule(const std::string& fileName, std::shared_ptr<compiler::Compiler>& compiledModule) {
  std::ofstream file { };

  file.open(fileName);
  file << compiledModule->initializationText();
  file << compiledModule->combinationalText();
  file << compiledModule->sequentialText();
  file.close();
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage : ./regex_compiler <regex_file> <output_file> "
                 "\n\tregex_file : The file containing the regular expression to compile."
                 "\n\toutput_file : The name of the file to output the compiled Verilog to.";
    exit(-1);
  }

  std::string regexString = getRegexString(argv[1]);

  // Parse the string into an AST
  compiler::Parser parser { };
  std::shared_ptr<compiler::Codon> root = parser.parse(regexString);

  // Compile the AST into a Verilog module
  std::shared_ptr<compiler::Compiler> compiledModule = compiler::Compiler::compile(root);
  outputModule(argv[2], compiledModule);
}