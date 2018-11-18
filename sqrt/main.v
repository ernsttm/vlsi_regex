// This module serves as the entry point into the square root modules that
// I am going to test/develop for my regular expression project.
//
// Effectively it will read in a file, and then serve it to the declared 
// module.
module main;

  reg clk, reset;
  reg [31:0] data[4:0];
  reg [31:0] x;
  reg [150 * 8:0] fileName;
  wire [15:0] y;
  wire rdy;

  sqrt32 dut (clk, rdy, reset, x, y);

  always #10 clk = ~clk;

  integer i;
  initial begin
    // Load the data from the hex file
    if ($value$plusargs("DATA_FILE=%s", fileName)) begin
      $display("Using data file : %0s", fileName);
      $readmemh(fileName, data);
      for (i = 0; i <= 4; i = i + 1) begin
        clk = 0;
        reset = 1;

        x = data[i];

        #35 reset = 0;

        wait (rdy) $display("y = %d", y);
      end // for (i = 0; i <= 4; i = i + 1)
      $finish;
    end // if (("DATA_FILE", fileName))
  end // initial

endmodule // main