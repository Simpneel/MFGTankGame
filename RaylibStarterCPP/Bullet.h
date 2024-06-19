#pragma once
#include "SpriteObject.h"

class Bullet : public SpriteObject {
protected:
	int bulletCount = 0;
	void OnUpdate(float deltaTime);
public:
	bool CheckCollision(Rectangle colRec);
};
