//
// Created by todd on 11/29/18.
//

#ifndef REGEX_COMPILER_COMPILER_WILDCARDCOMPILER_H_
#define REGEX_COMPILER_COMPILER_WILDCARDCOMPILER_H_

#include <sstream>

#include "compiler/Compiler.h"

namespace compiler {

class WildcardCompiler : public Compiler {
 public:
  WildcardCompiler();

  explicit WildcardCompiler(uint patternId);

  void handleCodon(std::shared_ptr<Codon> codon) override;

  std::string initializationText() override;

  std::string combinationalText() override;

  std::string sequentialText() override;

  ~WildcardCompiler() override = default;

 private:
  std::shared_ptr<Codon> codon_;

  std::ostringstream initStream_;
  std::ostringstream seqStream_;

  void wildcardInit();
  void wildcardSeqLogic();
};

}

#endif //REGEX_COMPILER_COMPILER_WILDCARDCOMPILER_H_
