#include "CharacterHealth.h"

void CharacterHealth::dead()
{
}

CharacterHealth::CharacterHealth()
{
}

CharacterHealth::~CharacterHealth()
{
}


void CharacterHealth::EnemytakeDamage(float EnemydamageAmount_) {
	health -= EnemydamageAmount_;
	if (health <= 0) {
		dead();
	}
	//std::cout << " health " << health << std::endl;
}