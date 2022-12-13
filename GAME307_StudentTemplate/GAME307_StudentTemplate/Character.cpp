#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
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

	if (!body)
		return false;

	return true;
}

void Character::Update(float deltaTime)
{
	// Create a new overall steering output
	SteeringOutput* steering;
	steering = new SteeringOutput();

	if (stateMachine)
	{
		stateMachine->Update();

		switch (stateMachine->GetCurrentStateName())
		{
		case STATE::ATTACK:
			cout << "STATE: ATTACK" << endl;
			break;

		case STATE::CHASE:
			cout << "STATE: CHASE" << endl;
			steerToSeekPlayer(steering);
			break;

		case STATE::WANDER:
			cout << "STATE: DO_NOTHING" << endl;
			break;
		}
	}




	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	// using the target, calculate and set values in the overall steering output
	//steerToSeekPlayer(steering);

	//SteeringBehaviour* steering_algorithm = new Seek(body, target);
	//steering = steering_algorithm->getSteering();

	// apply the steering to the equations of motion
	body->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering)
		delete steering;
}

void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;
	PlayerBody* target = scene->game->getPlayer();

	SteeringBehaviour* steering_algorithm = new Seek(body, target);
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
void Character::dead() {

}

void Character::projectile()
{
	printf("Enemy killed \n");
}

void Character::HandleEvents(const SDL_Event& event)
{
	// Handle events here, if needed
}

void Character::render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// Notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}

bool Character::readStateMachineXML(string fileName)
{
	/**
	stateMachine = new StateMachine(this);

	State* attackPlayer = new State(STATE::ATTACK);
	State* chasePlayer = new State(STATE::CHASE);
	State* doNothing = new State(STATE::DO_NOTHING);

	// Chase -> Attack
	Condition* ifInAttackRange = new ConditionInAttackRange(this);
	chasePlayer->AddTransition(new Transition(ifInAttackRange, attackPlayer));

	// Attack -> Chase
	Condition* ifOutOfAttackRange = new ConditionOutOfAttackRange(this);
	attackPlayer->AddTransition(new Transition(ifOutOfAttackRange, chasePlayer));


	// Chase -> Do Nothing
	Condition* ifOutOfChaseRange = new ConditionOutOfChaseRange(this);
	chasePlayer->AddTransition(new Transition(ifOutOfChaseRange, doNothing));

	// Do Nothing -> Chase
	Condition* ifInChaseRange = new ConditionInChaseRange(this);
	doNothing->AddTransition(new Transition(ifInChaseRange, chasePlayer));

	stateMachine->SetInitialState(doNothing);
	/**/

	return true;
}
