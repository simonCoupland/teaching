// Include all STL associative containers
#include <set>
#include <map>

// Include the vector container
#include <vector>

// Include iostream so we can print to the screen
#include <iostream>

// Include the student header
#include "student.h"

// Using the std namespace
using namespace std;

ostream& operator<<(ostream& out, const Student& stu)
{
	return out << stu.toString();
}

int main()
{
	vector<Student> students(5);
	vector<Student>::iterator studentsIter;

	students.at(0) = Student("P09512154","Fred","Bloggs",upperSecond);
	students.at(1) = Student("P0965345X","Jack","Sprat",lowerSecond);
	students.at(2) = Student("P08654125","Henry","Hoover",upperSecond);
	students.at(3) = Student("P09565457","Alex","Smart",first);
	students.at(4) = Student("P09376595","Tim","Dumas",third);

	for(studentsIter=students.begin();studentsIter!=students.end();++studentsIter)
	{
		cout << (*studentsIter) << endl;
	}

	system("pause");
	return 0;
}