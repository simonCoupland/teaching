#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

using namespace std;

template <classname G>
class Observer
{
public:
	virtual void update(G state) = 0;
};

template <classname G>
class Subject
{
protected:
public:
	void attach(Observer * observer);
	void detach(Observer * observer);
	void notify(G state);
};


#endif