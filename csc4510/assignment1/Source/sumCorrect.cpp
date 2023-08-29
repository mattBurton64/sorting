// This is a c++ program intended to take into two integer inputs, sum them and finally return the total value
#include <iostream>

int main () {
	int firstNumber = 0; // stores the first number input by the user
	int secondNumber = 0; // stores the second number input by the user
	int total = 0; // stores the total sum of the first and second values combined

	// Handles user input
	std::cout << "Enter 2 integers to be added together" << std::endl;
	std::cin >> firstNumber >> secondNumber;

	// Handles summing calculation
	total = firstNumber + secondNumber;
	
	// Handles output
	std::cout << firstNumber << " + " << secondNumber << " = " << total << std::endl;

	return 0;
}
