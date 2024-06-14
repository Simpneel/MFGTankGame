#pragma once
#include <raylib.h>
#include "GameObject.h"
using Vec3 = MathClasses::Vector3;


class SpriteObject : public GameObject {
public:
	Texture2D* Sprite;
	Vec3 Origin;
	SpriteObject();
protected:
	void OnDraw() override;
};