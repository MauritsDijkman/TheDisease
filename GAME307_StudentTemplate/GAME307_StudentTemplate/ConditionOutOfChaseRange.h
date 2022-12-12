#ifndef CONDITION_OUT_OF_CHASE_RANGE_H
#define CONDITION_OUT_OF_CHASE_RANGE_H

// Basic include
#include "Condition.h"

class ConditionOutOfChaseRange :
	public Condition
{
public:
	ConditionOutOfChaseRange(Character* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_OUT_OF_CHASE_RANGE_H
