#ifndef OBJECT_H
#define OBJECT_H
#include "SDL_image.h"
#include "PhysicsObject.h"
using namespace MATH;

class Object : public PhysicsObject{

private:
	SDL_Texture* texture;

public:
	Object();
	Object(SDL_Texture* texture_);
	~Object();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvent(const SDL_Event& event);
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};
#endif // !OBJECT_H