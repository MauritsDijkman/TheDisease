#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H
#include "Character.h"

class EnemyCharacter : public CharacterHealth{
private:
	int enemyType;
	void Dead();
protected:
	float moveSpeed = 2.0f;//2.0
public:
	EnemyCharacter();
	~EnemyCharacter();
	void SeekPlayer(Vec3 playerLocation_);
	void projectile();
};
#endif //!ENEMYCHARACTER_H