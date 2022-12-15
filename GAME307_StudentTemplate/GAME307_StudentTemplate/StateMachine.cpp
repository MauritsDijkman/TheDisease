// Header include
#include "StateMachine.h"

void StateMachine::SetInitialState(State* initial_)
{
	initialState = initial_;
	currentState = initialState;
}

void StateMachine::Update()
{
	Transition* triggered = NULL;

	// Store first transition that triggers
	for (auto transition : currentState->GetTransitions())
	{
		if (transition->IsTriggered())
		{
			triggered = transition;
			break;
		}
	}

	if (triggered)
	{
		State* targetState = triggered->GetTargetState();

		//[TODO] Collect exit actions, transition action, and target state actions
		currentState = targetState;
	}
	else
	{
		// Process actions for current state
	}

	// Return actions
	// But I'm not doing actions in this simple demo
	return;
}
