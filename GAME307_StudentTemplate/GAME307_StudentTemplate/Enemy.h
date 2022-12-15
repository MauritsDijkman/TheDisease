#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include "GameObject.h"
#include "vector.h"
#include "Scene.h"
#include "KinematicBody.h"
#include "Node.h"
#include "SeekTarget.h"
#include "ArriveTarget.h"
#include "SteerToTarget.h"
#include "Wander.h"
#include "KinematicWander.h"
#include "Statemachine.h"

using namespace std;
using namespace MATH;

class Enemy {
private:
	class Scene* ownerScene;

	StateMachine* stateMachine;

	Node* currentTargetNode;
	int currentTargetNumber;

	vector<Node*> targetNodes;

	Vec3 spawnPos;
	Vec3 position;
	Vec3 velocity;

	float maxSpeed = 5;

	PlayerBody* player;

	float currentAttackValue;

	void HandleDecisionMaking(float deltaTime);
	void AttackPlayer(float deltaTime, float attackInterval);
public:
	class KinematicBody* moveBody;

	Enemy(PlayerBody* player_)
	{
		ownerScene = NULL;
		moveBody = NULL;
		player = player_;
	};
	~Enemy()
	{
		if (moveBody)
			delete moveBody;
	};

	bool OnCreate(Scene* ownerScene_);
	void OnDestroy() {};

	void setTexture(SDL_Texture* texture_) { moveBody->setTexture(texture_); }

	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& event);
	void render(float scale);

	float GetDistance(Vec3 p, Vec3 q);

	void SteerToNodeTarget_Caller(float deltaTime);
	void SteerToTargetPos_Caller(float deltaTime);
	void WanderRandom_Caller(float deltaTime);
	void SteerToNodeTarget(SteeringOutput* steering);
	void SteerToTargetPos(SteeringOutput* steering);
	void WanderRandom(SteeringOutput* steering);

	void SetTargetNodes(vector<Node*> targetNodes_) { targetNodes = targetNodes_; }

	Vec3 GetPos() { return moveBody->getPos(); }
	Vec3 GetPlayerPos() { return player->getPos(); }
	Vec3 GetSpawnPos() { return spawnPos; }

	bool readStateMachineXML(string fileName);
};
#endif // !ENEMY_H
