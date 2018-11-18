// This is a slightly more complex module in that it allows the detection of 
// a specific pattern of character values. in the input.  It will keep track of 
// its position within the stream, and only go high when an entire pattern is 
// found.
module pattern(clk, rdy, reset, nextChar, match);
  input clk;
  output rdy;
  input reset;

  input [7:0] nextChar;
  output match;

  reg [0:0] matchReg;
  reg [0:0] readyReg;

  // The length of the expected pattern must correlate with the number of 
  // positions representable. 
  wire [7:0] expectedPattern [3:0];
  reg [1:0] position = 0;
  reg [1:0] positionNext;
  reg [1:0] endPosition = 3;

  // Declare the expected pattern only once
  assign expectedPattern[0] = "t";
  assign expectedPattern[1] = "e";
  assign expectedPattern[2] = "s";
  assign expectedPattern[3] = "t";

  wire rdy = readyReg;
  wire match = matchReg;

  task clear;
    begin
      // position = 0;
      readyReg = 0;
      matchReg = 0;
    end
  endtask 

  initial clear;

  // Combinational Logic
  always @(*) begin
    positionNext = position + 1;
  end // always @(*)

  // Sequential Logic
  always @(reset or posedge clk)
    if (reset)
      clear;
    else begin
      if (nextChar == expectedPattern[position]) begin
        position <= positionNext;

        if (position == endPosition) begin
          matchReg = 1;
          position = 0;
        end // if (position == endPosition)
      end else begin
        position = 0;
      end // if ()

      readyReg = 1;
    end // else
endmodule // pattern