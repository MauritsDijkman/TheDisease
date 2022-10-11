#include "Level.h"
Level::Level(int wallNum_) {
	wallNum = wallNum_;
	walls = new Wall * [wallNum];
	for (int i = 0; i < wallNum; i++) {
		walls[i] = new Wall;
		walls[i]->setBoundingBoxWidth(1.0f);
		walls[i]->setBoundingBoxHeight(1.0f);
	}



}

Level::~Level() {
	for (int i = 0; i < wallNum; i++) {
		delete walls[i];
	}

	delete walls;

}

void Level::makeLevel(int sceneNum) { //Makes the level by placing all the walls
	//For outside walls
	//float xpos1 = 0.0;
	//float ypos1 = 0.0f;
	//float xpos2 = 0.0f;
	//float ypos2 = 0.0f;

	//For interior walls
	//float xpos3 = 0.0f;
	//float ypos3 = 0.0f;


	switch (sceneNum) {

	case 1:

		//Interior walls       x.x    y.y    z.z
		walls[46]->setPos(Vec3(8.0f, 11.0f, 0.0f));
		walls[47]->setPos(Vec3(8.0f, 9.0f, 0.0f));
		walls[48]->setPos(Vec3(10.0f, 12.0f, 0.0f));

		walls[49]->setPos(Vec3(8.0f, 5.0f, 0.0f));
		walls[50]->setPos(Vec3(8.0f, 3.0f, 0.0f));
		walls[51]->setPos(Vec3(10.0f, 3.0f, 0.0f));

		walls[52]->setPos(Vec3(18.0f, 11.0f, 0.0f));
		walls[53]->setPos(Vec3(20.0f, 11.0f, 0.0f));
		walls[54]->setPos(Vec3(20.0f, 9.0f, 0.0f));

		walls[55]->setPos(Vec3(18.0f, 3.0f, 0.0f));
		walls[56]->setPos(Vec3(20.0f, 3.0f, 0.0f));
		walls[57]->setPos(Vec3(20.0f, 5.0f, 0.0f));


		break;
	default:
		break;
	}

}

void Level::setWallTextures(SDL_Texture* texturePtr) {
	for (int i = 0; i < wallNum; i++) {
		walls[i]->setTexture(texturePtr);
	}

}