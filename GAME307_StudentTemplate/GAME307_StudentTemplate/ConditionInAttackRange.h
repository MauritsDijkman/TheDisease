#ifndef CONDITION_IN_ATTACK_RANGE
#define CONDITION_IN_ATTACK_RANGE

// Basic include
#include "Condition.h"

class ConditionInAttackRange :
	public Condition
{
public:
	ConditionInAttackRange(Character* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_IN_ATTACK_RANGE
