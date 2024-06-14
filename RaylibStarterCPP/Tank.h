#pragma once
#include "SpriteObject.h"

class Tank : public SpriteObject {
protected:
	void OnUpdate(float deltaTime) override;
};

class Tank2 : public SpriteObject {
protected:
	void OnUpdate(float deltaTime) override;
};