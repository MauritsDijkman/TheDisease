#ifndef CONDITION_H
#define CONDITION_H

// Abstract class (has a pure virtual function)
class Condition
{
protected:
	class Character* owner;

public:
	// Constructor
	Condition(Character* owner_) { owner = owner_; }
	~Condition() {};

	// Test function
	virtual bool test() = 0;
};

#endif // !CONDITION_H
