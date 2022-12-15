#ifndef CONDITION_OUT_OF_WANDER_RANGE
#define CONDITION_OUT_OF_WANDER_RANGE

// Basic include
#include "Condition.h"

class ConditionOutOfWanderRange :
	public Condition
{
public:
	ConditionOutOfWanderRange(Enemy* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_OUT_OF_WANDER_RANGE
