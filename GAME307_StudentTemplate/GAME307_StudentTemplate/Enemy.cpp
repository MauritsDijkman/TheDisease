#include "Enemy.h"

bool Enemy::OnCreate(Scene* ownerScene_)
{
	ownerScene = ownerScene_;

	for (int i = 0; i < 4; i++)
	{
		Node* node_ = new Node();
		node_->SetPosition(Vec3(i + 2, 0.0f, 0.0f));
		targetNodes.push_back(node_);
	}

	/**/
	if (targetNodes.size() > 0) {
		currentTargetNumber = 0;
		currentTargetNode = targetNodes[currentTargetNumber];
		cout << "Current target node: " << currentTargetNumber << endl;
		cout << "Current target node position: " << currentTargetNode->GetPos().x << " || " << currentTargetNode->GetPos().y << endl;
	}
	/**/

	// Configure and instantiate the body to use for the demo
	if (!moveBody)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		moveBody = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!moveBody)
		return false;

	return true;
}

void Enemy::Update(float deltaTime)
{
	/**/
	if (currentTargetNode)
	{
		float distance = GetDistance(position, currentTargetNode->GetPos());
		cout << "Distance: " << distance << endl;

		if (distance < 0.5f)
		{
			currentTargetNumber++;
			currentTargetNode = targetNodes[currentTargetNumber];
		}
		else
			MoveToTarget(deltaTime);
	}
	/**/
}

void Enemy::MoveToTarget(float deltaTime)
{
	SteeringOutput* steering;
	steering = new SteeringOutput();

	SteerToTarget(steering);

	moveBody->Update(deltaTime, steering);

	if (steering)
		delete steering;
}

void Enemy::HandleEvents(const SDL_Event& event)
{
	// Handle events here, if needed
}

void Enemy::render(float scale)
{
	/**/
	SDL_Renderer* renderer = ownerScene->game->getRenderer();
	Matrix4 projectionMatrix = ownerScene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// Notice use of "body" in the following
	SDL_QueryTexture(moveBody->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * moveBody->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees
	float orientation = moveBody->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, moveBody->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
	/**/
}

void Enemy::SteerToTarget(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;

	//SteeringBehaviour* steering_algorithm = new SeekTarget(moveBody, currentTargetNode);
	SteeringBehaviour* steering_algorithm = new ArriveTarget(moveBody, currentTargetNode);
	steering_outputs.push_back(steering_algorithm->getSteering());

	// Add togethere any steering outputs
	for (unsigned i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
			*steering += *steering_outputs[i];
	}

	// Clean up memory
	if (steering_algorithm)
		delete steering_algorithm;
}

float Enemy::GetDistance(Vec3 p, Vec3 q)
{
	// Distance = sqrt((pX-qX)^2 + (pY-qY)^2)
	return sqrt((p.x - q.x) * (p.x - q.x) +
		(p.y - q.y) * (p.y - q.y));
}
