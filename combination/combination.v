// This file represens a fully complex regular expression, including strict 
// patterns, wild cards, and 1 or more repititions.  This is the format that 
// will to be taken when compiling regular expressions into verilog using c.
//
// Since this will serve as a pattern for future generation, it will be more
// generic and stylized then a strictly optimized solution for the given pattern
// would necessarily have to be. 
module combination(clk, rdy, reset, data, streamEnd, match, startPos, endPos);
  input clk; // Input clock
  output rdy; // Goes to 1 when the circuit has completed
  input reset; // Reset the logic for the next execution cycle

  input [7:0] data; // Next ASCII char in the input stream.
  input streamEnd; // High when the stream is fully processed, false otherwise.
  output match; // High if a match has been detected, false otherwise.
  output [31:0] startPos; // If match is high, contains the location the pattern started.
  output [31:0] endPos; // If match is high, contains the location the pattern ended.

  // Status registers for loading wires
  reg matchReg;
  reg readyReg;

  wire rdy = readyReg;
  wire match = matchReg;

  // Keep track of the current location in the stream
  reg [31:0] charCounter = 0;
  reg [31:0] charCounterNext;

  // State for keeping track of the position within the pattern.
  reg [31:0] position = 0;
  reg [31:0] positionNext;

  // Output position registers (including effectively temps)
  reg [31:0] endReporter;
  reg [31:0] startReporter;
  reg [31:0] endPosition = -1;
  reg [31:0] startPosition = -1;

  wire endPos = endReporter;
  wire startPos = startReporter;

  // Finally we get to the step of declaring the individual patterns expected
  // The pattern this logic will search for is "test.(ab)*".  Meaning a matching
  // string will have the word "test", and wild card, and then one or more
  // repitions of the phrase "ab". 
  wire [7:0] simplePattern [3:0];
  wire [7:0] repPattern [1:0];

  assign simplePattern[0] = "t";
  assign simplePattern[1] = "e";
  assign simplePattern[2] = "s";
  assign simplePattern[3] = "t";
  reg [31:0] pattern_1_end = 4;

  reg [31:0] pattern_2_end = 4 + 1;

  assign repPattern[0] = "a";
  assign repPattern[1] = "b";
  reg [31:0] pattern_3_size = 2;
  reg [31:0] pattern_3_end = 5 + 2;

  // Repitition patterns require a special subtractor in the repition case.
  reg [31:0] pattern_3_reset;

  // Clear the state of the circuit for the next execution cycle.
  task clear;
    begin
      readyReg = 0;
      matchReg = 0;
    end
  endtask 

  // Trigger reporting a pattern success. 
  task success;
    begin
      matchReg = 1;
      endReporter = endPosition;
      startReporter = startPosition;
    end
  endtask 

  // Combinational Logic for incrementing the counters
  always @(*) begin
    // Normal counters
    positionNext = position + 1;
    charCounterNext = charCounter + 1;
    
    // Repitition pattern resets
    pattern_3_reset = position - pattern_3_size;
  end // always @(*)

  // Sequential logic for determining if stream matches the given regular
  // expression
  always @(reset or posedge clk)
    if (reset)
      clear;
    else begin
      if (streamEnd && -1 != endPosition) begin
        // The input stream has terminated with a detected pattern, report it.
        success;
      end else begin // if (streamEnd && -1 != endPosition)
        if (position < pattern_1_end) begin
          // Handle the first pattern logic (this is a simple pattern)
          if (data == simplePattern[position]) begin
            if (-1 == startPosition) begin
              // A new opening character has been detected, note the position
              startPosition <= position;
            end // if (0 == startPosition)

            position <= positionNext;
          end else begin 
            position = 0;
          end // end else
        end else if (position < pattern_2_end) begin 
          // Handle the second pattern logic (wild card)
          position <= positionNext;
        end else begin
          // Handle the third pattern logic (1 or more repition, this will 
          // include position increases as well as endPosition alteration)
          if (data == repPattern[position - pattern_2_end]) begin
            position <= positionNext;

            // A repitition has been detected
            if (position == pattern_3_end - 1) begin
              position <= pattern_3_reset;
              endPosition <= charCounter;
            end // if (rposition == pattern_2_end)
          end else begin
            if (-1 != endPosition) begin
              success;
            end // if (-1 != endPosition)

            position <= 0;
            endPosition <= -1;
          end // end else
        end // end else

        charCounter <= charCounterNext;
      end // end else

      readyReg = 1;
    end // else
endmodule // combination