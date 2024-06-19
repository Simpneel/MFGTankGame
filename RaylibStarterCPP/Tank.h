#pragma once
#include "SpriteObject.h"

class Tank : public SpriteObject {
protected:
	void OnUpdate(float deltaTime) override;
public:
	Vec3 GetLocation();
};

class Tank2 : public Tank {
protected:
	void OnUpdate(float deltaTime) override;
};