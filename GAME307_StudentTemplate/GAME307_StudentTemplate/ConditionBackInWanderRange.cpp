#include "ConditionBackInWanderRange.h"
#include "Enemy.cpp"

bool ConditionBackInWanderRange::test()
{
	float thresholdDistance = 5.0f;

	if (VMath::distance(owner->GetSpawnPos(), owner->GetPos()) < thresholdDistance)
		return true;

	return false;

}
