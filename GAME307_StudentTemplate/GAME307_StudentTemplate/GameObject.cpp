#include "GameObject.h"

GameObject::GameObject() : texture(nullptr){}

GameObject::GameObject(SDL_Texture* texture_){}

GameObject::~GameObject()
{
}

bool GameObject::OnCreate()
{
	return false;
}

void GameObject::OnDestroy()
{
}

void GameObject::Update( float deltaTime_)
{
}

void GameObject::Render() const
{
}

void GameObject::HandleEvent(const SDL_Event& event)
{
}
