//#include "Button.h"
//
//Button::Button(const string& fileName_, Scene* owner_)
//{
//	scene = owner_;
//	image = IMG_Load(fileName_.c_str());
//}
//
//Button::~Button() {}
//
//bool Button::onCreate()
//{
//	Vec3 screenCoords;
//	int w, h;
//
//	SDL_Renderer* renderer;
//	SDL_Window* window = scene->getWindow();
//	renderer = SDL_GetRenderer(window);
//
//	texture = SDL_CreateTextureFromSurface(renderer, image);
//	if (image == nullptr)
//		cerr << "Can't open the image << endl;";
//
//	Vec3 pos = Vec3(10.0f, 8.0f, 0.0f);
//	float scale = 1.0f;
//	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
//	screenCoords = scene->getProjectionMatrix() * pos;
//	w = static_cast<int>(w * scale);
//	h = static_cast<int>(h * scale);
//
//	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
//	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
//	square.w = w;
//	square.h = h;
//
//	return true;
//}
//
//void Button::Render()
//{
//	SDL_Renderer* renderer;
//	SDL_Window* window = scene->getWindow();
//	renderer = SDL_GetRenderer(window);
//
//	float orientationDegrees = 0.0f;
//
//	SDL_RenderCopyEx(renderer, texture, nullptr, &square,
//		orientationDegrees, nullptr, SDL_FLIP_NONE);
//}
//
//bool Button::clicked(Vec3 mousePos_)
//{
//	// TODO
//	// Compare the mouse position to the bounding box of this button
//
//	// Create some variables, calculate the bounding box size in world coords
//	// based on the position of the button and the size of the texture
//
//	return true;
//}