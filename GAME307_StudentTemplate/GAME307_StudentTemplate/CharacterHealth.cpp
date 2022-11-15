#include "CharacterHealth.h"


CharacterHealth::CharacterHealth() {}

CharacterHealth::~CharacterHealth() {}

void CharacterHealth::dead() {}

void CharacterHealth::EnemytakeDamage(float EnemydamageAmount_)
{
	health -= EnemydamageAmount_;

	if (health <= 0)
	{
		dead();
		health = 0;
	}
}
