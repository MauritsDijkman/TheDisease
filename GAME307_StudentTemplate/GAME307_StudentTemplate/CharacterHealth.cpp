#include "CharacterHealth.h"

void CharacterHealth::dead()
{
}

CharacterHealth::CharacterHealth() : health(3.0f), maxHealth(3.0f)
{
}

CharacterHealth::~CharacterHealth()
{
}


void CharacterHealth::takeDamage(float damageAmount_) {
	health -= damageAmount_;
	if (health <= 0) {
		dead();
	}
}