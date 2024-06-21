#pragma once
#include "SpriteObject.h"

class Bullet : public SpriteObject {
protected:
	void OnUpdate(float deltaTime);
public:
	bool CheckCollision(Rectangle colRec);
	bool CheckCollision(Rectangle top, Rectangle bot, Rectangle left, Rectangle right);
};
