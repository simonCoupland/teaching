// Include all STL sequence containers
#include <array>
#include <vector>
#include <deque>
#include <list>

// Include String and file processing tools
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Using the std namespace
using namespace std;

int main()
{
	string file1 = ".\\assets\\text\\1D.txt"; // A bunch of numbers
	string file2 = ".\\assets\\text\\2D.txt"; // A grid of numbers
	string file3 = ".\\assets\\text\\2D+.txt"; // Something else...?

	vector<int> vectorOfInts; // A vector
	deque<int> dequeOfInts; // A deque
	list<int> listofInts; // A list


	ifstream fileReader; // File reading tool
	istringstream parser; // String reading tool

	string line; // A string to be read from the file
	int num; // A number to be read from the string

	fileReader.open(file1); // Open a file
	if (fileReader.is_open()) // If it opened
	{
		// Read all the lines of text in one at a time
		// Each line is put in line
		while ( getline(fileReader,line) ) 
		{
			// Send the string reader to have our newly read line
			parser.str(line);
			// Read all the numbers
			while(parser >> num)
			{
				vectorOfInts.push_back(num);
			}
			parser.clear();
		}
		fileReader.close();
	}

	// Print out what has just been read in from a file
	for(int i=0;i < vectorOfInts.size();i++)
	{
		cout << vectorOfInts.at(i) << " ";
	}

	cout << endl;

	system("pause");

	return 0;
}