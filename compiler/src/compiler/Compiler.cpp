//
// Created by todd on 11/18/18.
//

#include <fstream>

#include "compiler/Compiler.h"

#include "compiler/CompilerException.h"
#include "compiler/PatternCompiler.h"
#include "compiler/RootCompiler.h"

namespace compiler {

Compiler::Compiler() : patternId_ { PATTERN_COUNTER++ } { }

std::shared_ptr<Compiler> Compiler::compile(std::shared_ptr<compiler::Codon> codon) {
  std::shared_ptr<Compiler> codonCompiler;

  switch (codon->type()) {
    case CodonType::ROOT:
      codonCompiler = std::make_shared<RootCompiler>();
      break;
    case CodonType::PATTERN:
      codonCompiler = std::make_shared<PatternCompiler>();
      break;
    case CodonType::WILDCARD:
    case CodonType::REPITITION:
    default:
      throw CompilerException { "Codon not recognized." };
  }

  codonCompiler->handleCodon(codon);
  return codonCompiler;
}

void Compiler::output(const std::string& fileName, std::shared_ptr<compiler::Compiler> module) {
  std::ofstream file { };

  file.open(fileName, std::ofstream::out | std::ofstream::trunc);
  file << module->initializationText();
  file << module->combinationalText();
  file << module->sequentialText();
  file.close();
}

Compiler::Compiler(uint patternId) : patternId_ { patternId } { }

size_t Compiler::incrementPatternSize(size_t size) {
  PATTERN_SIZE += size;
  return PATTERN_SIZE;
}

size_t Compiler::PATTERN_SIZE = 0;
std::atomic_uint Compiler::PATTERN_COUNTER { 0 };

}