#include "student.h"

Student::Student()
{
	pNumber = "";
	firstName = "";
	lastName = "";
	outcome = unknown;
}

Student::Student(string newPNumber, string newFirstName, string newLastName, DegreeClassifcation newOutcome)
{
	pNumber = newPNumber;
	firstName = newFirstName;
	lastName = newLastName;
	outcome = newOutcome;
}

bool Student::operator< (const Student other) const
{
	return pNumber < other.pNumber;
}

string Student::toString() const
{
	string str;
	string outcomes[5] = {"First","2:1","2:2","Third","Unclassified"};
	str.append(pNumber);
	str.append("\t");
	str.append(firstName);
	str.append("\t");
	str.append(lastName);
	str.append("\t");
	str.append(outcomes[outcome]);
	return str;
}