#include "ConditionOutOfChaseRange.h"
#include "Enemy.h"

bool ConditionOutOfChaseRange::test()
{
	float thresholdDistance = 5.0f;

	if (VMath::distance(owner->GetPlayerPos(), owner->GetPos()) > thresholdDistance)
		return true;

	return false;
}
