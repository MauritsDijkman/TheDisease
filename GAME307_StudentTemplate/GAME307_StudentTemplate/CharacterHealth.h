#ifndef CHARACTERHEALTH_H
#define CHARACTERHEALTH_H

#include "Object.h"

class CharacterHealth : public Object
{
protected:
	float health = 3.0f;
	float maxHealth = 3.0f;
	virtual void dead();

public:
	CharacterHealth();
	~CharacterHealth();

	void EnemytakeDamage(float enemydamageAmount_);

	float getHealth() { return health; }
	void setHealth(float newHealth) { health = newHealth; }
};

#endif // !CHARACTERHEALTH_H
