// This module starts approaching the complexity of generating true regular 
// expression detection.  It will contain a pattern that can be repeated 1 to 
// n number of times. 
module repitition(clk, rdy, reset, nextChar, done, match, startPos, endPos); 
  input clk;
  output rdy;
  input reset;

  input [7:0] nextChar;
  input done;
  output match;
  output [31:0] startPos;
  output [31:0] endPos;

  reg [0:0] matchReg;
  reg [0:0] readyReg; 

  wire [7:0] expectedPattern [1:0];
  reg [0:0] position = 0;
  reg [0:0] positionNext;
  reg [0:0] lastPos = 1;

  reg [31:0] charCounter = 0;
  reg [31:0] charCounterNext;

  reg [31:0] endPosition = -1;
  reg [31:0] startPosition = -1;

  reg [31:0] endReporter;
  reg [31:0] startReporter;

  // Declare the expected pattern only once
  assign expectedPattern[0] = "a";
  assign expectedPattern[1] = "b";


  wire rdy = readyReg;
  wire match = matchReg;

  wire endPos = endReporter;
  wire startPos = startReporter;

  task clear;
    begin
      readyReg = 0;
      matchReg = 0;
    end
  endtask 

  task success;
    begin
      matchReg = 1;
      endReporter = endPosition;
      startReporter = startPosition;
    end
  endtask

  initial clear;

  // Combinational Logic
  always @(*) begin
    positionNext = position + 1;
    charCounterNext = charCounter + 1;
  end // always @(*)

  // Sequential Logic
  always @(reset or posedge clk)
    if (reset)
      clear;
    else begin
      if (done && -1 != endPosition) begin
        // The input stream has terminated, determine if there is a success
        // in the buffer and output it.
        success;
      end else begin // if (done && -1 != endPosition)
        if (nextChar == expectedPattern[position]) begin
          position <= positionNext;

          if (-1 == startPosition) begin
            startPosition <= charCounter;
          end // if (0 == startPosition)

          // A repitition has been detected 
          if (position == lastPos) begin
            position = 0;
            endPosition <= charCounter;
          end // if (position == endPosition)
        end else begin
          if (-1 != endPosition) begin
            success;
          end // if (0 != endPosition)

          endPosition <= -1;
          startPosition <= -1;
        end // if (nextChar == expectedPattern)

        charCounter <= charCounterNext;
      end // end else

      readyReg = 1;
    end // else

endmodule // pattern