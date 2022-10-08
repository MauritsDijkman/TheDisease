#ifndef SEEK_TARGET_H
#define SEEK_TARGET_H

#include "SteeringBehaviour.h"
#include "Node.h"

class SeekTarget :
	public SteeringBehaviour
{
protected:
	Node* target;

public:
	SeekTarget(Body* character_, Node* target_);
	virtual ~SeekTarget();

	SteeringOutput* getSteering();
};

#endif
