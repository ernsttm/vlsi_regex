//
// Created by todd on 11/18/18.
//

#include "compiler/RootCompiler.h"

#include "compiler/CompilerException.h"

namespace compiler {

// This string contains the header information used by all regex modules.
const std::string ROOT_INITIALIZATION =
    "module compiled_regex(clk, rdy, reset, data, streamEnd, match, startPos, endPos);\n"
    "  input clk; // Input clock\n"
    "  output rdy; // Goes to 1 when the circuit has completed\n"
    "  input reset; // Reset the logic for the next execution cycle\n"
    "\n"
    "  input [7:0] data; // Next ASCII char in the input stream.\n"
    "  input streamEnd; // High when the stream is fully processed, false otherwise.\n"
    "  output match; // High if a match has been detected, false otherwise.\n"
    "  output [31:0] startPos; // If match is high, contains the location the pattern started.\n"
    "  output [31:0] endPos; // If match is high, contains the location the pattern ended.\n"
    "\n"
    "  // Status registers for loading wires\n"
    "  reg matchReg;\n"
    "  reg readyReg;\n"
    "\n"
    "  wire rdy = readyReg;\n"
    "  wire match = matchReg;\n"
    "\n"
    "  // Keep track of the current location in the stream\n"
    "  reg [31:0] charCounter = 0;\n"
    "  reg [31:0] charCounterNext;\n"
    "\n"
    "  // State for keeping track of the position within the pattern.\n"
    "  reg [31:0] position = 0;\n"
    "  reg [31:0] positionNext;\n"
    "\n"
    "  // Output position registers (including effectively temps)\n"
    "  reg [31:0] endReporter;\n"
    "  reg [31:0] startReporter;\n"
    "  reg [31:0] endPosition = -1;\n"
    "  reg [31:0] startPosition = -1;\n"
    "\n"
    "  wire endPos = endReporter;\n"
    "  wire startPos = startReporter;\n"
    "\n"
    "// Clear the state of the circuit for the next execution cycle.\n"
    "  task clear;\n"
    "    begin\n"
    "      readyReg = 0;\n"
    "      matchReg = 0;\n"
    "    end\n"
    "  endtask \n"
    "\n"
    "  // Trigger reporting a pattern success. \n"
    "  task success;\n"
    "    begin\n"
    "      matchReg = 1;\n"
    "      endReporter = endPosition;\n"
    "      startReporter = startPosition;\n"
    "      endPosition = -1;\n"
    "      startPosition = -1;"
    "    end\n"
    "  endtask \n";

const std::string ROOT_COMBO_HEADER =
    "// Combinational Logic for incrementing the counters\n"
    "  always @(*) begin\n"
    "    // Normal counters\n"
    "    positionNext = position + 1;\n"
    "    charCounterNext = charCounter + 1;\n";

const std::string ROOT_COMBO_FOOTER =
    "end // always @(*)\n";

const std::string ROOT_SEQ_HEADER =
    "// Sequential logic for determining if stream matches the given regular\n"
    "  // expression\n"
    "  always @(reset or posedge clk)\n"
    "    if (reset)\n"
    "      clear;\n"
    "    else if (streamEnd) begin\n"
    "      if (-1 != endPosition)\n"
    "        success;\n"
    "\n"
    "      readyReg = 1;\n"
    "    end else begin\n"
    "      // If the position is 0, assign it as a possible start position\n"
    "      // This avoids placing the logic in a specific regular expression subsection.\n"
    "      if (0 == position) begin\n"
    "        // A new opening character has been detected, note the position\n"
    "        startPosition = charCounter;\n"
    "      end // if (0 == startPosition)\n";

const std::string ROOT_SEQ_FOOTER =

    "\n"
    "      charCounter <= charCounterNext;\n"
    "      readyReg = 1;\n"
    "    end // else\n"
    "endmodule // combination";


void RootCompiler::handleCodon(std::shared_ptr<compiler::Codon> codon){
  if (CodonType::ROOT != codon->type()) {
    throw CompilerException { "Invalid codon given to root compiler." };
  }

  resetPatternSize();

  initText_ = ROOT_INITIALIZATION;
  comboText_ = ROOT_COMBO_HEADER;
  seqText_ = ROOT_SEQ_HEADER;

  for (auto& child : codon->children()) {
    std::shared_ptr<Compiler> codonCompiler = compile(child);

    initText_.append(codonCompiler->initializationText());
    comboText_.append(codonCompiler->combinationalText());
    seqText_.append(codonCompiler->sequentialText());
  }

  comboText_.append(ROOT_COMBO_FOOTER);
  seqText_.append(ROOT_SEQ_FOOTER);
}

std::string RootCompiler::initializationText() {
  return initText_;
}

std::string RootCompiler::combinationalText() {
  return comboText_;
}

std::string RootCompiler::sequentialText() {
  return seqText_;
}

}