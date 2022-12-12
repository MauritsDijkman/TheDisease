#ifndef CONDITION_IN_CHASE_RANGE_H
#define CONDITION_IN_CHASE_RANGE_H

// Basic include
#include "Condition.h"

class ConditionInChaseRange :
	public Condition
{
public:
	ConditionInChaseRange(Character* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_IN_CHASE_RANGE_H
