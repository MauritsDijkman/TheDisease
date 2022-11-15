#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Character.h"

class EnemyCharacter : public CharacterHealth
{
private:
	int enemyType;
	void Dead();

protected:
	float moveSpeed = 1.0f;

public:
	EnemyCharacter();
	~EnemyCharacter();

	void SeekPlayer(Vec3 playerLocation_);
	void projectile();
};

#endif //!ENEMYCHARACTER_H
