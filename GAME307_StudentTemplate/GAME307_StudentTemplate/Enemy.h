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

using namespace std;
using namespace MATH;

class Enemy
{
private:
	class Scene* ownerScene;
	class KinematicBody* moveBody;

	Node* currentTargetNode;
	int currentTargetNumber;

	vector<Node*> targetNodes;

	Vec3 position;
	Vec3 velocity;

	float maxSpeed = 5;

public:
	Enemy()
	{
		ownerScene = NULL;
		moveBody = NULL;
	};

	~Enemy() {
		if (moveBody)
			delete moveBody;
	};

	bool OnCreate(Scene* ownerScene_);
	void OnDestroy() {};

	void setTexture(SDL_Texture* texture_)
	{
		moveBody->setTexture(texture_);
	}

	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& event);
	void render(float scale);

	void MoveToTarget(float deltaTime);
	float GetDistance(Vec3 p, Vec3 q);

	void SteerToTarget(SteeringOutput* steering);
};

#endif // !ENEMY_H
