#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* render_, string pathName_)
{
	surface = NULL;
	texture = NULL;

	surface = IMG_Load(pathName_.c_str());
	texture = SDL_CreateTextureFromSurface(render_, surface);
	if (surface == nullptr)
		std::cerr << "Can't open the image" << std::endl;

	pathName = pathName_;
}

void GameObject::Render(Matrix4 projectionMatrix_, SDL_Renderer* renderer_,
	float scale_, float orientationDegrees_)
{
	Vec3 screenCoords;
	int w, h;
	SDL_Rect square;

	Vec3 pos = Vec3(posX, posY, 0.0f);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix_ * pos;

	w = static_cast<int>(w * scale_);
	h = static_cast<int>(h * scale_);

	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees (degrees * 180.0f / M_PI).
	float orientationDegrees = orientationDegrees_ * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer_, texture, nullptr, &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);
}

#pragma region GetFunctions

SDL_Surface* GameObject::GetSurface()
{
	return surface;
}

SDL_Texture* GameObject::GetTexture()
{
	return texture;
}

Vec3 GameObject::GetPosition()
{
	return Vec3(posX, posY, 0.0f);
}

string GameObject::GetPathName()
{
	return pathName;
}

#pragma endregion
