-- This is an Ada program intended to take into two integer inputs, sum them and finally return the total value
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Long_Long_Integer_Text_IO; use Ada.Long_Long_Integer_Text_IO;

procedure SumCorrect is
	-- variable declaration
    firstNumber : Long_Long_Integer; -- stores the first number input by the user
	secondNumber : Long_Long_Integer; -- stores the second number input by the user
	total : Long_Long_Integer; -- stores the total sum of the first and second numbers
begin
	-- Handles user input
    Put_Line("Enter 2 integers to be added together");
	Get(firstNumber);
	Get(secondNumber);
	
	-- Handles sum calculation
	total := firstNumber + secondNumber;

	-- Handles output
	Put (firstNumber, Width => 0);
	Put (" + ");
	Put (secondNumber, Width => 0);
	Put (" = ");
	Put (total, Width => 0);
end SumCorrect;
