//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_
#define REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_

#include "compiler/Compiler.h"

namespace compiler {

/**
 * This class is responsible for compiling a strictly matching pattern into a Verilog module. This could take the form
 * of a input regex like "test", where the only successfully matching pattern is "test".
 */
class PatternCompiler : public Compiler {
 public:
  PatternCompiler() = default;
  void compile(std::shared_ptr<Codon> codon) override;
  std::string initializationText() override;
  std::string combinationalText() override;
  std::string sequentialText() override;
  ~PatternCompiler() override = default;
};

}

#endif //REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_
