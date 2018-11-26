//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_
#define REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_

#include <sstream>

#include "compiler/Compiler.h"

namespace compiler {

/**
 * This class is responsible for compiling a strictly matching pattern into a Verilog module. This could take the form
 * of a input regex like "test", where the only successfully matching pattern is "test".
 */
class PatternCompiler : public Compiler {
 public:
  PatternCompiler();

  explicit PatternCompiler(uint patternId);

  void handleCodon(std::shared_ptr<Codon> codon) override;

  std::string initializationText() override;

  std::string combinationalText() override;

  std::string sequentialText() override;

  ~PatternCompiler() override = default;

 private:
  size_t size_;
  std::shared_ptr<Codon> codon_;

  std::ostringstream initStream_;
  std::ostringstream seqStream_;

  bool validPattern(const std::string& pattern);
  void patternInitComment();
  void patternInitDeclare();
  void patternInitSize();
  void patternInitAssign();
  void patternSeqLogic();
};

}

#endif //REGEX_COMPILER_COMPILER_PATTERNCOMPILER_H_
