/*! \mainpage Lab Exercise 1 - Simple Calc
 *
 * This is a simple program containing a number of bugs which you must fix.
 *
 * The program will not yet compile, you must first get the program to compile.
 *
 * Then you must track down, fix and comment (DOXYGEN) on ten bugs in the code.
 *
 * main.h also need comments to be completed.
 */

/*! \file main.cpp
 * \brief Main file for the application
 *
 * Contains the entry point of the application and the functions which combine 
 * to provide a simple calculator functionality.
 */


#include <iostream>
#include "main.h"

using namespace std;

int main() //!< Entry point for the application
{
	while(exitProgram = false);
	{
		menu(); // Run the menu
	}

	return 0;
}

//! A function which provides a simple text menu system 

void menu()
{
	char choice;
	int firstNumber;
	int secondNumber;

	cout << endl << endl<< "    Simple Calc" << endl << endl;
	cout << "    Menu Options" <<endl;
	cout << "====================" << endl << endl;
	cout << "1: Add two numbers" << endl;
	cout << "2: Subtract two numbers" << endl;
	cout << "3: Mulitply two numbers" << endl;
	cout << "4: Divide two numbers" << endl;
	cout << "x: Exit the program" << endl;

	cin >> choice;
	switch(choice)
	{
	case '1':
		getNumbers(&firstNumber,&secondNumber);
		add(firstNumber,secondNumber);
		break;
	case '2':
		getNumbers(&firstNumber,&secondNumber);
		subtract(firstNumber,secondNumber);
	case '3':
		getNumbers(&firstNumber,&secondNumber);
		subtract(firstNumber,secondNumber); 
		break;
	case '4':
		getNumbers(&firstNumber,&secondNumber);
		divide(firstNumber,secondNumber);
		break;
	case 'X':
		exitProgram = true;
		break;
	}
}

void getNumbers(int * aNumber, int *anotherNumber)
{
	cout << "Enter a number: ";
	cin >> *aNumber;
	cout << "Enter another number: ";
	cin >> anotherNumber;
}

void add(int aNumber, int anotherNumber)
{
	int result = aNumber + anotherNumber;
	cout << aNumber << " + " << anotherNumber << " = " << result << endl;
}

void multiply(int aNumber, int anotherNumber) 
{
	int result = aNumber * anotherNumber;
	cout << aNumber << " * " << anotherNumber << " = " << result << endl;
}

void divide(int aNumber, int anotherNumber) 
{
	int result = aNumber / anotherNumber;
	cout << aNumber << " / " << anotherNumber << " = " << result << endl;
}
