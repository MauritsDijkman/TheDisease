#ifndef CONDITION_H
#define CONDITION_H

// Abstract class (has a pure virtual function)
class Condition
{
protected:
	class Enemy* owner;

public:
	// Constructor
	Condition(Enemy* owner_) { owner = owner_; }
	~Condition() {};

	// Test function
	virtual bool test() = 0;
};

#endif // !CONDITION_H
