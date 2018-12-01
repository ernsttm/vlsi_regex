//
// Created by todd on 11/29/18.
//

#include <compiler/CompilerException.h>
#include <compiler/WildcardCompiler.h>

#include "compiler/WildcardCompiler.h"

namespace compiler {

WildcardCompiler::WildcardCompiler() : Compiler { } { }

WildcardCompiler::WildcardCompiler(uint patternId) : Compiler { patternId } { }

void WildcardCompiler::handleCodon(std::shared_ptr<compiler::Codon> codon) {
  if (CodonType::WILDCARD != codon->type()) {
    throw CompilerException { "Invalid codon given to wildcard compiler." };
  }

  if (!codon->children().empty()) {
    throw CompilerException { "Wildcards can only serve as terminal nodes" };
  }

  if (!codon->pattern().empty()) {
    throw CompilerException { "Wildcard can't utilize patterns" };

  }

  codon_ = codon;
  wildcardInit();
  wildcardSeqLogic();
}

std::string WildcardCompiler::initializationText() {
  return initStream_.str();
}

std::string WildcardCompiler::combinationalText() {
  return "";
}

std::string WildcardCompiler::sequentialText() {
  return seqStream_.str();
}

void WildcardCompiler::wildcardInit() {
  initStream_ << "  // Wildcard for pattern: " << patternId_ << std::endl;
  initStream_ << "  reg [31:0] pattern_" << patternId_ << "_size = " << incrementPatternSize(1) << ";\n\n";
}

void WildcardCompiler::wildcardSeqLogic() {
  seqStream_ << "        if (position == pattern_" << patternId_ << "_size - 1) begin\n";
  if (codon_->final()) {
    seqStream_ << "          endPosition = charCounter;\n"
                  "          success;\n";
  } else {
    seqStream_ << "          position <= positionNext;\n";
  }
  seqStream_ << "        end\n";
}



}