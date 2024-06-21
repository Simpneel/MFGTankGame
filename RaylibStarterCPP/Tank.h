#pragma once
#include "SpriteObject.h"

class Tank : public SpriteObject {
protected:
	void OnUpdate(float deltaTime) override;
public:
	int Direction;
};