#pragma once
#include "SpriteObject.h"

class Turret : public SpriteObject {
protected:
	void OnUpdate(float deltaTime) override;
};