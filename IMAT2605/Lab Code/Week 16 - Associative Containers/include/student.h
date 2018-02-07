#ifndef STUDENT_H
#define STUDENT_H

// Using the std namespace
using namespace std;

enum DegreeClassifcation{first, upperSecond, lowerSecond, third, fail, unknown};

#include <string>

class Student
{
private:
	string pNumber; // A students P number
	string firstName; // A students first name
	string lastName; // A students first name
	DegreeClassifcation outcome; // The classification awarded to that student
public:
	Student(); // Default constructor
	Student(string newPNumber, string newFirstName, string newLastName, DegreeClassifcation newOutcome); // Constructor with values
	bool operator< (const Student other) const; // Overloaded < so we can put these in associative containers
	string toString() const; // String Representation of this object
};

#endif