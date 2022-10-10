#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Character.h"

class EnemyCharacter : public CharacterHealth
{
private:
	int enemyType;

	void dead();

protected:
	float moveSpeed = 4.0f;

public:
	EnemyCharacter();
	~EnemyCharacter();

	void seekPlayer(Vec3 playerLocation_);

	void projectile();
};

#endif