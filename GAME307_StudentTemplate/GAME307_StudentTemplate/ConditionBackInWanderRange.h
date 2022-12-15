#ifndef CONDITION_BACK_IN_WANDER_RANGE
#define CONDITION_BACK_IN_WANDER_RANGE

// Basic include
#include "Condition.h"

class ConditionBackInWanderRange :
	public Condition
{
public:
	ConditionBackInWanderRange(Enemy* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_BACK_IN_WANDER_RANGE
