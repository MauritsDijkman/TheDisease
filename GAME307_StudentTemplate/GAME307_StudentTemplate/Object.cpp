#include "Object.h"

Object::Object() : texture(nullptr) {}

Object::Object(SDL_Texture* texture_) {}

Object::~Object()
{
}

bool Object::OnCreate()
{
	return false;
}

void Object::OnDestroy()
{
}

void Object::Update(float deltaTime_)
{
}

void Object::Render() const
{
}

void Object::HandleEvent(const SDL_Event& event)
{
}
