#ifndef CONDITION_OUT_OF_ATTACK_RANGE_H
#define CONDITION_OUT_OF_ATTACK_RANGE_H

// Basic include
#include "Condition.h"

class ConditionOutOfAttackRange :
	public Condition
{
public:
	ConditionOutOfAttackRange(Enemy* owner_) : Condition{ owner_ }
	{
		// Put other stuff here if needed in constructor
	}

	bool test();
};

#endif // !CONDITION_OUT_OF_ATTACK_RANGE_H
