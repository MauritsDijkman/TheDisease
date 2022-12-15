#include "ConditionOutOfWanderRange.h"
#include "Enemy.h"

bool ConditionOutOfWanderRange::test()
{
	float thresholdDistance = 5.0f;

	if (VMath::distance(owner->GetSpawnPos(), owner->GetPos()) > thresholdDistance)
		return true;

	return false;
}
