#include "ConditionInAttackRange.h"
#include "Enemy.h"

bool ConditionInAttackRange::test()
{
	float thresholdDistance = 0.3f;

	if (VMath::distance(owner->GetPlayerPos(), owner->GetPos()) < thresholdDistance)
		return true;

	return false;
}
