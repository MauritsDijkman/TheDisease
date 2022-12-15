#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter() : enemyType(0) {}

void EnemyCharacter::SeekPlayer(Vec3 playerLocation_)
{
	Vec3 enemyToPlayer = playerLocation_ - pos;
	int signx;
	int signy;

	if (signbit(enemyToPlayer.x) == 1)
		signx = -1;
	else
		signx = 1;

	if (signbit(enemyToPlayer.y) == 1)
		signy = -1;
	else
		signy = 1;

	if (fabs(enemyToPlayer.x) > 2 * fabs(enemyToPlayer.y))
		vel = Vec3(signx * moveSpeed, 0.0f, 0.0f);
	else if (fabs(enemyToPlayer.y) > 2 * fabs(enemyToPlayer.x))
		vel = Vec3(0.0f, signy * moveSpeed, 0.0f);
	else
		vel = Vec3(signx * moveSpeed, signy * moveSpeed, 0.0f);
}

void EnemyCharacter::WanderRandom(SteeringOutput* steering) {
	
	// Create a list with the steering outputs
	vector<SteeringOutput*> steering_outputs;
	
	// Set the steering behaviour
	SteeringBehaviour* steering_algorithm = new Wander(moveBody);
	steering_outputs.push_back(steering_algorithm->getSteering());
	
	// Add togethere any steering outputs
	for (unsigned i = 0; i < steering_outputs.size(); i++) {
		if (steering_outputs[i])
			*steering += *steering_outputs[i];
	}
	
	// Clean up memory
	if (steering_algorithm)
		delete steering_algorithm;
}

void EnemyCharacter::Dead()
{
	printf("Enemy is killed! \n");
}

void EnemyCharacter::projectile() {}