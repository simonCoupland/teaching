#include <string>
#include <fstream>
#include <fstream>
#include <algorithm>

using namespace std;

void main()
{
	string sText = "Civic";
	ifstream sourceFile("source.txt");

	if (sourceFile.is_open())
	{
		getline(sourceFile, sText);
	}
	
	// Using the STL Algorithms:

	// 1. Count how many words are contained in the string sText
	// 2. Convert all characters to lower case
	// 3. Identify whether or not the text is a palindrome
}