#ifndef AMMUNITION_H
#define AMMUNITION_H
#include "Object.h"

class Ammunition : public Object{

private:
	int visible = 1;

public:
	Ammunition();
	~Ammunition();
	int getvisible() { return visible; }
	void decrementVisible() { visible--; };
};
#endif //!AMMUNITION_H