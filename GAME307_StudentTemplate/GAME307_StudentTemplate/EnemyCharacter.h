#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H
#include "Character.h"
#include "Wander.h"

class EnemyCharacter : public CharacterHealth{

private:
	int enemyType;
	void Dead();

protected:
	float moveSpeed = 2.5f;//2.0

public:
	class KinematicBody* moveBody;
	EnemyCharacter();
	~EnemyCharacter() {if (moveBody) delete moveBody;};
	void SeekPlayer(Vec3 playerLocation_);
	void WanderRandom(SteeringOutput* steering);
	void projectile();
};
#endif //!ENEMYCHARACTER_H