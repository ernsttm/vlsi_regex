//
// Created by todd on 11/18/18.
//

#include "compiler/PatternCompiler.h"

#include "compiler/CompilerException.h"

namespace compiler {

PatternCompiler::PatternCompiler() : Compiler { } { }

PatternCompiler::PatternCompiler(uint patternId) : Compiler { patternId } { }

void PatternCompiler::handleCodon(std::shared_ptr<compiler::Codon> codon){
  if (CodonType::PATTERN != codon->type()) {
    throw CompilerException { "Invalid codon given to pattern compiler" };
  }

  if (!codon->children().empty()) {
    throw CompilerException { "Patterns can only serve as terminal nodes." };
  }

  if (codon->pattern().empty()  || !validPattern(codon->pattern())) {
    throw CompilerException { "Patterns must have a valid character sequence to match." };
  }
  codon_ = codon;

  patternInitComment();
  patternInitDeclare();
  patternInitSize();
  patternInitAssign();
  patternSeqLogic();
}

std::string PatternCompiler::initializationText() {
  return initStream_.str();
}

std::string PatternCompiler::combinationalText() {
  return "";
}

std::string PatternCompiler::sequentialText() {
  return seqStream_.str();
}

bool PatternCompiler::validPattern(const std::string& pattern) {
  for (char c : pattern) {
    if (48 > c || 127 < c) {
      // If the character is outside of the range supported, fail to compile the pattern.
      return false;
    }
  }

  return true;
}

void PatternCompiler::patternInitComment() {
  initStream_ << "  // Expected pattern for " << patternId_ << " with characters " << codon_->pattern() << std::endl;
}

void PatternCompiler::patternInitDeclare() {
  initStream_ << "  wire [7:0] pattern_" << patternId_ << "_expected [" << codon_->pattern().size() - 1 << ":0];" << std::endl;
}

void PatternCompiler::patternInitSize() {
  initStream_ << "  reg [31:0] pattern_" << patternId_ << "_size = " << incrementPatternSize(codon_->pattern().size())
      << ";" << std::endl << std::endl;
}

void PatternCompiler::patternInitAssign() {
  const std::string& pattern = codon_->pattern();
  for (uint i = 0; i < pattern.size(); i++) {
    initStream_ << "  assign pattern_" << patternId_ << "_expected[" << i << "] = \"" << pattern[i] << "\";"
        << std::endl;
  }
  initStream_ << std::endl;
}

void PatternCompiler::patternSeqLogic() {
  seqStream_ << "          // Handle simple pattern logic\n"
                "          if (data == pattern_" << patternId_ << "_expected[position]) begin\n"
                "            position <= positionNext;\n";

  if (codon_->final()) {
    seqStream_ << "            if (position == pattern_" << patternId_ <<"_size) begin\n"
                  "              success;\n"
                  "            end\n";
  }

  seqStream_ << "          end else begin \n"
                "            position = 0;\n"
                "          end // end else\n" << std::endl;
}

}