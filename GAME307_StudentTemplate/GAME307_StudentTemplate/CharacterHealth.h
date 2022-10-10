#ifndef CHARACTERHEALTH_H
#define CHARACTERHEALTH_H

#include "Object.h"

class CharacterHealth : public Object
{
protected:
	float health, maxHealth;
	virtual void dead();
public:
	CharacterHealth();
	~CharacterHealth();

	void takeDamage(float damageAmount_);

	float getHealth() { return health = 0; }

	void setHealth(float h) { health = h; }

	//virtual float getHealth() = 0; //Get the player health
};
#endif
