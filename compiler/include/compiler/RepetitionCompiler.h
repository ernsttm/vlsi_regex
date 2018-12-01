//
// Created by todd on 11/30/18.
//

#ifndef REGEX_COMPILER_COMPILER_REPITITIONCOMPILER_H_
#define REGEX_COMPILER_COMPILER_REPITITIONCOMPILER_H_

#include <sstream>

#include "compiler/Compiler.h"

namespace compiler {

class RepetitionCompiler : public Compiler {
 public:
  RepetitionCompiler();

  explicit RepetitionCompiler(uint patternId);

  void handleCodon(std::shared_ptr<Codon> codon) override;

  std::string initializationText() override;

  std::string combinationalText() override;

  std::string sequentialText() override;

  ~RepetitionCompiler() override = default;

 private:
  std::shared_ptr<Codon> codon_;

  std::ostringstream initStream_;
  std::ostringstream comboStream_;
  std::ostringstream seqStream_;

  void repetitionInit();
  void repetitionCombo();
  void repetitionSeq();
};

}

#endif //REGEX_COMPILER_COMPILER_REPITITIONCOMPILER_H_
