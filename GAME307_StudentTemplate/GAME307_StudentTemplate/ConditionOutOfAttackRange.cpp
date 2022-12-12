#include "ConditionOutOfAttackRange.h"
#include "Character.h"

bool ConditionOutOfAttackRange::test()
{
	float thresholdDistance = 0.3f;

	if (VMath::distance(owner->GetPlayerPos(), owner->GetPos()) > thresholdDistance)
		return true;

	return false;
}
