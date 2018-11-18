// This simple module serves as my first foray into the world of regular 
// expression detection in verilog.  It will have the job of recognizing
// if a certain character is input (in this case 'a'), and returning true or
// false in the correct manner.
module char(clk, rdy, reset, testChar, match);
  input clk;
  output rdy;
  input reset;

  input [7:0] testChar;
  output match;

  reg [0:0] matchReg;
  reg [0:0] readyReg;
  reg [7:0] expectedChar;

  wire rdy = readyReg;
  wire match = matchReg;

  task clear;
    begin
      expectedChar = "A";
      readyReg = 0;
      matchReg = 0;
    end
  endtask

  initial clear;

  always @(reset or posedge clk)
    if (reset)
      clear;
    else begin
      if (testChar == expectedChar) begin
        matchReg = 1;
      end else begin 
        matchReg = 0;
      end // end else
      readyReg = 1;
    end // else
endmodule // char