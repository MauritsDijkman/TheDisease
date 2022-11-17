#ifndef NODE_H
#define NODE_H
#include "MMath.h"

using namespace std;
using namespace MATH;

class Tile;
class Node{
private:
	int	label;
	Vec3 position;
	Tile* tile;
public:
	Node(int label_, Vec3 position_ = Vec3()){
		label = label_;
		position = position_;
		tile = NULL;
	}

	~Node();
	// Get functions
	int GetLabel() { return label; }
	Vec3 GetPos() { return position; }
	Tile* GetTile() { return tile; }
	// Set functions
	void SetTile(Tile* tile_) { tile = tile_; }
	void SetPosX(float posX_) { position.x = posX_; }
	void SetPosY(float posY_) { position.y = posY_; }
};
#endif // !NODE_H