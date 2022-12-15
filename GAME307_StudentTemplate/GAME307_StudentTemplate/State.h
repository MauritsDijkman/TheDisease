#ifndef STATE_H
#define STATE_H

// Necessary include
#include <list>

// Namespace
using namespace std;

// States
enum class STATE { DO_NOTHING, WANDER, CHASE, ATTACK, BACK_TO_START };

// Necessary class include (solves weird bug)
class Transition;

class State
{
private:
	// List with transitions
	list<Transition*> transitions;

	// Ignore Actions for this simple example
	STATE name;

public:
	// Constructors
	State(STATE name_) { name = name_; }
	~State() {};

	// Add function
	void AddTransition(Transition* transition_) { transitions.push_back(transition_); }

	// Get functions
	list<Transition*> GetTransitions() { return transitions; }
	STATE GetName() { return name; }
};

#endif // !STATE_H
