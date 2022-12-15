#include "ConditionInChaseRange.h"
#include "Character.h"

bool ConditionInChaseRange::test()
{
	float thresholdDistance = 5.0f;

	if (VMath::distance(owner->GetPlayerPos(), owner->GetPos()) < thresholdDistance)
		return true;

	return false;
}
