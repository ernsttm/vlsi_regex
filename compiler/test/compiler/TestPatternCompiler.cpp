//
// Created by todd on 11/18/18.
//

#include <gtest/gtest.h>

#include <memory>

#include "compiler/PatternCompiler.h"

namespace compiler_test {

const std::string BASIC_INIT =
    "  // Expected pattern for 1 with characters test\n"
    "  wire [7:0] pattern_1_expected [3:0];\n"
    "  reg [31:0] pattern_1_end = 4;\n"
    "  reg [31:0] pattern_1_beg = 0;\n"
    "  reg [31:0] pattern_1_size = 4;\n"
    "\n"
    "  assign pattern_1_expected[0] = \"t\";\n"
    "  assign pattern_1_expected[1] = \"e\";\n"
    "  assign pattern_1_expected[2] = \"s\";\n"
    "  assign pattern_1_expected[3] = \"t\";\n"
    "\n";

const std::string BASIC_COMBO = "";

const std::string BASIC_SEQ = "          // Handle simple pattern logic\n"
                              "          if (data == pattern_1_expected[position - pattern_1_beg]) begin\n"
                              "            position <= positionNext;\n"
                              "          end else begin \n"
                              "            position = 0;\n"
                              "          end // end else\n\n";

TEST(compiler_test, basicPattern) {
  std::shared_ptr<compiler::Codon> codon = std::make_shared<compiler::Codon>(compiler::CodonType::PATTERN, "test", false);
  compiler::PatternCompiler patternCompiler { 1 };
  patternCompiler.handleCodon(codon);

  ASSERT_EQ(BASIC_INIT, patternCompiler.initializationText());
  ASSERT_EQ(BASIC_COMBO, patternCompiler.combinationalText());
  ASSERT_EQ(BASIC_SEQ, patternCompiler.sequentialText());
}

}