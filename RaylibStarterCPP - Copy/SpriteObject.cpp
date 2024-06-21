#include "SpriteObject.h"

using Mat3 = MathClasses::Matrix3;

SpriteObject::SpriteObject()
{
	Sprite = nullptr;
	Origin = Vec3(0.5f, 0.5f, 0.5f);
}

void SpriteObject::OnDraw()
{
	Vec3 pos = GetWorldPosition();
	float rot = GetWorldRotation() * RAD2DEG;
	Vec3 scale = GetWorldScale();

	DrawTexturePro(*Sprite, 
		Rectangle{ 0.0f, 0.0f, (float)Sprite->width, (float)Sprite->height },
		Rectangle{pos.x, pos.y, (float)Sprite->width * scale.x, (float)Sprite->height * scale.y},
		Vector2{ Sprite->width * Origin.x * scale.x, Sprite->height * Origin.y * scale.y },
		rot, WHITE);
}
