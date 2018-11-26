// This serves as a simulation main to allow the running of test regular expression modules.
module main;
    reg clk, reset;
    reg [8:0] data;
    reg [7:0] char;
    reg [150 * 8:0] fileName;

    reg last;
    wire y;
    wire rdy;

    wire [31:0] endPos;
    wire [31:0] startPos;

    compiled_regex dut (clk, rdy, reset, char, last, match, startPos, endPos);

    always #10 clk = ~clk;

    integer i;
    integer file;

    task triggerDetector;
        begin
            clk = 0;
            reset = 1;

            #35 reset = 0;

            wait (rdy);
            if (match)
                $display("%d,%d\n", startPos, endPos);
        end
    endtask

    initial begin
        last = 0;

        // Load the data from the hex file
        if ($value$plusargs("DATA_FILE=%s", fileName)) begin
            file = $fopen(fileName, "r");
            data = $fgetc(file);
            while (data != 'h1ff) begin
                char = data;
                triggerDetector;

                data = $fgetc(file);
            end // for (i = 0; i <= 4; i = i + 1)

            last = 1;
            triggerDetector;

            $finish;
        end // if (("DATA_FILE", fileName))
    end // initial

endmodule // main