#ifndef  STATE_MACHINE_H
#define STATE_MACHINE_H

// Basic includes
#include "State.h"
#include "Transition.h"
#include "Condition.h"

// Extra includes
#include "ConditionInAttackRange.h"
#include "ConditionOutOfAttackRange.h"
#include "ConditionOutOfChaseRange.h"
#include "ConditionInChaseRange.h"

class StateMachine
{
private:
	State* initialState;
	State* currentState;

	class Enemy* owner;

public:
	// Constructors
	StateMachine(Enemy* owner_) { owner = owner_; }
	~StateMachine() {};

	// Basic update
	void Update();

	// Set function
	void SetInitialState(State* initial_);

	// Get function
	STATE GetCurrentStateName() { return currentState->GetName(); }
};

#endif // !STATE_MACHINE_H
