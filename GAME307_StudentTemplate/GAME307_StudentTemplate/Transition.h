#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"
#include "Condition.h"

class Transition
{
private:
	// Ignoring action for this demo
	State* targetState;
	Condition* condition;

public:
	// Constructors
	Transition(Condition* condition_, State* targetState_)
	{
		condition = condition_;
		targetState = targetState_;
	}
	~Transition();

	// Trigger condition
	bool IsTriggered() { return condition->test(); }

	// Get function
	State* GetTargetState() { return targetState; }
};

#endif // !TRANSITION_H
