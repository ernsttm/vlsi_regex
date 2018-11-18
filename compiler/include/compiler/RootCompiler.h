//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_COMPILER_ROOTCOMPILER_H_
#define REGEX_COMPILER_COMPILER_ROOTCOMPILER_H_

#include "compiler/Compiler.h"

namespace compiler {

/**
 * The class responsible for compiling the root node of a Verilog regular expression module.  It will be responsible
 * for adding whatever the uniformly required text is, as well as recursively compiling any regex codon the expression
 * contains.
 */
class RootCompiler : public Compiler {
 public:
  RootCompiler() = default;
  void compile(std::shared_ptr<Codon> codon) override;
  std::string initializationText() override;
  std::string combinationalText() override;
  std::string sequentialText() override;
  ~RootCompiler() override = default;
};

}

#endif //REGEX_COMPILER_COMPILER_ROOTCOMPILER_H_
