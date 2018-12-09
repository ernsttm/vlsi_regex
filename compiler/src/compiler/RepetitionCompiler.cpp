//
// Created by todd on 11/30/18.
//

#include <compiler/RepetitionCompiler.h>
#include <compiler/CompilerException.h>

#include "compiler/RepetitionCompiler.h"

namespace compiler {

RepetitionCompiler::RepetitionCompiler() : Compiler { } { }

RepetitionCompiler::RepetitionCompiler(uint patternId) : Compiler { patternId } { }

void RepetitionCompiler::handleCodon(std::shared_ptr<Codon> codon) {
  if (CodonType::REPITITION != codon->type()) {
    throw CompilerException { "Invalid codon given to repetition compiler. "};
  }

  if (!codon->children().empty()) {
    throw CompilerException { "Repetitions can only serve as terminal nodes."};
  }

  if (codon->pattern().empty()) {
    throw CompilerException { "Repetition cannot have an empty pattern. "};
  }
  codon_ = codon;

  repetitionInit();
  repetitionCombo();
  repetitionSeq();
}

std::string RepetitionCompiler::initializationText() {
  return initStream_.str();
}

std::string RepetitionCompiler::combinationalText() {
  return comboStream_.str();
}

std::string RepetitionCompiler::sequentialText() {
  return seqStream_.str();
}

void RepetitionCompiler::repetitionInit() {
  size_t patternEnd = incrementPatternSize(codon_->pattern().size());
  initStream_ << "  // Expected repetition for " << patternId_ << " with characters " << codon_->pattern() << std::endl;
  initStream_ << "  wire [7:0] pattern_" << patternId_ << "_expected [" << codon_->pattern().size() - 1 << ":0];\n";
  initStream_ << "  reg [31:0] pattern_" << patternId_ << "_end = " << patternEnd << ";\n";
  initStream_ << "  reg [31:0] pattern_" << patternId_ << "_beg = " << patternEnd - codon_->pattern().size() << ";\n";
  initStream_ << "  reg [31:0] pattern_" << patternId_ << "_size = " << codon_->pattern().size() << ";\n\n";

  initStream_ << "  // Repetition patterns require a special subtractor in the repetition case.\n"
                 "  reg [31:0] pattern_" << patternId_ << "_reset;\n\n";

  const std::string& pattern = codon_->pattern();
  for (uint i = 0; i < pattern.size(); i++) {
    initStream_ << "  assign pattern_" << patternId_ << "_expected[" << i << "] = \"" << pattern[i] << "\";\n";
  }
  initStream_ << std::endl;
}

void RepetitionCompiler::repetitionCombo() {
  comboStream_ << "    // Repetition pattern resets\n"
                  "    pattern_" << patternId_ << "_reset = position - pattern_" << patternId_ << "_size + 1;\n";
}

void RepetitionCompiler::repetitionSeq() {
  seqStream_ << "  if (data == pattern_" << patternId_ << "_expected[position - pattern_" << patternId_ << "_beg]) begin\n"
                "    position <= positionNext;\n"
                "\n"
                "    if (position == pattern_" << patternId_ << "_end - 1) begin\n"
                "      position <= pattern_" << patternId_ << "_reset;\n";

  if (codon_->final()) {
    seqStream_ << "      endPosition <= charCounter;\n";
  } else {
    seqStream_ << "      rep_found = 1;\n";
  }

  seqStream_ << "    end\n"
                "  end else begin\n";

  if (codon_->final()) {
    seqStream_ << "    if (-1 != endPosition) begin\n"
                  "      success;\n"
                  "    end\n"
                  "    endPosition <= -1;\n"
                  "    position <= 0;\n";
  } else {
    seqStream_ << "    if (rep_found) begin\n"
                  "      position = pattern_" << patternId_ << "_end;\n"
                  "      positionNext = pattern_" << patternId_ << "_end + 1;\n"
                  "    end else begin\n"
                  "      position <= 0;\n"
                  "    end\n";
    seqStream_ << "    rep_found = 0;\n";
  }
  seqStream_ << "    end\n";
}

}